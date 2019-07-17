#ifndef WALKING_H_
#define WALKING_H_

#include "WalkingManagerState.h"

class WalkingStateManager;

class WALKING : public WalkingManagerState {
public:
	WALKING();
	virtual ~WALKING();

	virtual void prev(WalkingStateManager * manager);
	virtual void next(WalkingStateManager * manager);
	virtual void handle(WalkingStateManager * manager);
};

#endif /* CALCULATEDISTANCE_H_ */
