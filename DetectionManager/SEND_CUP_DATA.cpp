/*
 * PausedState.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "SEND_CUP_DATA.h"
#include "DetectionManager.h"

#include <iostream>

SEND_CUP_DATA::SEND_CUP_DATA()
: DetectionManagerState(std::string("SEND CUP DATA")) {
}

SEND_CUP_DATA::~SEND_CUP_DATA() {
}

void SEND_CUP_DATA::prev(DetectionManager * player)
{
	
}

void SEND_CUP_DATA::next(DetectionManager * player)
{
	player->SetState(DetectionManager::ST_LOOK);
}

void SEND_CUP_DATA::handle(DetectionManager * manager)
{
	std::cout << "Sending data..." << std::endl;
	char  buf[20];
	std::cout << "data: "<< manager->distance << std::endl;
	snprintf(buf, sizeof(buf), "%d", manager->distance);
	manager->server->sendToServer(buf);
	std::cout << "data sent" << std::endl;
}