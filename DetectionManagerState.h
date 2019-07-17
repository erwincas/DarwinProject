/*
 * MusicPlayerState.h
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#ifndef DETECTIONMANAGERSTATE_H_
#define DETECTIONMANAGERSTATE_H_

#include <string>


class DetectionManager;

class DetectionManagerState {
public:
	DetectionManagerState(std::string name);
	virtual ~DetectionManagerState();

	virtual void prev(DetectionManager * manager);
	virtual void next(DetectionManager * manager);
	virtual void handle(DetectionManager * manager);

	std::string GetName() { return m_name; }

private:
	std::string   m_name;
};

#endif /* DETECTIONMANAGERSTATE_H_ */
