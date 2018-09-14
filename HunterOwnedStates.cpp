#include "HunterOwnedStates.h"
#include "fsm/State.h"
#include "Hunter.h"
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

EnterAndDrinkAtSaloon* EnterAndDrinkAtSaloon::Instance()
{
	static EnterAndDrinkAtSaloon instance;

	return &instance;
}

void EnterAndDrinkAtSaloon::Enter(Hunter* pHunter)
{
	//if the Hunter is not already located at the saloon, he must
	//change location to the saloon
	if (pHunter->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Walkin' to the saloon";

		pHunter->ChangeLocation(saloon);
	}
}

void EnterAndDrinkAtSaloon::Execute(Hunter * pHunter)
{
	//Now the hunter is drining in the saloon
	pHunter->AddToAlcoholQuantity(1);

	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Drinkin' a good ol' whiskey";

	//if enough alcohol drunk, Hunter is drank
	if (pHunter->Drank())
	{
		pHunter->GetFSM()->ChangeState(DrunkAtSaloon::Instance());
	}
}

void EnterAndDrinkAtSaloon::Exit(Hunter * pHunter)
{
	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": "
		<< "Hmm tasty";
}

bool EnterAndDrinkAtSaloon::OnMessage(Hunter * agent, const Telegram & msg)
{
	return false;
}

DrunkAtSaloon * DrunkAtSaloon::Instance()
{
	static DrunkAtSaloon instance;

	return &instance;
}

void DrunkAtSaloon::Enter(Hunter * pHunter)
{
	//if the Hunter is not already located at the saloon, he must
	//change location to the saloon
	if (pHunter->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Walkin' to the saloon";

		pHunter->ChangeLocation(saloon);
	}
}

void DrunkAtSaloon::Execute(Hunter * pHunter)
{
	//Now the hunter is drank in the saloon

	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "I'm so drunk";
}

void DrunkAtSaloon::Exit(Hunter * pHunter)
{
	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": "
		<< "I'm so drunk";
}

bool DrunkAtSaloon::OnMessage(Hunter * agent, const Telegram & msg)
{
	return false;
}

FightAtSaloon * FightAtSaloon::Instance()
{
	return nullptr;
}

void FightAtSaloon::Enter(Hunter * pHunter)
{
}

void FightAtSaloon::Execute(Hunter * pHunter)
{
}

void FightAtSaloon::Exit(Hunter * pHunter)
{
}

bool FightAtSaloon::OnMessage(Hunter * agent, const Telegram & msg)
{
	return false;
}
