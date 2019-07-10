/*
 * PlayingState.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "CALCULATE_DISTANCE.h"
#include "DetectionManager.h"

#include <iostream>

CALCULATE_DISTANCE::CALCULATE_DISTANCE()
: DetectionManagerState(std::string("CALC DISTANCE")) {
}

CALCULATE_DISTANCE::~CALCULATE_DISTANCE() {
}

void CALCULATE_DISTANCE::next(DetectionManager * player)
{
	player->SetState(DetectionManager::ST_SEND);
}

void CALCULATE_DISTANCE::prev(DetectionManager * player)
{
	
}
void CALCULATE_DISTANCE::handle(DetectionManager * manager)
{
	int height = manager->cup.height;
	if(manager->cup.height < manager->cup.width)
	{
		height = manager->cup.width;
	}
	manager->distance = manager->detector->calculateDistance(height);
	std::cout << "calculating distance: " << manager->distance << std::endl;
	
}
