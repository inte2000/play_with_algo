// bucket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <string>
#include <deque>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <cassert>


enum class LOCATION
{
    LEFT,
    RIGHT
};

enum class ACTION
{
    GO_SELF,
    GO_WITH_WOLF,
    GO_WITH_SHEEP,
    GO_WITH_VEGETABLE,
    BACK_SELF,
    BACK_WITH_WOLF,
    BACK_WITH_SHEEP,
    BACK_WITH_VEGETABLE,
    INVALID,
};

struct ItemState
{
  ItemState();
  bool IsSameState(const ItemState& state) const;
  void PrintStates();
  bool IsFinalState();

  LOCATION farmer,wolf,sheep,vegetable;
  ACTION curAction;
};


struct ActionProcess
{
    ACTION  act_name;
    std::function<bool(const ItemState& current, ItemState& next)>  TakeAction;
};

std::map<LOCATION, std::string> locationMap = {
    { LOCATION::LEFT ,         "Left" },
    { LOCATION::RIGHT ,        "Right" }
};

std::map<ACTION, std::string> actMsgMap = {
    { ACTION::GO_SELF ,             "Farmer go over the river" },
    { ACTION::GO_WITH_WOLF ,        "Farmer take wolf go over the river" },
    { ACTION::GO_WITH_SHEEP ,       "Farmer take sheep go over the river" },
    { ACTION::GO_WITH_VEGETABLE ,   "Farmer take vegetable go over the river" },
    { ACTION::BACK_SELF ,                "Farmer go back" },
    { ACTION::BACK_WITH_WOLF ,      "Farmer take wolf go back" },
    { ACTION::BACK_WITH_SHEEP ,     "Farmer take sheep go back" },
    { ACTION::BACK_WITH_VEGETABLE , "Farmer take vegetable go back" },
    { ACTION::INVALID , "" }
};

ItemState::ItemState()
{
    farmer = LOCATION::LEFT;
    wolf = LOCATION::LEFT;
    sheep = LOCATION::LEFT;
    vegetable = LOCATION::LEFT;
    curAction = ACTION::INVALID;
}


bool ItemState::IsSameState(const ItemState& state) const
{
    return ( (farmer == state.farmer) 
             && (wolf == state.wolf) 
             && (sheep == state.sheep) 
             && (vegetable == state.vegetable) );
}


void ItemState::PrintStates()
{
    std::cout << actMsgMap[curAction] << "  ";
    std::cout << ": " << "framer " <<locationMap[farmer] << 
                                          ", wolf " << locationMap[wolf] << 
                                          ", sheep " << locationMap[sheep] << 
                                          ", vegetable " << locationMap[vegetable] << std::endl;
}

bool ItemState::IsFinalState()
{
    return ( (farmer == LOCATION::RIGHT) 
             && (wolf == LOCATION::RIGHT) 
             && (sheep == LOCATION::RIGHT) 
             && (vegetable == LOCATION::RIGHT) );
}

bool IsProcessedState(deque<ItemState>& states, const ItemState& newState)
{
    auto it = find_if( states.begin(), states.end(),
        [&newState](ItemState& item) { return item.IsSameState(newState); });

    return (it != states.end());
}

void PrintResult(deque<ItemState>& states)
{
  cout << "Find Result : " << endl;
  for (auto& x : states)
  {
      x.PrintStates();
  }
  cout << endl << endl;
}

bool IsCurrentStateValid(const ItemState& current)
{
    if ((current.wolf == current.sheep) && (current.sheep != current.farmer))
    {
        return false;
    }

    if ((current.vegetable == current.sheep) && (current.sheep != current.farmer))
    {
        return false;
    }

    return true;
}

bool ProcessFarmerGo(const ItemState& current, ItemState& next)
{
    if(current.farmer != LOCATION::LEFT)
        return false;

    next = current;

    next.farmer    = LOCATION::RIGHT;
    next.curAction = ACTION::GO_SELF;

    return IsCurrentStateValid(next);
}

bool ProcessFarmerGoTakeWolf(const ItemState& current, ItemState& next)
{
    if((current.farmer != LOCATION::LEFT) || (current.wolf != LOCATION::LEFT))
        return false;

    next = current;

    next.farmer    = LOCATION::RIGHT;
    next.wolf      = LOCATION::RIGHT;
    next.curAction = ACTION::GO_WITH_WOLF;

    return IsCurrentStateValid(next);
}

bool ProcessFarmerGoTakeSheep(const ItemState& current, ItemState& next)
{
    if((current.farmer != LOCATION::LEFT) || (current.sheep != LOCATION::LEFT))
        return false;

    next = current;

    next.farmer    = LOCATION::RIGHT;
    next.sheep     = LOCATION::RIGHT;
    next.curAction = ACTION::GO_WITH_SHEEP;

    return IsCurrentStateValid(next);
}

bool ProcessFarmerGoTakeVegetable(const ItemState& current, ItemState& next)
{
    if((current.farmer != LOCATION::LEFT) || (current.vegetable != LOCATION::LEFT))
        return false;

    next = current;

    next.farmer    = LOCATION::RIGHT;
    next.vegetable = LOCATION::RIGHT;
    next.curAction = ACTION::GO_WITH_VEGETABLE;

    return IsCurrentStateValid(next);
}

bool ProcessFarmerBack(const ItemState& current, ItemState& next)
{
    if(current.farmer != LOCATION::RIGHT)
        return false;

    next = current;

    next.farmer    = LOCATION::LEFT;
    next.curAction = ACTION::BACK_SELF;

    return IsCurrentStateValid(next);
}

bool ProcessFarmerBackTakeWolf(const ItemState& current, ItemState& next)
{
    if((current.farmer != LOCATION::RIGHT) || (current.wolf != LOCATION::RIGHT))
        return false;

    next = current;

    next.farmer    = LOCATION::LEFT;
    next.wolf      = LOCATION::LEFT;
    next.curAction = ACTION::BACK_WITH_WOLF;

    return IsCurrentStateValid(next);
}

bool ProcessFarmerBackTakeSheep(const ItemState& current, ItemState& next)
{
    if((current.farmer != LOCATION::RIGHT) || (current.sheep != LOCATION::RIGHT))
        return false;

    next = current;

    next.farmer    = LOCATION::LEFT;
    next.sheep     = LOCATION::LEFT;
    next.curAction = ACTION::BACK_WITH_SHEEP;

    return IsCurrentStateValid(next);
}

bool ProcessFarmerBackTakeVegetable(const ItemState& current, ItemState& next)
{
    if((current.farmer != LOCATION::RIGHT) || (current.vegetable != LOCATION::RIGHT))
        return false;

    next = current;

    next.farmer    = LOCATION::LEFT;
    next.vegetable = LOCATION::LEFT;
    next.curAction = ACTION::BACK_WITH_VEGETABLE;

    return IsCurrentStateValid(next);
}

ActionProcess actMap[] = 
{
    { ACTION::GO_SELF,                ProcessFarmerGo                },
    { ACTION::GO_WITH_WOLF,           ProcessFarmerGoTakeWolf        },
    { ACTION::GO_WITH_SHEEP,          ProcessFarmerGoTakeSheep       },
    { ACTION::GO_WITH_VEGETABLE,      ProcessFarmerGoTakeVegetable   },
    { ACTION::BACK_SELF,              ProcessFarmerBack              },
    { ACTION::BACK_WITH_WOLF,         ProcessFarmerBackTakeWolf      },
    { ACTION::BACK_WITH_SHEEP,        ProcessFarmerBackTakeSheep     },
    { ACTION::BACK_WITH_VEGETABLE,    ProcessFarmerBackTakeVegetable }
};

void SearchStates(deque<ItemState>& states)
{
    ItemState current = states.back(); /*每次都从当前状态开始*/
    if(current.IsFinalState())
    {
        PrintResult(states);
        return;
    }

    ItemState next;
    for (auto& act : actMap)
    {
        if(act.TakeAction(current, next))
        {
            if(!IsProcessedState(states, next))
            {
              states.push_back(next);
              SearchStates(states);
              states.pop_back();
            }
        }
    }
}


int main(int argc, char* argv[])
{
    deque<ItemState> states;
    //ItemState init = { LOCATION::LEFT, LOCATION::LEFT, LOCATION::LEFT, LOCATION::LEFT };
    ItemState init;

    states.push_back(init);
    SearchStates(states);

    assert(states.size() == 1); /*穷举结束后states应该还是只有一个初始状态*/

    return 0;
}
