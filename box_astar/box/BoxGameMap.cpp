#include "stdafx.h"
#include "BoxGameMap.h"



BoxGameMap::BoxGameMap()
{
    memset(m_map, ' ', MAX_MAP_ROW*MAX_MAP_COL);
    m_rowCount = 0;
    m_colCount = 0;
}

BoxGameMap::BoxGameMap(char *map, int row, int col)
{
    assert((row >= 0) && (row < MAX_MAP_ROW));
    assert((col >= 0) && (col < MAX_MAP_COL));

    Init(map, row, col);
}


BoxGameMap::~BoxGameMap()
{
}

void BoxGameMap::PrintMap()
{
    for (int i = 0; i < m_rowCount; i++)
    {
        for (int j = 0; j < m_colCount; j++)
        {
            if (m_map[i][j].isDead)
            {
                std::cout << 'O' << ", ";
            }
            else
            {
                std::cout << m_map[i][j].value << ", ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

bool BoxGameMap::Init(char *map, int row, int col)
{
    m_rowCount = row;
    m_colCount = col;
    char *pos = map;
    for (int i = 0; i < m_rowCount; i++)
    {
        for (int j = 0; j < m_colCount; j++)
        {
            m_map[i][j].value = *pos++;
            m_map[i][j].isDest = (m_map[i][j].value == MAP_V_DEST);
            m_map[i][j].isDead = false;
        }
    }

    ProcessDead();
    return true;
}

void BoxGameMap::ProcessDead()
{
    for (int i = 0; i < m_rowCount; i++)
    {
        for (int j = 0; j < m_colCount; j++)
        {
            //是空位置，并且不是目标点的情况，需要判断是否是死亡点
            if (!m_map[i][j].isDest && (m_map[i][j].value == MAP_V_SPACE))
            {
                m_map[i][j].isDead = IsDeadPos(i, j);
            }
            else
            {
                m_map[i][j].isDead = false;
            }
        }
    }
}

bool BoxGameMap::IsDeadPos(int row, int col)
{
    Direction dirs[] = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };
    bool isCorner = false;
    for (auto& dir : dirs)
    {
        MapPos newPos = { row + dir.row_offset, col + dir.col_offset };
        
        if (m_map[newPos.row][newPos.col].value == MAP_V_BOARD)
        {
            if (isCorner)
            {
                return true; //已经连续两个方向是墙了，说明是个corner
            }
            
            isCorner = true;
            if (dir.col_offset == 0) //沿行方向找墙
            {
                int col_s, col_e;
                if (GetRowWall(newPos.row, newPos.col, col_s, col_e))
                {
                    if (!IsRowHasDestPos(row, col_s, col_e))
                        return true;
                }
            }
            else //否则沿着列方向找墙
            {
                int row_s, row_e;
                if (GetColWall(newPos.row, newPos.col, row_s, row_e))
                {
                    if (!IsColHasDestPos(col, row_s, row_e))
                        return true;
                }
            }

        }
        else
        {
            isCorner = false; //这个方向不是墙，将标记清除
        }
    }

    return false;
}

bool BoxGameMap::GetRowWall(int row, int col, int& cs, int& ce)
{
    cs = col;
    while (m_map[row][cs].value == MAP_V_BOARD)
    {
        if (cs == 0)
            break;

        cs--;
    }
    if ((cs > 0) && (m_map[row][cs].value != MAP_V_OUT))
        return false;

    ce = col;
    while (m_map[row][cs].value == MAP_V_BOARD)
    {
        if (ce == (m_colCount - 1))
            break;
        
        ce++;
    }

    if ((ce < (m_colCount - 1)) && (m_map[row][cs].value != MAP_V_OUT))
        return false;

    return true;
}

bool BoxGameMap::IsRowHasDestPos(int row, int cs, int ce)
{
    for (int col = cs; col <= ce; col++)
    {
        if (m_map[row][col].isDest)
            return true;
    }

    return false;
}

bool BoxGameMap::GetColWall(int row, int col, int& rs, int& re)
{
    rs = row;
    while (m_map[rs][col].value == MAP_V_BOARD)
    {
        if (rs == 0)
            break;

        rs--;
    }
    if ((rs > 0) && (m_map[rs][col].value != MAP_V_OUT))
        return false;

    re = row;
    while (m_map[re][col].value == MAP_V_BOARD)
    {
        if (re == (m_rowCount - 1))
            break;

        re++;
    }

    if ((re < (m_rowCount - 1)) && (m_map[re][col].value != MAP_V_OUT))
        return false;

    return true;
}

bool BoxGameMap::IsColHasDestPos(int col, int rs, int re)
{
    for (int row = rs; row <= re; row++)
    {
        if (m_map[row][col].isDest)
            return true;
    }

    return false;
}
