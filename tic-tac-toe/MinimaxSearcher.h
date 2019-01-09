#pragma once

#include "Searcher.h"
#include "Evaluator.h"

class MinimaxSearcher : public Searcher
{
public:
    MinimaxSearcher(Evaluator *evaluator);
    virtual ~MinimaxSearcher(void);

    virtual int SearchBestPlay(const GameState& state, int depth);

#ifdef _DEBUG
    int _searcherCounter;
#endif

protected:
    int MiniMax(GameState& state, int depth, int max_player_id);

protected:
    Evaluator *m_evaluator;
};
