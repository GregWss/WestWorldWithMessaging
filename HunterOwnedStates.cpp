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

		pHunter->GetFSM()->ChangeState(FightAtSaloonH::Instance());

		return true;

	}//end switch

	return false; //send message to global message handler
}

FightAtSaloonH * FightAtSaloonH::Instance()
{
	static FightAtSaloonH instance;

	return &instance;
}

void FightAtSaloonH::Enter(Hunter * pHunter)
{
	//if the Hunter is not already located at the saloon, he must
	//change location to the saloon
	if (pHunter->Location() != saloon)
	{
		cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Walkin' to the saloon";

		pHunter->ChangeLocation(saloon);
	}
}

void FightAtSaloonH::Execute(Hunter * pHunter)
{
	//Now the hunter is drank in the saloon
	if(pHunter->h_Hurt()) {
		cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "I'm hurt !'";
		// we send the message of hurt to miner
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
		pHunter->ID(),        //ID of sender
		ent_Miner_Bob,            //ID of recipient
		Msg_KnockOut,   //the message
		NO_ADDITIONAL_INFO);
		pHunter->AddToAlcoholQuantity(-5);
		pHunter->GetFSM()->ChangeState(HealHimself::Instance());
	}else {	
		float punch_probability = rand() % 100;
		if (punch_probability < 80) {
			cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Hit ya'";
			// we send the message of hit to miner
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pHunter->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_Hit,   //the message
			NO_ADDITIONAL_INFO);
		}else{
			// we send the message of miss to miner
			cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "Miss ya'";
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			pHunter->ID(),        //ID of sender
			ent_Miner_Bob,            //ID of recipient
			Msg_Miss,   //the message
			NO_ADDITIONAL_INFO);
		}
	}
}

void FightAtSaloonH::Exit(Hunter * pHunter)
{
	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": "
		<< "More beverage pls !";
}

bool FightAtSaloonH::OnMessage(Hunter * pHunter, const Telegram & msg)
{
	SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_Hit:
		cout << "\nMessage handled by " << GetNameOfEntity(pHunter->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pHunter->ID())
			<< ": Aouch !";

	  pHunter->h_Punch(1);

		return true;

  case Msg_Miss:
  		cout << "\nMessage handled by " << GetNameOfEntity(pHunter->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pHunter->ID())
			<< ": Chiure démoniaque !";
		
    return true;

  case Msg_KnockOut:
  		cout << "\nMessage handled by " << GetNameOfEntity(pHunter->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(pHunter->ID())
			<< ": Je chie dans la pute qui t'a mise au monde !";
		
    pHunter->GetFSM()->ChangeState(EnterAndDrinkAtSaloon::Instance());
    return true;

	}//end switch

	return false; //send message to global message handler
}


///////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////
HealHimself * HealHimself::Instance()
{
	static HealHimself instance;

	return &instance;
}

void HealHimself::Enter(Hunter * pHunter)
{
	//The hunter is going to heal himself
	if (pHunter->Location() != hospital)
	{
		cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "It hurts ! Going to Hospital";
		pHunter->ChangeLocation(hospital);
	}
}

void HealHimself::Execute(Hunter * pHunter)
{
	//The hunter recover
	pHunter->h_AddToHealth(3);
	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": " << "I feel much better !";
	pHunter->GetFSM()->ChangeState(EnterAndDrinkAtSaloon::Instance());
}


void HealHimself::Exit(Hunter * pHunter)
{
	cout << "\n" << GetNameOfEntity(pHunter->ID()) << ": "
		<< "Going back to the bar !";
}

bool HealHimself::OnMessage(Hunter * pHunter, const Telegram & msg)
{
	return false;
}
