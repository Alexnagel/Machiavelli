#include "King.h"


King::King() : PlayerCard("King")
{
}


King::~King()
{
}


void King::PerformCharacteristic()
{
	/*
	Hij krijgt de koningskaart en wordt de volgende ronde startspeler. Na zijn beurt roept hij de overige karakters
	op. De Koning ontvangt 1 goudstuk voor elk geel gebouw dat hij voor zich heeft liggen. Als er geen nieuwe
	Koning is (omdat dit karakter is afgelegd of vermoord), dan blijft de huidige Koning in ambt en verricht hij ook
	deze beurt de genoemde handelingen.

	Bijzondere gevallen :

	- Als de Koning vermoord wordt blijft deze tot het einde van de ronde de bij zijn ambt horende
	  handelingen verrichten. Aan het begin van de volgende ronde krijgt de in de vorige ronde vermoorde
	  Koning de koningskaart.

	- Als de koningskaart is afgelegd, blijft de zittende Koning ook de volgende ronde in ambt.
	*/
}

PlayerCardType King::GetType()
{
	return PlayerCardType::KING;
}