#ifndef DETECTIONMANAGER_H_
#define DETECTIONMANAGER_H_

#include "DetectionClass.h"
#include "SocketCommunication.h"

class DetectionManagerState;
class DetectionClass;
class SocketCommunication;

class DetectionManager {
public:
	enum State
	{
		ST_LOOK,
		ST_CALC,
		ST_SEND
	};
	DetectionClass * detector;
	SocketCommunication * server;
	Rect cup = Rect(-1,-1,-1,-1);
	int distance = -1;

	DetectionManager();
	virtual ~DetectionManager();

	void prevState();
	void nextState();
	void handle();

	void SetState(State state);

private:
	DetectionManagerState * m_pState;
};

#endif /* DETECTIONMANAGER_H_*/
