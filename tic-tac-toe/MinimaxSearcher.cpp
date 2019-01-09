#include "StdAfx.h"
#include "MinimaxSearcher.h"

MinimaxSearcher::MinimaxSearcher(Evaluator *evaluator)
{
#ifdef _DEBUG
    _searcherCounter = 0;
#endif
    m_evaluator = evaluator;
}

MinimaxSearcher::~MinimaxSearcher(void)
{
}

int MinimaxSearcher::SearchBestPlay(const GameState& state, int depth)
{
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
            tryState.SetGameCell(i, max_player_id); //假设当前玩家在此位置落子
            tryState.SwitchPlayer();
            int value = MiniMax(tryState, depth - 1, max_player_id);
            if(value >= bestValue)
            {
                bestValue = value;
                bestPos = i;
            }
        }
    }

#ifdef _DEBUG
    std::cout << "MinimaxSearcher " << _searcherCounter << " (without Alpha-Beta)" << std::endl;
#endif

    return bestPos;
}

int MinimaxSearcher::MiniMax(GameState& state, int depth, int max_player_id)
{
    if(state.IsGameOver() || (depth == 0))
    {
#ifdef _DEBUG
        _searcherCounter++;
#endif
        return m_evaluator->Evaluate(state, max_player_id);
    }
    
    int current_player = state.GetCurrentPlayer();
    int score = (current_player == max_player_id) ? -GAME_INF : GAME_INF;
    for(int i = 0; i < BOARD_CELLS; i++)
    {
        if(state.IsEmptyCell(i))/*此位置可以落子*/
        {
            state.SetGameCell(i, state.GetCurrentPlayer());
            state.SwitchPlayer();
            int value = MiniMax(state, depth - 1, max_player_id);
            state.SwitchPlayer(); //恢复递归搜索之前的状态
            state.ClearGameCell(i);
            if(current_player == max_player_id)
            {
                score = std::max(score, value);
            }
            else
            {
                score = std::min(score, value);
            }
        }
    }
    
    return score;
}
#if 0
int CMinimaxSearcher::MiniMax(CGameState& state, int depth)
{
    if(state.IsGameOver())
        return state.Evaluate();
    if(depth == 0)
        return state.Evaluate();
    
    int bestValue[BOARD_CELLS] = { 0 };
    int best = 0;
    if(state.IsComputerPlayer())
        bestValue[best] = -GAME_INF;
    else
        bestValue[best] = GAME_INF;

    CGameState tryState = state;
    int i;
    for(i = 0; i < BOARD_CELLS; i++)
    {
        if(tryState.IsEmptyCell(i))
        {
            tryState.SetGameCell(i, tryState.GetPlayerRole());
            tryState.SwitchPlayer();
            int value = MiniMax(tryState, depth - 1);
            tryState.SwitchPlayer();
            tryState.SetGameCell(i, CELL_EMPTY);
            
            if(state.IsComputerPlayer())
            {
                if(value > bestValue[best])
                {
                    best = 0;
                    bestValue[best] = value;
                }
                else if(value == bestValue[best])
                {
                    best++;
                    bestValue[best] = value;
                }
            }
            else
            {
                if(value < bestValue[best])
                {
                    best = 0;
                    bestValue[best] = value;
                }
                else if(value == bestValue[best])
                {
                    best++;
                    bestValue[best] = value;
                }
            }
        }
    }
    if(best > 0)
        best = rand() % best;
    
    return bestValue[best];
}
#endif