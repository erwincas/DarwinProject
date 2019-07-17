#ifndef SENDCUPDATA_H_
#define SENDCUPDATA_H_

#include "DetectionManagerState.h"

class DetectionManager;

class SEND_CUP_DATA : public DetectionManagerState {
public:
	SEND_CUP_DATA();
	virtual ~SEND_CUP_DATA();

	virtual void prev(DetectionManager * manager);
	virtual void next(DetectionManager * manager);
	virtual void handle(DetectionManager * manager);
};

#endif /* SENDCUPDATA_H_ */
