#include "StdAfx.h"
#include "AlphaBetaSearcher.h"

AlphaBetaSearcher::AlphaBetaSearcher(Evaluator *evaluator)
{
#ifdef _DEBUG
    _searcherCounter = 0;
#endif
    m_evaluator = evaluator;
}

AlphaBetaSearcher::~AlphaBetaSearcher(void)
{
}

int AlphaBetaSearcher::SearchBestPlay(const GameState& state, int depth)
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
            int value = AlphaBeta(tryState, depth - 1, -GAME_INF, GAME_INF, max_player_id);
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
    std::cout << "MinimaxSearcher " << _searcherCounter << " (with Alpha-Beta)" << std::endl;
#endif

    return bestCell[bestPos];
}

int AlphaBetaSearcher::AlphaBeta(GameState& state, int depth, int alpha, int beta, int max_player_id)
{
    if(state.IsGameOver() || (depth == 0))
    {
#ifdef _DEBUG
        _searcherCounter++;
#endif
        return m_evaluator->Evaluate(state, max_player_id);
    }
    
    if(state.GetCurrentPlayer() == max_player_id) /*极大值节点*/
    {
        for(int i = 0; i < BOARD_CELLS; i++)
        {
            if(state.IsEmptyCell(i))
            {
                state.SetGameCell(i, state.GetCurrentPlayer());
                state.SwitchPlayer();
                int value = AlphaBeta(state, depth - 1, alpha, beta, max_player_id);
                alpha = std::max(alpha, value);
                state.SwitchPlayer();
                state.ClearGameCell(i);
                if(beta <= alpha)/*beta 剪枝*/
                    break;
            }
        }

        return alpha;
    }
    else
    {
        for(int i = 0; i < BOARD_CELLS; i++)
        {
            if(state.IsEmptyCell(i))
            {
                state.SetGameCell(i, state.GetCurrentPlayer());
                state.SwitchPlayer();
                int value = AlphaBeta(state, depth - 1, alpha, beta, max_player_id);
                state.SwitchPlayer();
                state.ClearGameCell(i);
                beta = std::min(beta, value);
                if(beta <= alpha)/*alpha 剪枝*/
                    break;
            }
        }
        
        return beta;
    }
}


#if 0
int AlphaBetaSearcher::AlphaBeta(GameState& state, int depth, int alpha, int beta, int max_player_id)
{
    if (state.IsGameOver() || (depth == 0))
    {
#ifdef _DEBUG
        _searcherCounter++;
#endif
        return m_evaluator->Evaluate(state, max_player_id);
    }

    if (state.GetCurrentPlayer() == max_player_id) /*极大值节点*/
    {
        for (int i = 0; i < BOARD_CELLS; i++)
        {
            GameState tryState = state;
            if (tryState.IsEmptyCell(i))
            {
                tryState.SetGameCell(i, tryState.GetCurrentPlayer());
                tryState.SwitchPlayer();
                int value = AlphaBeta(tryState, depth - 1, alpha, beta, max_player_id);
                alpha = std::max(alpha, value);
                if (beta <= alpha)/*beta 剪枝*/
                    break;
            }
        }

        return alpha;
    }
    else
    {
        for (int i = 0; i < BOARD_CELLS; i++)
        {
            GameState tryState = state;
            if (tryState.IsEmptyCell(i))
            {
                tryState.SetGameCell(i, tryState.GetCurrentPlayer());
                tryState.SwitchPlayer();
                int value = AlphaBeta(tryState, depth - 1, alpha, beta, max_player_id);
                beta = std::min(beta, value);
                if (beta <= alpha)/*alpha 剪枝*/
                    break;
            }
        }

        return beta;
    }
}
#endif