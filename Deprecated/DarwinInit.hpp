/* Initialise Darwin class header file */

#include <stdio.h>
#include <unistd.h>
#include "LinuxDARwIn.h"
#include <string.h>
#include <libgen.h>
  
using namespace Robot;

#define INI_FILE_PATH		"/robotis/Data/config.ini"
#define U2D_DEV_NAME		"/dev/ttyUSB0"

#ifdef MX28_1024
#define MOTION_FILE_PATH 	"/robotis/Data/motion_1024.bin"
#else
#define	MOTION_FILE_PATH	"/robotis/Data/motion_4096.bin"
#endif


class DarwinInit {
	private:
		void change_current_dir(void);
       	bool load_action_file(void);
		bool framework_init(void);

	public:
		DarwinInit(void);
    	LinuxCM730* linux_cm730;
		CM730* cm730;
		minIni* ini;
};
