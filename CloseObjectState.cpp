#include "CloseObjectState.h"


CloseObjectState::CloseObjectState()
{

}


CloseObjectState::~CloseObjectState()
{
}


void CloseObjectState::doAction(double _timer, Enemy& enemy, Player& player){}
int CloseObjectState::goNext(Enemy& enemy, Player& player){ return 0; }
void CloseObjectState::randomizeState(mt19937* rnd){}

void CloseObjectState::chooseMovingVector(Enemy& enemy)
{
	
}