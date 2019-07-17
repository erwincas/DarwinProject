/*
 * StoppedState.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "IDLE.h"
#include "WalkingStateManager.h"


#include <iostream>

IDLE::IDLE()
: WalkingManagerState(std::string("IDLE")) {
}

IDLE::~IDLE() {
}

void IDLE::next(WalkingStateManager * manager)
{
	if(manager->walkFlag == 1)
	{
		manager->SetState(WalkingStateManager::ST_WALK);
	}
	else
	{
		manager->SetState(WalkingStateManager::ST_GRAB);
	}
	//manager->SetState(WalkingStateManager::ST_GRAB);
}
void IDLE::prev(WalkingStateManager * manager)
{
	
}
void IDLE::handle(WalkingStateManager * manager)
{
	std::cout << "--------------------------IDLE--------------------------"<< std::endl;

}


