/*
 * StoppedState.h
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#ifndef LOOKFORCUP_H_
#define LOOKFORCUP_H_

#include "DetectionManagerState.h"

class DetectionManager;

class LOOK_FOR_CUP : public DetectionManagerState {
public:
	LOOK_FOR_CUP();
	virtual ~LOOK_FOR_CUP();

	virtual void prev(DetectionManager * manager);
	virtual void next(DetectionManager * manager);
	virtual void handle(DetectionManager * manager);
};

#endif /* LOOKFORCUP_H_ */
