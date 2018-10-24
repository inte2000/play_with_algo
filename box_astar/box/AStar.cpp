#include "stdafx.h"
#include "AStar.h"


double ManhattanDistance(const ANODE& n1, const ANODE& n2)
{
    return (std::abs(n1.row - n2.row) + std::abs(n1.col - n2.col));
}

AStar::AStar(BoxGameMap *map, GameState *state)
{
    m_map = map;
    m_state = state;
}


AStar::~AStar()
{
}

bool AStar::FindPath(const MapPos& from, const MapPos& to, std::vector<MapPos>& path)
{
    ANODE source = { from.row, from.col, 0.0, 0.0, -1, -1 };
    ANODE target = { to.row, to.col, 0.0, 0.0, -1, -1 };

    //步骤(1)
    m_open.insert(source);

    //步骤(2)
    ANODE cur_node;
    while (ExtractMiniFromOpen(cur_node))
    {
        //graph->open.erase(cur_node);
        m_close.push_back(cur_node);
        if (cur_node == target)
        {
            GetPath(path);
            return true;
        }

        Direction dirs[] = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };
        //步骤(3)
        for (auto& dir : dirs)
        {
            ANODE nn = { cur_node.row + dir.row_offset, cur_node.col + dir.col_offset, 0.0, 0.0 };

            if ((nn.row >= 0) && (nn.row < m_map->GetRowCount()) && (nn.col >= 0) && (nn.col < m_map->GetColCount())
                && IsEmpty(nn.row, nn.col) && !IsNodeExistInClose(nn.row, nn.col))
            {
                std::multiset<ANODE, compare>::iterator it;
                it = find(m_open.begin(), m_open.end(), nn);
                if (it == m_open.end()) /*nn不在open列表*/
                {
                    nn.g = cur_node.g + 1; //将g始终赋值为0可得到BFS算法的效果
                    nn.h = ManhattanDistance(nn, target);
                    nn.prev_row = cur_node.row;
                    nn.prev_col = cur_node.col;
                    m_open.insert(nn);
                }
                else  /*nn在open列表中*/
                {
                    if ((cur_node.g + 1.0) < it->g)
                    {
                        nn = *it;
                        nn.g = cur_node.g + 1.0;
                        nn.prev_row = cur_node.row;
                        nn.prev_col = cur_node.col;
                        m_open.erase(it);
                        m_open.insert(nn);
                    }
                }
            }
        }
    }

    return false;
}

bool AStar::ExtractMiniFromOpen(ANODE& node)
{
    std::multiset<ANODE, compare>::iterator fin = m_open.begin();
    if (fin == m_open.end())
    {
        return false;
    }

    node = *fin;
    m_open.erase(fin);
    return true;
}

bool AStar::IsNodeExistInClose(int row, int col)
{
    std::vector<ANODE>::iterator it;
    for (it = m_close.begin(); it != m_close.end(); ++it)
    {
        if ((it->row == row) && (it->col == col))
        {
            return true;
        }
    }

    return false;
}

bool AStar::IsEmpty(int row, int col)
{
    if (m_map->IsWall(row, col))
        return false;

    if (m_state->IsBox(row, col))
        return false;

    return true;
}

void AStar::GetPath(std::vector<MapPos>& path)
{
    std::vector<ANODE>::reverse_iterator it = m_close.rbegin();
    int ri = it->row;
    int rj = it->col;
    while ((it != m_close.rend()) && (ri != -1) && (rj != -1))
    {
        if ((ri == it->row) && (rj == it->col))
        {
            //path.push_back({ it->i, it->j });
            path.insert(path.begin(), { it->row, it->col });
            ri = it->prev_row;
            rj = it->prev_col;
        }

        ++it;
    }
}
