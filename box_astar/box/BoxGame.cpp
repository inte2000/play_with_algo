#include "stdafx.h"
#include "BoxGame.h"
#include "AStar.h"



//std::vector<Direction> dirs = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };


bool BoxGame::InitMap(char *map, int row, int col)
{
    if ((row < 0) || (row >= MAX_MAP_ROW))
    {
        return false;
    }

    if ((col < 0) && (col >= MAX_MAP_COL))
    {
        return false;
    }

    m_map = new BoxGameMap(map, row, col);
    GameState *state = new GameState(map, row, col);
    m_states.push_back(state);
    m_map->PrintMap();
    return (m_map != nullptr);
}

bool BoxGame::ResolveGame()
{
    int index = 0;
    while (index < static_cast<int>(m_states.size()))
    {
        GameState *state = m_states[index];
        if (IsFinalState(state))
        {
            m_result++;
            PrintMoveRecords(state);
        }
        else
        {
            SearchNewGameStates(state);
        }

        index++;
        if ((index % 1000) == 0)
            std::cout << "index " << index << std::endl;
    }

    return (m_result > 0);
}

bool BoxGame::CanPushBox(GameState *state, const MapPos& man, int row_offset, int col_offset)
{
    bool canMove = false;

    MapPos box = { man.row + row_offset, man.col + col_offset }; //小人的推动方向是箱子
    MapPos boxTo = { box.row + row_offset, box.col + col_offset }; //箱子的新位置坐标

    MapNode& node = m_map->Get(boxTo.row, boxTo.col);
    if (node.isDead)
    {
        return false; //这个位置是死点
    }
    if ((node.value == MAP_V_BOARD) || state->IsBox(boxTo.row, boxTo.col))
    {
        return false; //这个位置是障碍物或其他箱子
    }

    return true;
}

void BoxGame::SearchNewGameStates(GameState *state)
{
    Direction dirs[] = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };

    for (int i = 0; i < state->GetBoxCount(); i++)
    {
        //检查每一个箱子周围四个方向是否有空位置，可以将小人移动过来
        MapPos box = state->GetBox(i);
        for (auto& dir : dirs)
        {
            MapPos newMan = { box.row + dir.row_offset, box.col + dir.col_offset };
            //只要不是墙或箱子，就尝试能否将小人移动到箱子边上
            if (!m_map->IsWall(newMan.row, newMan.col) && !state->IsBox(newMan.row, newMan.col))
            {
                AStar astar(m_map, state);
                std::vector<MapPos> path;
                if (astar.FindPath(state->GetMan(), newMan, path)) //有路径可以到这个地方
                {
                    //推的方向是小人的与箱子位置的反方向
                    Direction push = { -dir.row_offset, -dir.col_offset };
                    MoveToNewState(state, newMan, path, push);//尝试在这个位置推箱子
                }
            }
        }
    }
}

void BoxGame::MoveToNewState(GameState *parent, const MapPos& man, std::vector<MapPos>& path, const Direction& push)
{
    if (CanPushBox(parent, man, push.row_offset, push.col_offset))
    {
        GameState *state = new GameState(parent);
        state->SetActionPath(path);
        state->MoveMan(man.row, man.col, push.row_offset, push.col_offset);
        if (!AddNewState(state))
        {
            delete state;
        }
    }
}

bool BoxGame::IsFinalState(const GameState *state)
{
    for (int i = 0; i < state->GetBoxCount(); i++)
    {
        MapPos box = state->GetBox(i);
        MapNode node = m_map->Get(box.row, box.col);
        if (!node.isDest)
            return false;
    }

    return true;
}

bool BoxGame::AddNewState(GameState *state)
{

    for (auto& item : m_states)
    {
        if (item->IsSameState(state))
        {
            return false;
        }
    }

    m_states.push_back(state);
    return true;
}

void BoxGame::PrintMoveRecords(GameState *state)
{
    std::cout << "Find result "<< m_result << ": " << std::endl;
    
    GameState *parent = state;
    while (parent != nullptr)
    {
        const std::vector<MapPos>& path = parent->GetActionPath();

        std::cout << "Step x:" << std::endl;
        if (!path.empty())
        {
            std::cout << "Man Move :";
            for (auto& item : path)
            {
                std::cout << "[" << item.row << " , " << item.col << "] ";
            }
            std::cout << std::endl;
        }
        MapPos man = parent->GetMan();

        std::cout << "Man push [ "<< man.row << " , "<< man.col << " ]" << std::endl;

        parent = parent->GetParent();
    }

    std::cout << std::endl;
}
