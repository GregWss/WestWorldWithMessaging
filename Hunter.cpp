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