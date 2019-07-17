/*
 * PlayingState.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "WALKING.h"
#include "WalkingStateManager.h"

#include <iostream>

WALKING::WALKING()
: WalkingManagerState(std::string("WALKING")) {
}

WALKING::~WALKING() {
}

void WALKING::next(WalkingStateManager * manager)
{
	
}
void WALKING::prev(WalkingStateManager * manager)
{
	manager->SetState(WalkingStateManager::ST_IDLE);
}
void WALKING::handle(WalkingStateManager * manager)
{
	std::cout << "------------------------WALKING-----------------"<< std::endl;
	manager->motion->walkForward();	
}
