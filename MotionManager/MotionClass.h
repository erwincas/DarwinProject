#ifndef MOTIONCLASS_H_
#define MOTIONCLASS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

#include <termios.h>
#include <term.h>
#include <pthread.h>

#include "LinuxDARwIn.h"
#include "FSR.h"

#define INI_FILE_PATH 	"/Data/config.ini"
#define U2D_DEV_NAME 	"/dev/ttyUSB0"

using namespace Robot;

//class MotionManager;
//class Action;

class MotionClass
{
	public:
		MotionClass();
		virtual ~MotionClass();
		bool walkFlag;
		void walkForward();
		void rotateLeft();
		void rotateRight();
		void grab();

	private:
		bool init_Framework(void);
		//bool init(void);
		void change_current_dir();
};


#endif 
