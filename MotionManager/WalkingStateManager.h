#ifndef WALKINGSTATEMANAGER_H_
#define WALKINGSTATEMANAGER_H_

#include "MotionClass.h"

class MotionClass;
class WalkingManagerState;

class WalkingStateManager {
public:
	enum State
	{
		ST_WALK,
		ST_IDLE,
		ST_GRAB
	};

	
	WalkingStateManager();
	virtual ~WalkingStateManager();
	MotionClass * motion;
	void prevState();
	void nextState();
	void handle();

	void SetState(State state);

	int walkFlag;

private:
	WalkingManagerState * m_pState;
};

#endif /* WALKINGSTATEMANAGER_H_*/
