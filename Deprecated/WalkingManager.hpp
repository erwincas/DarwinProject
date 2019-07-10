/* Walking manager class header file */
#include "LinuxDARwIn.h"
#include <time.h>


#ifdef MX28_1024
#define MOTION_FILE_PATH 	"/robotis/Data/motion_1024.bin"
#else
#define	MOTION_FILE_PATH	"/robotis/Data/motion_4096.bin"
#endif



using namespace Robot;

class WalkingManager {
	private:
		minIni* ini;
		CM730* cm730;
		void walking_init();
		void run_page(unsigned int);
		
	public:
		WalkingManager(minIni* ini, CM730* cm730);
		void stand(int);
		void move(int);
		void start_walking(void);
		void stop_walking(void);
};
