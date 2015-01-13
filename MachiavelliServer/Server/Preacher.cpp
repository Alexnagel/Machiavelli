#include "Preacher.h"


Preacher::Preacher() : PlayerCard("Preacher")
{
}


Preacher::~Preacher()
{
}

std::string Preacher::GetCharacteristicDescription()
{
	return "As a Preacher you will receive 1 gold for every blue building you have build";
}

void Preacher::PerformCharacteristic()
{
	/*
	Zijn gebouwenkaarten mogen door de condotierre niet verwijderd worden. De prediker onvangt 1 goudstuk
	voor elk blauw gebouw dat hij voor zich heeft liggen.
	*/
}

PlayerCardType Preacher::GetType()
{
	return PlayerCardType::PREACHER;
}