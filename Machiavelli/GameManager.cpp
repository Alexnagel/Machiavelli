#include "GameManager.h"


GameManager::GameManager()
{
    ClientSocket("127.0.0.1", 10001);
}


GameManager::~GameManager()
{
}
