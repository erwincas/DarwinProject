#ifndef SENDCUPDATA_H_
#define SENDCUPDATA_H_

#include "WalkingManagerState.h"

class WalkingManager;

class GRAB : public WalkingManagerState {
public:
	GRAB();
	virtual ~GRAB();

	virtual void prev(WalkingStateManager * manager);
	virtual void next(WalkingStateManager * manager);
	virtual void handle(WalkingStateManager * manager);
};

#endif /* SENDCUPDATA_H_ */
