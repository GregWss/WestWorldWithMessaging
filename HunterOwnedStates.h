#ifndef HUNTER_OWNED_STATES_H
#define HUNTER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Name:   HunterOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Hunter class.
//
//  Author: Baptiste ROUPAIN & Grégory WEISS
//
//------------------------------------------------------------------------
#include "fsm/State.h"


class Hunter;
struct Telegram;

//------------------------------------------------------------------------
//
//  In this state the hunter will drink at the saloon
//------------------------------------------------------------------------
class EnterAndDrinkAtSaloon : public State<Hunter>
{
private:

	EnterAndDrinkAtSaloon() {}

	//copy ctor and assignment should be private
	EnterAndDrinkAtSaloon(const EnterAndDrinkAtSaloon&);
	EnterAndDrinkAtSaloon& operator=(const EnterAndDrinkAtSaloon&);

public:

	//this is a singleton
	static EnterAndDrinkAtSaloon* Instance();

	virtual void Enter(Hunter* pHunter);

	virtual void Execute(Hunter* pHunter);

	virtual void Exit(Hunter* pHunter);

	virtual bool OnMessage(Hunter* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  In this state the hunter is drunk and will be ready to start
//  a fight
//------------------------------------------------------------------------
class DrunkAtSaloon : public State<Hunter>
{
private:

	DrunkAtSaloon() {}

	//copy ctor and assignment should be private
	DrunkAtSaloon(const DrunkAtSaloon&);
	DrunkAtSaloon& operator=(const DrunkAtSaloon&);

public:

	//this is a singleton
	static DrunkAtSaloon* Instance();

	virtual void Enter(Hunter* pHunter);

	virtual void Execute(Hunter* pHunter);

	virtual void Exit(Hunter* pHunter);

	virtual bool OnMessage(Hunter* agent, const Telegram& msg);

};

//------------------------------------------------------------------------
//
//  In this state the hunter will be fighting
//------------------------------------------------------------------------
class FightAtSaloon : public State<Hunter>
{
private:

	FightAtSaloon() {}

	//copy ctor and assignment should be private
	FightAtSaloon(const FightAtSaloon&);
	FightAtSaloon& operator=(const FightAtSaloon&);

public:

	//this is a singleton
	static FightAtSaloon* Instance();

	virtual void Enter(Hunter* pHunter);

	virtual void Execute(Hunter* pHunter);

	virtual void Exit(Hunter* pHunter);

	virtual bool OnMessage(Hunter* agent, const Telegram& msg);

};


#endif