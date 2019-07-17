#include "DetectionManager.h"

#include "LOOK_FOR_CUP.h"
#include "SEND_CUP_DATA.h"
#include "CALCULATE_DISTANCE.h"

#include <iostream>

DetectionManager::DetectionManager()
: m_pState(new LOOK_FOR_CUP()){
	this->detector = new DetectionClass();
	this->server = new SocketCommunication(8080);
}

DetectionManager::~DetectionManager() {
	delete m_pState;
}

void DetectionManager::prevState() {
	m_pState->prev(this);
}

void DetectionManager::nextState() {
	m_pState->next(this);
}
void DetectionManager::handle() {
	m_pState->handle(this);
}

void DetectionManager::SetState(State state)
{
	std::cout << "changing from " << m_pState->GetName() << " to ";
	delete m_pState;

	if(state == ST_SEND)
	{
		m_pState = new SEND_CUP_DATA();
	}
	else if(state == ST_CALC)
	{
		m_pState = new CALCULATE_DISTANCE();
	}
	else
	{
		m_pState = new LOOK_FOR_CUP();
	}

	std::cout << m_pState->GetName() << " state\n";
}
