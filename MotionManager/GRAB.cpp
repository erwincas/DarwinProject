#include "GRAB.h"
#include "WalkingStateManager.h"

#include <iostream>

GRAB::GRAB()
: WalkingManagerState(std::string("GRAB")) {
}

GRAB::~GRAB() {
}

void GRAB::prev(WalkingStateManager * manager)
{
	manager->SetState(WalkingStateManager::ST_IDLE);
}

void GRAB::next(WalkingStateManager * manager)
{
	
}

void GRAB::handle(WalkingStateManager * manager)
{
	std::cout << "-------------------------------GRABBING-------------------------------" << std::endl;
	manager->motion->grab();
}
