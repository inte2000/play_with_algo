#pragma once

#include "BoxGameMap.h"
#include "GameState.h"

struct ANODE
{
    bool operator== (const ANODE& n) const
    {
        if ((row == n.row) && (col == n.col))
        {
            return true;
        }

        return false;
    }
    int row;
    int col;
    double g;
    double h;
    int prev_row;
    int prev_col;
};

struct compare
{
    bool operator()(const ANODE& n1, const ANODE& n2) const
    {
        double f1 = n1.g + n1.h;
        double f2 = n2.g + n2.h;

        return (f1 < f2);
    }
};


class AStar
{
public:
    AStar(BoxGameMap *map, GameState *state);
    ~AStar();

    bool FindPath(const MapPos& from, const MapPos& to, std::vector<MapPos>& path);

protected:
    bool ExtractMiniFromOpen(ANODE& node);
    bool IsNodeExistInClose(int row, int col);
    bool IsEmpty(int row, int col);
    void GetPath(std::vector<MapPos>& path);

protected:
    BoxGameMap *m_map;
    GameState *m_state;
    std::multiset<ANODE, compare> m_open;
    std::vector<ANODE> m_close;
};
