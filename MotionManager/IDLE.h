#ifndef LOOKFORCUP_H_
#define LOOKFORCUP_H_

#include "WalkingManagerState.h"

class WalkingManager;

class IDLE : public WalkingManagerState {
public:
	IDLE();
	virtual ~IDLE();

	virtual void prev(WalkingStateManager * manager);
	virtual void next(WalkingStateManager * manager);
	virtual void handle(WalkingStateManager * manager);
};

#endif /* LOOKFORCUP_H_ */
