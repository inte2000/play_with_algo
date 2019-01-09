// tic-tac-toe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameControl.h"
#include "GameState.h"
#include "MinimaxSearcher.h"
#include "NegamaxSearcher.h"
#include "AlphaBetaSearcher.h"
#include "NegamaxAlphaBetaSearcher.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "WzEvaluator.h"
#include "FeEvaluator.h"

const int SEARCH_DEPTH = 6;

#if 0
int main(int argc, char* argv[])
{
    WzEvaluator wzFunc;
    FeEvaluator feFunc; //这个强一点

    MinimaxSearcher ms(&feFunc);
    AlphaBetaSearcher abs(&feFunc);
    NegamaxSearcher ns(&wzFunc);
    NegamaxAlphaBetaSearcher nabs(&feFunc);

    ComputerPlayer computer("DELL 7577");
    computer.SetSearcher(&abs, SEARCH_DEPTH);

    ComputerPlayer computer1("KA47");
    computer1.SetSearcher(&nabs, SEARCH_DEPTH);

    GameControl gc;
    gc.SetPlayer(&computer, PLAYER_A);
    gc.SetPlayer(&computer1, PLAYER_B);
    
    int play1win = 0;
    int play2win = 0;
    int draw = 0;
    for (int i = 0; i < 100; i++)
    {
        GameState init_state;
        init_state.InitGameState(PLAYER_A);
        gc.InitGameState(init_state);
        int winner = gc.Run();
        if (winner == PLAYER_A)
        {
            play1win++;
        }
        else if (winner == PLAYER_B)
        {
            play2win++;
        }
        else
        {
            draw++;
        }
    }

    return 0;
}
#endif

int main(int argc, char* argv[])
{
    WzEvaluator wzFunc;
    FeEvaluator feFunc; //这个强一点

    MinimaxSearcher ms(&feFunc);
    AlphaBetaSearcher abs(&feFunc);
    NegamaxSearcher ns(&feFunc);
    NegamaxAlphaBetaSearcher nabs(&feFunc);

    HumanPlayer human("张三");

    ComputerPlayer computer("DELL 7577");
    computer.SetSearcher(&ms, SEARCH_DEPTH);

    //ComputerPlayer computer1("KA47");
    //computer1.SetSearcher(&nabs, SEARCH_DEPTH);

    GameState init_state;
    init_state.InitGameState(PLAYER_A);
    /*
    //预设一些状态，比如残局
    init_state.SetGameCell(0, PLAYER_A);
    init_state.SetGameCell(1, PLAYER_B);
    init_state.SetGameCell(3, PLAYER_B);
    init_state.SetGameCell(4, PLAYER_B);
    init_state.SetGameCell(5, PLAYER_A);
    init_state.SetGameCell(6, PLAYER_A);
    */
    /*
    //预设一些状态，比如残局
    init_state.SetGameCell(0, PLAYER_B);
    init_state.SetGameCell(3, PLAYER_B);
    init_state.SetGameCell(4, PLAYER_A);
    init_state.SetGameCell(5, PLAYER_A);
    init_state.SetGameCell(6, PLAYER_A);
    init_state.SetGameCell(8, PLAYER_B);
    */
    GameControl gc;
    gc.SetPlayer(&computer, PLAYER_A);
    gc.SetPlayer(&human, PLAYER_B);
    //gc.SetPlayer(&computer1, PLAYER_B);
    gc.InitGameState(init_state);
    int winner = gc.Run();

    if (winner == PLAYER_NULL)
    {
        std::cout << "GameOver, Draw!" << std::endl;
    }
    else
    {
        Player *winnerPlayer = gc.GetPlayer(winner);
        std::cout << "GameOver, " << winnerPlayer->GetPlayerName() << " Win!" << std::endl;
    }

    std::cin.clear();
    std::cin.ignore();
    std::cin.get();

    return 0;
}
