#pragma once

#include "Searcher.h"
#include "Evaluator.h"


class AlphaBetaSearcher : public Searcher
{
public:
    AlphaBetaSearcher(Evaluator *evaluator);
    virtual ~AlphaBetaSearcher(void);

    virtual int SearchBestPlay(const GameState& state, int depth);

#ifdef _DEBUG
    int _searcherCounter;
#endif

protected:
    int AlphaBeta(GameState& state, int depth, int alpha, int beta, int max_player_id);

protected:
    Evaluator *m_evaluator;
};
