/* GrabbingManager header file */
#include "LinuxDARwIn.h"

#ifdef MX28_1024
#define MOTION_FILE_PATH 	"/robotis/Data/motion_1024.bin"
#else
#define	MOTION_FILE_PATH	"/robotis/Data/motion_4096.bin"
#endif

using namespace Robot;

class GrabbingManager {
	private:
		minIni* ini;
		
		void grab_init();
		void run_page(int page);
	public:
		GrabbingManager(minIni*);
};
