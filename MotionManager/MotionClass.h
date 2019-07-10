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

class MotionClass
{
	public:
		MotionClass();
		virtual ~MotionClass();
		void walkForward();
		void rotateLeft();
		void rotateRight();

	private:
		minIni* ini;
		void init();
		void change_current_dir();
};


#endif 
