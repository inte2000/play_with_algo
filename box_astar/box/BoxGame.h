#pragma once

#include "BoxGameMap.h"
#include "GameState.h"

class BoxGame
{
public:
    BoxGame()
    {
        m_map = nullptr;
        m_result = 0;
    }
    ~BoxGame()
    {
        if (m_map != nullptr)
        {
            delete m_map;
        }
    }

    bool InitMap(char *map, int row, int col);
    bool ResolveGame();

protected:
    bool CanPushBox(GameState *state, const MapPos& man, int row_offset, int col_offset);

    void SearchNewGameStates(GameState *state);
    void MoveToNewState(GameState *parent, const MapPos& man, std::vector<MapPos>& path, const Direction& push);
    bool IsFinalState(const GameState *state);
    bool AddNewState(GameState *state);
    void PrintMoveRecords(GameState *state);
protected:
    BoxGameMap *m_map;
    std::vector<GameState *> m_states;
    int m_result;
};

