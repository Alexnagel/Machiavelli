#include "Condottiere.h"


Condottiere::Condottiere() : PlayerCard("Condottiere")
{
}


Condottiere::~Condottiere()
{
}


void Condottiere::PerformCharacteristic()
{
	/*
	Hij mag een gebouw bij een andere speler weghalen. Gebouwen die maar 1 goudstuk waard zijn mag hij
	kosteloos verwijderen. Voor andere gebouwen moet hij 1 goudstuk minder betalen dan ze hun eigenaar gekost
	hebben. Het goud wordt aan de bank betaald. Het verwijderde gebouw gaat op de aflegstapel. De condotierre
	mag ook gebouwen van vermoorde karakters verwijderen. Hij mag echter geen gebouwen verwijderen uit
	steden die al uit 8 of meer gebouwen bestaan. De condotierre ontvangt 1 goudstuk voor elk rood gebouw dat
	hij voor zich heeft liggen.
	*/
}

PlayerCardType Condottiere::GetType()
{
	return PlayerCardType::CONDOTTIERE;
}
