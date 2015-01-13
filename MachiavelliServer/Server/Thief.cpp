#include "Thief.h"


Thief::Thief() : PlayerCard("Thief")
{
}


Thief::~Thief()
{
}

std::string Thief::GetCharacteristicDescription()
{
	std::string output;

	output.append("As a Thief you will choose a character to steal all his gold.");
	output.append("You will receive the gold when it is this character his turn.");

	return output;
}

void Thief::PerformCharacteristic()
{
	/*
	Hij kiest een karakter, die hij deze ronde wil bestelen. Hij mag de moordenaar of diens slachtoffer niet
	aanwijzen. Als een karakter door de dief is gekozen, dan geeft deze zich pas bloot als hij aan de beurt is. Het
	bestolen karakter geeft zich niet in de beurt van de dief bloot! Hij geeft al het goud dat hij bezit pas aan het
	begin van zijn eigen beurt aan de dief. Het goud dat het bestolen karakter tijdens zijn beurt ontvangt mag hij
	houden.
	*/
}

PlayerCardType Thief::GetType()
{
	return PlayerCardType::THIEF;
}