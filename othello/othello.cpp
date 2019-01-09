// othello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameControl.h"
#include "GameState.h"
#include "NegamaxAlphaBetaSearcher.h"
#include "ComputerPlayer.h"
#include "HumanPlayer.h"
#include "WzEvaluator.h"
#include "OdEvaluator.h"

const int SEARCH_DEPTH = 6;

int testState[GAME_CELLS] = 
{
    0,0,2,1,1,1,0,0,
    2,0,0,2,1,1,0,0,
    2,2,2,1,2,1,1,1,
    2,2,2,1,2,2,1,1,
    2,2,2,1,2,2,2,0,
    2,2,2,1,2,0,0,0,
    2,2,2,1,2,2,0,0,
    2,0,1,1,1,0,0,0
};

int main(int argc, char* argv[])
{
    NegamaxAlphaBetaSearcher nabs;

    HumanPlayer human("ÕÅÈý");
    //ComputerPlayer computer1("KA47");
    //computer1.SetSearcher(&nabs, 3);
    ComputerPlayer computer("DELL 7577");
    computer.SetSearcher(&nabs, SEARCH_DEPTH); 

    WzEvaluator wzEv;
    OdEvaluator odEv;
    GameState init_state;
    init_state.InitGameState(PLAYER_A);
    //init_state.SetGameState(testState, PLAYER_A);
    init_state.SetEvaluator(&wzEv);

    GameControl gc;
    gc.SetPlayer(&computer, PLAYER_A);
    gc.SetPlayer(&human, PLAYER_B);
    //gc.SetPlayer(&computer1, PLAYER_B);
    gc.InitGameState(init_state);
    gc.Run();

    return 0;
}
