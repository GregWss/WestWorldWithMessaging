#include "HunterOwnedStates.h"
#include "fsm/State.h"
#include "Miner.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;


#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

EnterAndDrinkAtSaloon * EnterAndDrinkAtSaloon::Instance()
{
	return nullptr;
}

void EnterAndDrinkAtSaloon::Enter(Hunter * hunter)
{
}

void EnterAndDrinkAtSaloon::Execute(Hunter * Hunter)
{
}

void EnterAndDrinkAtSaloon::Exit(Hunter * Hunter)
{
}

bool EnterAndDrinkAtSaloon::OnMessage(Hunter * agent, const Telegram & msg)
{
	return false;
}

DrunkAtSaloon * DrunkAtSaloon::Instance()
{
	return nullptr;
}

void DrunkAtSaloon::Enter(Hunter * hunter)
{
}

void DrunkAtSaloon::Execute(Hunter * Hunter)
{
}

void DrunkAtSaloon::Exit(Hunter * Hunter)
{
}

bool DrunkAtSaloon::OnMessage(Hunter * agent, const Telegram & msg)
{
	return false;
}

FightAtSaloon * FightAtSaloon::Instance()
{
	return nullptr;
}

void FightAtSaloon::Enter(Hunter * hunter)
{
}

void FightAtSaloon::Execute(Hunter * Hunter)
{
}

void FightAtSaloon::Exit(Hunter * Hunter)
{
}

bool FightAtSaloon::OnMessage(Hunter * agent, const Telegram & msg)
{
	return false;
}
