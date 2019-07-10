/* Walking manager class cpp file */
#include "WalkingManager.hpp"

#define PAGE_SIT 		15
#define PAGE_STAND 		16
#define PAGE_PICK_UP	50
#define SPEED_FW 		15
#define SPEED_TURN 		10

WalkingManager::WalkingManager(minIni* ini, CM730* cm730) {
	this->ini = ini;
	this->cm730 = cm730;
	walking_init();
}
	
void WalkingManager::walking_init(){
	MotionManager::GetInstance()->LoadINISettings(this->ini);
    MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
	MotionManager::GetInstance()->SetEnable(true);
	Walking::GetInstance()->X_MOVE_AMPLITUDE = SPEED_FW;

    Action::GetInstance()->LoadFile(MOTION_FILE_PATH);
}

void WalkingManager::move(int distance) {
	run_page(PAGE_STAND);
	printf("Start walking \n");
	start_walking();
	sleep(2);
	stop_walking();
	run_page(PAGE_SIT);
}

void start_walking(void) {
	if(Walking::GetInstance()->IsRunning() == false){
		/* Always stand before starting with walking */
		run_page(PAGE_STAND);
		/* Onderstaande moet worden Enable BodyW/OArms, zodat de beker in de hand blijft, hiervoo is een aanpassing in het framework gemaakt, weet nu even de exacte naam niet. */
		Walking::GetInstance->m_Joint.SetEnableBodyWithoutHead(true, true);	
		Walking::GetInstance()->Start();
	}
}

void stop_walking(void) {
	if(Walking::GetInstance()->IsRunning() == true){
		Walking::GetInstance()->Stop();
		/* Geef de joints weer vrij voor andere acties */
		Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(false, false);
	}
}


void WalkingManager::run_page(unsigned int page){
     Action::GetInstance()->m_Joint.SetEnableBody(true, true);
     Action::GetInstance()->Start(page);
     while(Action::GetInstance()->IsRunning()); /* Wacht tot de actie is uitgevoerd */
	 Action::GetInstance()->m_Joint.SetEnableBody(false, false);
}

