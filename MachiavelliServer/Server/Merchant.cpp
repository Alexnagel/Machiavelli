#include "Merchant.h"


Merchant::Merchant() : PlayerCard("Merchant")
{
}


Merchant::~Merchant()
{
}


void Merchant::PerformCharacteristic()
{
	/*
	Hij ontvangt 1 goudstuk. Bovendien ontvangt hij 1 goudstuk voor elk groen gebouw dat hij voor zich heeft
	liggen.
	*/
}

PlayerCardType Merchant::GetType()
{
	return PlayerCardType::MERCHANT;
}