#include "DarwinInit.hpp"
#include "WalkingManager.hpp" 
#include "GrabbingManager.hpp"
#include <stdio.h>

int main(void) {
	printf("Testing for Project Krekel\n");

	DarwinInit init;
	WalkingManager walkingmanager(init.ini, init.cm730);
	
	walkingmanager.move(10);
	GrabbingManager grabbingmanager(init.ini);

	return 0;
}
