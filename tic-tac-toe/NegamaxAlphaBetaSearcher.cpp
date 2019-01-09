#include "StdAfx.h"
#include "NegamaxAlphaBetaSearcher.h"

NegamaxAlphaBetaSearcher::NegamaxAlphaBetaSearcher(Evaluator *evaluator)
{
#ifdef _DEBUG
    _searcherCounter = 0;
#endif
    m_evaluator = evaluator;
}

NegamaxAlphaBetaSearcher::~NegamaxAlphaBetaSearcher(void)
{
}

int NegamaxAlphaBetaSearcher::SearchBestPlay(const GameState& state, int depth)
{
    std::vector<int> bestCell;
    int bestValue = -GAME_INF;
    int bestPos = 0;
#ifdef _DEBUG
    _searcherCounter = 0;
#endif

    int max_player_id = state.GetCurrentPlayer();
    for(int i = 0; i < BOARD_CELLS; i++)
    {
        GameState tryState = state;
        if(tryState.IsEmptyCell(i))
        {
            tryState.SetGameCell(i, max_player_id);
            tryState.SwitchPlayer();
            int value = -NegaMax(tryState, depth - 1, -GAME_INF, GAME_INF, max_player_id);
            if(value >= bestValue)
            {
                bestValue = value;
                bestCell.clear();
                bestCell.push_back(i);
            }
        }
    }

    if(bestCell.size() > 0)
        bestPos = rand() % bestCell.size();

#ifdef _DEBUG
    std::cout << "NegamaxSearcher " << _searcherCounter << " (with Alpha-Beta)" << std::endl;
#endif

    return bestCell[bestPos];
}

int NegamaxAlphaBetaSearcher::EvaluateNegaMax(GameState& state, int max_player_id)
{
    if(state.GetCurrentPlayer() == max_player_id)
        return m_evaluator->Evaluate(state, max_player_id);
    else
        return -m_evaluator->Evaluate(state, max_player_id);
}

int NegamaxAlphaBetaSearcher::NegaMax(GameState& state, int depth, int alpha, int beta, int max_player_id)
{
    if(state.IsGameOver() || (depth == 0))
    {
#ifdef _DEBUG
        _searcherCounter++;
#endif
        return EvaluateNegaMax(state, max_player_id);
    }
    
    int score = -GAME_INF;
    for(int i = 0; i < BOARD_CELLS; i++)
    {
        if(state.IsEmptyCell(i))
        {
            state.SetGameCell(i, state.GetCurrentPlayer());
            state.SwitchPlayer();
            int value = -NegaMax(state, depth - 1, -beta, -alpha, max_player_id);
            state.SwitchPlayer();
            state.ClearGameCell(i);
            score = std::max(score, value);
            alpha = std::max(alpha, value);
            if(beta <= alpha)
                break;
        }
    }
    
    return score;
}
