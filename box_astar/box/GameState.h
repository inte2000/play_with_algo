#pragma once

#include "BoxGameMap.h"

struct Action
{
    std::vector<MapPos> path;
    int push_x;
    int push_y;
};


class GameState
{
public:
    GameState(char *map, int row, int col);
    GameState(GameState *parent);
    ~GameState();

    const MapPos& GetMan() const { return m_man; }
    void SetActionPath(std::vector<MapPos>& path) { m_action.path = path; }
    const std::vector<MapPos>& GetActionPath() { return m_action.path; }
    void MoveMan(int row, int col, int row_offset, int col_offset);
    int GetBoxCount() const { return static_cast<int>(m_boxes.size()); }
    const MapPos& GetBox(int index) const { return m_boxes[index]; }
    GameState *GetParent() const { return m_parent; }
    bool IsBox(int row, int col) const;
    bool IsSameState(GameState *state);

protected:
    void Init(char *map, int row, int col);

protected:
    MapPos m_man;
    std::vector<MapPos> m_boxes;
    Action m_action;
    GameState *m_parent;
};

