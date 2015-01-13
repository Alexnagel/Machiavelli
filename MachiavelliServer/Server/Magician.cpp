#include "Magician.h"


Magician::Magician() : PlayerCard("Magician")
{
}


Magician::~Magician()
{
}

std::string Magician::GetCharacteristicDescription()
{
	std::string output;

	output.append("As a Magician you have two choices:\n");
	output.append("- You can change your building cards with another player (even if you have 0 cards).\n");
	output.append("- You can change you building cards with cards from the deck.");

	return output;
}


void Magician::PerformCharacteristic()
{
	/*
	Hij mag of:
	- al zijn handkaarten (ook als dit 0 is) voor alle handkaarten van een andere speler omruilen of
	- naar keuze een aantal handkaarten afleggen en een gelijk aantal gebouwenkaarten trekken
	*/
}

PlayerCardType Magician::GetType()
{
	return PlayerCardType::MAGICIAN;
}