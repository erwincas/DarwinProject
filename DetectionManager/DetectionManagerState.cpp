/*
 * MusicPlayerState.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "DetectionManagerState.h"


#include <iostream>

DetectionManagerState::DetectionManagerState(std::string name)
: m_name(name)
{

}

DetectionManagerState::~DetectionManagerState() {
}

void DetectionManagerState::prev(DetectionManager * player)
{
	std::cout << "Illegal state transition from " << GetName() << " to Playing\n";
}

void DetectionManagerState::next(DetectionManager * player)
{
	std::cout << "Illegal state transition from " << GetName() << " to Paused\n";
}

void DetectionManagerState::handle(DetectionManager * manager)
{
	std::cout << "Illegal handle";
}


