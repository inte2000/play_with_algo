#include "stdafx.h"
#include "GameState.h"
#include "BoxGameMap.h"



GameState::GameState(char *map, int row, int col)
{
    Init(map, row, col);
    m_parent = nullptr;
}

GameState::GameState(GameState *parent)
{
    m_man = parent->m_man;
    m_boxes = parent->m_boxes;
    m_action = parent->m_action;
    m_parent = parent;
}

GameState::~GameState()
{
}

void GameState::MoveMan(int row, int col, int row_offset, int col_offset)
{
    MapPos newPos = { row + row_offset, col + col_offset };
    for (auto& box : m_boxes)
    {
        if ((box.row == newPos.row) && (box.col == newPos.col))
        {
            box.row += row_offset;
            box.col += col_offset;
        }
    }

    m_action.push_x = row_offset;
    m_action.push_y = col_offset;
    m_man = newPos;
}

bool GameState::IsBox(int row, int col) const
{
    for (auto& box : m_boxes)
    {
        if ((box.row == row) && (box.col == col))
        {
            return true;
        }
    }

    return false;
}

bool GameState::IsSameState(GameState *state)
{
    if ((m_man.row != state->m_man.row) || (m_man.col != state->m_man.col))
        return false;

    if (m_boxes != state->m_boxes)
        return false;

    return true;
}

void GameState::Init(char *map, int row, int col)
{
    char *pos = map;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (*pos == MAP_V_MAN)
            {
                m_man = {i, j};
            }
            if(*pos == MAP_V_BOX)
            {
                m_boxes.push_back({i, j});
            }
            pos++;
        }
    }
}
