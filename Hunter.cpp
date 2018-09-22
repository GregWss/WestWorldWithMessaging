#include "Hunter.h"

bool Hunter::HandleMessage(const Telegram& msg)
{
	return h_pStateMachine->HandleMessage(msg);
}


void Hunter::Update()
{
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	h_pStateMachine->Update();
}

void Hunter::AddToAlcoholQuantity(const int val)
{
	h_alcohol += val;

	if (h_alcohol < 0) h_alcohol = 0;
}

bool Hunter::Drank()const
{
	if (h_alcohol >= AlcoholThreshold)
	{
		return true;
	}

	return false;
}

void Hunter::h_AddToHealth(int val) {
	if (this->h_health + val <= Health)
		this->h_health += val;
}

void Hunter::h_Punch(int val)
{
	this->h_health -= val;
}

bool Hunter::h_Hurt()const
{
	if (h_health <= 0) 
		return true;
	else 
		return false;
}