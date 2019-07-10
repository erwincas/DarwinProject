/* GrabbingManager source file */
#include "GrabbingManager.hpp"

#define PAGE_PICK_UP 60

GrabbingManager::GrabbingManager(minIni* ini) {
	this->ini = ini;
	//ab_init();
	grab_init();
	run_page(PAGE_PICK_UP);
}

void GrabbingManager::grab_init(){
	MotionManager::GetInstance()->LoadINISettings(this->ini);
    MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	MotionManager::GetInstance()->SetEnable(true);

    Action::GetInstance()->LoadFile(MOTION_FILE_PATH);

}

void GrabbingManager::run_page(int page) {
	Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	Action::GetInstance()->Start(page);
	while(Action::GetInstance()->IsRunning());
	Action::GetInstance()->m_Joint.SetEnableBody(false,false);
}
