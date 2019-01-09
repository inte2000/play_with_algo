#pragma once

#include "Searcher.h"
#include "Evaluator.h"

class NegamaxAlphaBetaSearcher : public Searcher
{
public:
    NegamaxAlphaBetaSearcher(Evaluator *evaluator);
    virtual ~NegamaxAlphaBetaSearcher(void);

    virtual int SearchBestPlay(const GameState& state, int depth);

#ifdef _DEBUG
    int _searcherCounter;
#endif

protected:
    int EvaluateNegaMax(GameState& state, int max_player_id);
    int NegaMax(GameState& state, int depth, int alpha, int beta, int max_player_id);

protected:
    Evaluator *m_evaluator;
};
