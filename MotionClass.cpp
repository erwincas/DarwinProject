#include "MotionClass.h"

MotionClass::MotionClass()
{
	//this->init();

	printf("Start constructor");	
	//LinuxCM730 linux_cm730(U2D_DEV_NAME);

	change_current_dir();

	LinuxCM730 linux_cm730(U2D_DEV_NAME);
	CM730 cm730(&linux_cm730);
	this->ini = new minIni(INI_FILE_PATH);
	this->cm730 = new CM730(cm730);

	init_Framework();

	int n = 0;
	int param[JointData::NUMBER_OF_JOINTS * 5];
	int wGoalPosition, wStartPosition, wDistance;

	for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
	{
		wStartPosition = MotionStatus::m_CurrentJoints.GetValue(id);
		wGoalPosition = Walking::GetInstance()->m_Joint.GetValue(id);
		if( wStartPosition > wGoalPosition )
			wDistance = wStartPosition - wGoalPosition;
		else
			wDistance = wGoalPosition - wStartPosition;

		wDistance >>= 2;
		if( wDistance < 8)
			wDistance = 8;

		param[n++] = id;
		param[n++] = CM730::GetLowByte(wGoalPosition);
		param[n++] = CM730::GetHighByte(wGoalPosition);
		param[n++] = CM730::GetLowByte(wDistance);
		param[n++] = CM730::GetHighByte(wDistance);

	}
	cm730.SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param);

	printf("Constructor has run to its end");
}

void MotionClass::change_current_dir(){
	char exepath[1024] = {0};
	if (readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
		chdir(dirname(exepath));
}

bool MotionClass::init_Framework(void)
{
	
	LinuxCM730 linux_cm730(U2D_DEV_NAME);
	CM730 cm730(&linux_cm730);
	

	if(MotionManager::GetInstance()->Initialize(&cm730) == false)
	{
		printf("Fail to initialize Motion Manager!\n");
		//return 0;
	}
	MotionManager::GetInstance()->LoadINISettings(ini);
	Walking::GetInstance()->LoadINISettings(ini);

	MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
	MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
	MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	//MotionManager::GetInstance()->SetEnable(true);

	LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
	motion_timer->Start();

	Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	MotionManager::GetInstance()->SetEnable(true);
	Action::GetInstance()->Start(15);
	printf("Framework initialized");
	while(Action::GetInstance()->IsRunning()) usleep(8*1000);
	printf("Framework initalization stopped running");
	return true;
}

/*bool MotionClass::init(void)
{
	
	change_current_dir();

	linuxCM730 linux_cm730(U2D_DEV_NAME);
	CM730 cm730(&linux_cm730);
	this->ini = new minIni(INI_FILE_PATH);

	init_Framework();

	int n = 0;
	int param[JointData::NUMBER_OF_JOINTS * 5];
	int wGoalPosition, wStartPosition, wDistance;

	for(int id=JointData::ID_R_SHOULDER_PITCH; id<JointData::NUMBER_OF_JOINTS; id++)
	{
		wStartPosition = MotionStatus::m_CurrentJoints.GetValue(id);
		wGoalPosition = Walking::GetInstance()->m_Joint.GetValue(id);
		if( wStartPosition > wGoalPosition )
			wDistance = wStartPosition - wGoalPosition;
		else
			wDistance = wGoalPosition - wStartPosition;

		wDistance >>= 2;
		if( wDistance < 8)
			wDistance = 8;

		param[n++] = id;
		param[n++] = CM730::GetLowByte(wGoalPosition);
		param[n++] = CM730::GetHighByte(wGoalPosition);
		param[n++] = CM730::GetLowByte(wDistance);
		param[n++] = CM730::GetHighByte(wDistance);
	}
	cm730.SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param);

	sleep(2);
	

//	Walking::GetInstance()->LoadINISettings(ini);
		
//	Action::GetInstance()->m_Joint.SetEnableRightArmOnly(true, true);
//	Action::GetInstance()->m_Joint.SetEnableLeftArmOnly(true, true);
//	Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
//	Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
//	MotionManager::GetInstance()->SetEnable(true);

	static const int MAX_FSR_VALUE = 254;

	
//	Walking::GetInstance()->X_MOVE_AMPLITUDE = 20;
//	Walking::GetInstance()->A_MOVE_AMPLITUDE = 0;
//	MotionManager::GetInstance()->StopLogging();
//	Walking::GetInstance()->Start();
//	usleep(1500000);
//	Walking::GetInstance()->Stop();

	
//	cm730.SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param);

//	sleep(2);

	//Action::GetInstance()->m_Joint.SetEnableRightArmOnly(true, true);
	//Action::GetInstance()->m_Joint.SetEnableLeftArmOnly(true, true);
	//Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
	//Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);

//	MotionManager::GetInstance()->SetEnable(true);
//	Action::GetInstance()->LoadFile("/robotis/Data/motion_4096.bin");

	//static const int MAX_FSR_VALUE = 254;

//	Walking::GetInstance()->LoadINISettings(ini);

	
//	Action::GetInstance()->m_Joint.SetEnableBody(true, true);
//	Action::GetInstance()->Start(60);
//	while(Action::GetInstance()->IsRunning());
//	Action::GetInstance()->m_Joint.SetEnableBody(false,false);

}*/

void MotionClass::walkForward(minIni* ini, CM730* cm730)
{

	this->ini = ini;
	this->cm730 = cm730;

	MotionManager::GetInstance()->LoadINISettings(this->ini);
	//MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	//MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	MotionManager::GetInstance()->SetEnable(true);
	
	Action::GetInstance()->m_Joint.SetEnableRightArmOnly(true, true);
	Action::GetInstance()->m_Joint.SetEnableLeftArmOnly(true, true);
	Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);

	Walking::GetInstance()->X_MOVE_AMPLITUDE = 20;
	Walking::GetInstance()->A_MOVE_AMPLITUDE = 0;
	MotionManager::GetInstance()->StopLogging();
	MotionManager::GetInstance()->SetEnable(true);
	Walking::GetInstance()->Start();
	usleep(1500000);
	Walking::GetInstance()->Stop();
}


void MotionClass::rotateLeft()
{
	Walking::GetInstance()->X_MOVE_AMPLITUDE = 0;
	Walking::GetInstance()->A_MOVE_AMPLITUDE = -30;
	MotionManager::GetInstance()->StopLogging();
	MotionManager::GetInstance()->SetEnable(true);
	Walking::GetInstance()->Start();
	usleep(3000000);
	Walking::GetInstance()->Stop();
}

void MotionClass::rotateRight()
{
	Walking::GetInstance()->X_MOVE_AMPLITUDE = 0;
	Walking::GetInstance()->A_MOVE_AMPLITUDE = 30;
	MotionManager::GetInstance()->StopLogging();
	MotionManager::GetInstance()->SetEnable(true);
	Walking::GetInstance()->Start();
	usleep(3000000);
	Walking::GetInstance()->Stop();
}

MotionClass::~MotionClass(){

}

