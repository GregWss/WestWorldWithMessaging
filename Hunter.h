#ifndef HUNTER_H
#define HUNTER_H
//------------------------------------------------------------------------
//
//  Name:   Hunter.h
//
//  Desc:   A class defining a hunter who like to fight.
//
//  Author: Baptiste ROUPAIN & Grégory WEISS
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "BaseGameEntity.h"
#include "Locations.h"
#include "misc/ConsoleUtils.h"
#include "HunterOwnedStates.h"
#include "fsm/StateMachine.h"

template <class entity_type> class State;
struct Telegram;

//the amount of alcohol before the hunter is drank and ready to fight
const int AlcoholThreshold = 5;
//max health of the hunter
const int Health = 3;

class Hunter : public BaseGameEntity
{
private:

	//an instance of the state machine class
	StateMachine<Hunter>*  h_pStateMachine;

	location_type         h_Location;

	//amount of alcohol the miner drank
	int                   h_alcohol;

	//current health of the hunter
	int                   h_health;

public:

	Hunter(int id) :h_Location(saloon),
		h_alcohol(0),
		h_health(3),
		BaseGameEntity(id)

	{
		//set up state machine
		h_pStateMachine = new StateMachine<Hunter>(this);

		h_pStateMachine->SetCurrentState(EnterAndDrinkAtSaloon::Instance());
		// GoHomeAndSleepTilRested pour le chasseur sera d�finie dans HunterOwnedStates

		/* NOTE, A GLOBAL STATE HAS NOT BEEN IMPLEMENTED FOR THE MINER */
	}

	~Hunter() { delete h_pStateMachine; }

	//this must be implemented
	void Update();

	//so must this
	virtual bool  HandleMessage(const Telegram& msg);


	StateMachine<Hunter>* GetFSM()const { return h_pStateMachine; }



	//-------------------------------------------------------------accessors
	location_type Location()const { return h_Location; }
	void          ChangeLocation(location_type loc) { h_Location = loc; }

	//D�finir ici l'ensemble des m�thodes du hunter
	void 			Hunter::AddToAlcoholQuantity(const int val);
	bool 			Hunter::Drank()const;
	void	  	m_AddToHealth(int val);
	void			Hunter::h_Punch(int val);
  	bool			Hunter::h_Hurt()const;


};



#endif
