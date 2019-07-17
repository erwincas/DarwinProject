/*
 *
 *
 *  
 *      
 */

#ifndef WALKINGMANAGERSTATE_H_
#define WALKINGMANAGERSTATE_H_

#include <string>


class WalkingStateManager;
class MotionClass;

class WalkingManagerState {
public:
	WalkingManagerState(std::string name);
	virtual ~WalkingManagerState();
	MotionClass * motion;
	virtual void prev(WalkingStateManager * manager);
	virtual void next(WalkingStateManager * manager);
	virtual void handle(WalkingStateManager * manager);

	std::string GetName() { return m_name; }

private:
	std::string   m_name;
};

#endif /* WALKINGMANAGERSTATE_H_ */
