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

bool EnterAndDrinkAtSaloon::OnMessage(Hunter * pHunter, const Telegram & msg)
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
		<< "Come and fight !";
}

bool DrunkAtSaloon::OnMessage(Hunter * pHunter, const Telegram & msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_CanYouMove:

		cout << "\nMessage handled by " << GetNameOfEntity(pHunter->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pHunter->ID())
			<< ": No !";

		pHunter->GetFSM()->ChangeState(FightAtSaloon::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

FightAtSaloon * FightAtSaloon::Instance()
{
	static FightAtSaloon instance;

	return &instance;
}

void FightAtSaloon::Enter(Hunter * pHunter)
{
	//if the Hunter is not already located at the saloon, he must
	//change location to the saloon
	if (pHunter->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Walkin' to the saloon";

		pHunter->ChangeLocation(saloon);
	}
}

void FightAtSaloon::Execute(Hunter * pHunter)
{
	//Now the hunter is drank in the saloon

	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Hit ya'";

	pHunter->AddToAlcoholQuantity(-5);
	pHunter->GetFSM()->ChangeState(EnterAndDrinkAtSaloon::Instance());
}

void FightAtSaloon::Exit(Hunter * pHunter)
{
	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": "
		<< "More beverage pls !";
}

bool FightAtSaloon::OnMessage(Hunter * pHunter, const Telegram & msg)
{
	return false;
}
