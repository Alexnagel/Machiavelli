#include "Murderer.h"


Murderer::Murderer() : PlayerCard("Murderer")
{
}


Murderer::~Murderer()
{
}


void Murderer::PerformCharacteristic()
{
	/*
	Hij kiest een karakter die hij deze ronde wil vermoorden.Als het gekozen karakter wordt genoemd, geeft deze
	zich niet bloot en komt hij deze ronde ook niet aan de beurt.Voorbeeld : als de moordenaar deze ronde de
	koopman aanwijst, dan slaat deze in stilte zijn beurt over.
	*/

}

PlayerCardType Murderer::GetType()
{
	return PlayerCardType::MURDERER;
}