/*
 * MusicPlayer.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "WalkingStateManager.h"
#include "MotionClass.h"

#include "IDLE.h"
#include "WALKING.h"
#include "GRAB.h"

#include <iostream>

WalkingStateManager::WalkingStateManager()
: m_pState(new IDLE()){
	this->motion = new MotionClass();
	this->walkFlag = 0;
	
}

WalkingStateManager::~WalkingStateManager() {
	delete m_pState;
}

void WalkingStateManager::prevState() {
	m_pState->prev(this);
}

void WalkingStateManager::nextState() {
	m_pState->next(this);
}
void WalkingStateManager::handle() {
	m_pState->handle(this);
}

void WalkingStateManager::SetState(State state)
{
	std::cout << "changing from " << m_pState->GetName() << " to ";
	delete m_pState;

	if(state == ST_GRAB)
	{
		m_pState = new GRAB();
	}
	else if(state == ST_WALK)
	{
		m_pState = new WALKING();
	}
	else
	{
		m_pState = new IDLE();
	}

	std::cout << m_pState->GetName() << " state\n";
}
