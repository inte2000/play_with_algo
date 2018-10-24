#pragma once


const int MAX_MAP_ROW = 16;
const int MAX_MAP_COL = 16;

const char MAP_V_OUT = 'A';
const char MAP_V_BOARD = 'X';
const char MAP_V_BOX = 'B';
const char MAP_V_DEST = '#';
const char MAP_V_SPACE = ' ';
const char MAP_V_MAN = '@';
/*
const char N_MASK_DEAD = 0x02;
const char N_MASK_DEST = 0x04;
const char N_MASK_DEST = 0x04;
*/
struct MapNode
{
    char value;   //'X'、'O'或' '
    bool isDead;  //是否是死亡点
    bool isDest;  //是否是目标点
};

struct MapPos
{
    int row;
    int col;
};

struct Direction
{
    int row_offset;
    int col_offset;
};

inline bool operator == (const MapPos& pos1, const MapPos& pos2)
{
    return ((pos1.row == pos2.row) && (pos1.col == pos2.col));
}

class BoxGameMap
{
public:
    BoxGameMap();
    BoxGameMap(char *map, int row, int col);
    ~BoxGameMap();

    bool IsWall(int row, int col) { return (m_map[row][col].value == MAP_V_BOARD); }
    MapNode& Get(int row, int col)
    {
        assert((row >= 0) && (row < m_rowCount));
        assert((col >= 0) && (col < m_colCount));
        return m_map[row][col];
    }
    const MapNode& Get(int row, int col) const
    {
        assert((row >= 0) && (row < m_rowCount));
        assert((col >= 0) && (col < m_colCount));
        return m_map[row][col];
    }
    void Set(int row, int col, const MapNode& value)
    {
        assert((row >= 0) && (row < m_rowCount));
        assert((col >= 0) && (col < m_colCount));
        m_map[row][col] = value;
    }
    int GetRowCount() { return m_rowCount; }
    int GetColCount() { return m_colCount; }
    void PrintMap();
protected:
    bool Init(char *map, int row, int col);
    void ProcessDead();
    bool IsDeadPos(int row, int col);
    bool GetRowWall(int row, int col, int& cs, int& ce);
    bool IsRowHasDestPos(int row, int cs, int ce);
    bool GetColWall(int row, int col, int& rs, int& re);
    bool IsColHasDestPos(int col, int rs, int re);
protected:
    int m_rowCount;   //地图的实际行数
    int m_colCount;   //地图的实际行数
    MapNode m_map[MAX_MAP_ROW][MAX_MAP_COL];   //简化数据模型，使用定长的二维数组
};

