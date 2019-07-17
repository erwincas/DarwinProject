#include "WalkingManagerState.h"


#include <iostream>

WalkingManagerState::WalkingManagerState(std::string name)
: m_name(name)
{

}

WalkingManagerState::~WalkingManagerState() {
}

void WalkingManagerState::prev(WalkingStateManager * manager)
{
	std::cout << "Illegal state transition from " << GetName() << " to Playing\n";
}

void WalkingManagerState::next(WalkingStateManager * manager)
{
	std::cout << "Illegal state transition from " << GetName() << " to Paused\n";
}

void WalkingManagerState::handle(WalkingStateManager * manager)
{
	std::cout << "Illegal handle";
}


