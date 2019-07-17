#ifndef CALCULATEDISTANCE_H_
#define CALCULATEDISTANCE_H_

#include "DetectionManagerState.h"

class DetectionManager;

class CALCULATE_DISTANCE : public DetectionManagerState {
public:
	CALCULATE_DISTANCE();
	virtual ~CALCULATE_DISTANCE();

	virtual void prev(DetectionManager * manager);
	virtual void next(DetectionManager * manager);
	virtual void handle(DetectionManager * manager);
};

#endif /* CALCULATEDISTANCE_H_ */
