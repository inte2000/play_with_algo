#pragma once

#include "Searcher.h"
#include "Evaluator.h"

class NegamaxSearcher : public Searcher
{
public:
    NegamaxSearcher(Evaluator *evaluator);
    virtual ~NegamaxSearcher(void);

    virtual int SearchBestPlay(const GameState& state, int depth);

#ifdef _DEBUG
    int _searcherCounter;
#endif

protected:
    int EvaluateNegaMax(GameState& state, int max_player_id);
    //int NegaMax(CGameState& state, int depth);
    int NegaMax(GameState& state, int depth, int color, int max_player_id);

protected:
    Evaluator *m_evaluator;
};
