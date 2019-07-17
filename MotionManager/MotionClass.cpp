#include "MotionClass.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

#include <termios.h>
#include <term.h>
#include <pthread.h>

#include "LinuxDARwIn.h"
#include "FSR.h"


using namespace Robot;

MotionClass::MotionClass()
{

	this->walkFlag = false;
	/*
	//this->init();

	//LinuxCM730 linux_cm730(U2D_DEV_NAME);
	this->motion = new MotionManager;
	this->act = new Action;
	this->change_current_dir();

	LinuxCM730 linux_cm730(U2D_DEV_NAME);
	CM730 cm730(&linux_cm730);
	this->ini = new minIni(INI_FILE_PATH);
	this->cm730 = &cm730;

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




	printf("Constructor has run to its end");*/
}

void MotionClass::change_current_dir(){
	char exepath[1024] = {0};
	if (readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
		int check = chdir(dirname(exepath));
}

bool MotionClass::init_Framework(void)
{
	return false;
/*
	if(this->motion->GetInstance()->Initialize(this->cm730) == false)
	{
		printf("Fail to initialize Motion Manager!\n");
		//return 0;
	}
	//MotionManager::GetInstance()->LoadINISettings(this->ini);
	//Walking::GetInstance()->LoadINISettings(this->ini);

	this->motion->GetInstance()->AddModule((MotionModule*)Head::GetInstance());
	this->motion->GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
	this->motion->GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	//MotionManager::GetInstance()->SetEnable(true);

	LinuxMotionTimer *motion_timer = new LinuxMotionTimer(this->motion->GetInstance());
	motion_timer->Start();


	this->act->GetInstance()->m_Joint.SetEnableBody(true, true);
	this->motion->GetInstance()->SetEnable(true);
	//Action::GetInstance()->Start();
	while(this->act->GetInstance()->IsRunning()) usleep(8*1000);
	return true;
	*/
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

void MotionClass::walkForward()
{

		printf( "\n===== Walk this bitch =====\n\n");

   	 	this->change_current_dir();
    	minIni* ini = new minIni(INI_FILE_PATH); 


    	//////////////////// Framework Initialize ////////////////////////////
		LinuxCM730 linux_cm730(U2D_DEV_NAME);
    	CM730 cm730(&linux_cm730);

	//if (this->initFlag == false){	
    	if(MotionManager::GetInstance()->Initialize(&cm730) == false)
    	{
        	printf("Fail to initialize Motion Manager!\n");
           
    	}
    	MotionManager::GetInstance()->LoadINISettings(ini);
    	Walking::GetInstance()->LoadINISettings(ini);
	
    	MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
    	MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
    	MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance    ());
	
    	LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
    	motion_timer->Start();
    /////////////////////////////////////////////////////////////////////
	//this->initFlag = true;
	//}
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
        if( wDistance < 8 )
            wDistance = 8;

        param[n++] = id;
        param[n++] = CM730::GetLowByte(wGoalPosition);
        param[n++] = CM730::GetHighByte(wGoalPosition);
        param[n++] = CM730::GetLowByte(wDistance);
        param[n++] = CM730::GetHighByte(wDistance);
    }
    cm730.SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param); // Opstaan gedeelte.

    printf("Press the ENTER key to begin!\n");
    //getchar();i
	usleep(1500000);
    printf("Press the SPACE key to start/stop walking.. \n\n");

    Action::GetInstance()->m_Joint.SetEnableRightArmOnly(true, true);
    Action::GetInstance()->m_Joint.SetEnableLeftArmOnly(true, true);
    Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
    Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);
    MotionManager::GetInstance()->SetEnable(true);

    //static const int MAX_FSR_VALUE = 254;



    Walking::GetInstance()->LoadINISettings(ini);
    //pthread_t thread_t;
    //pthread_create(&thread_t, NULL, walk_thread, NULL);

	//Walking::GetInstance()->X_MOVE_AMPLITUDE = 20;
	//Walking::GetInstance()->A_MOVE_AMPLITUDE = 0;
	//MotionManager::GetInstance()->StopLogging();
	//Walking::GetInstance()->Start();
	//usleep(1500000);
	//Walking::GetInstance()->Stop();

	Walking::GetInstance()->X_MOVE_AMPLITUDE = 20;
	Walking::GetInstance()->A_MOVE_AMPLITUDE = 0;
	MotionManager::GetInstance()->StopLogging();
	Walking::GetInstance()->Start();
	usleep(1500000);
	Walking::GetInstance()->Stop();
	usleep(2000000);
	/*while (1){

	Walking::GetInstance()->X_MOVE_AMPLITUDE = 20;
	Walking::GetInstance()->A_MOVE_AMPLITUDE = 0;
	MotionManager::GetInstance()->StopLogging();
	Walking::GetInstance()->Start();
	usleep(1500000);
	Walking::GetInstance()->Stop();
	usleep(2000000);
	if(this->walkFlag == true){
		break;
	}

	}*/

	//Walking::GetInstance()->X_MOVE_AMPLITUDE = 0;
	//Walking::GetInstance()->A_MOVE_AMPLITUDE = 0;
	//motion_timer->Stop();
	//printf("\n--------------------------\n im done with the walkforward function \n------------------    --------\n");
	/*
	this->change_current_dir();
	//this->ini = ini;
	//this->cm730 = cm730;

	//static const int MAX_FSR_VALUE = 254;*/
	/* int n = 0;
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
	this->cm730->SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param);*/

	//MotionManager::GetInstance()->LoadINISettings(this->ini);
	//Walking::GetInstance()->LoadINISettings(this->ini);
	//MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	//MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
	//MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	//MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
	/*this->motion->GetInstance()->SetEnable(true);

	
	this->act->GetInstance()->m_Joint.SetEnableRightArmOnly(true, true);
	this->act->GetInstance()->m_Joint.SetEnableLeftArmOnly(true, true);
	this->motion->GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);

	this->motion->GetInstance()->X_MOVE_AMPLITUDE = 20;
	this->motion->GetInstance()->A_MOVE_AMPLITUDE = 0;
	this->motion->GetInstance()->StopLogging();
	this->motion->GetInstance()->SetEnable(true);
	this->motion->GetInstance()->Start();F
	printf("\n--------------------------\n LOOPT IE NOU EINDELIJK? \n------------------    --------\n"); 
	usleep(1500000);
	this->motion->GetInstance()->Stop();
	printf("\n--------------------------\n BLIJKBAAR NIET \n------------------    --------\n"); 
	*/
}


void MotionClass::rotateLeft()
{
	/* Walking::GetInstance()->X_MOVE_AMPLITUDE = 0;
	Walking::GetInstance()->A_MOVE_AMPLITUDE = -30;
	MotionManager::GetInstance()->StopLogging();
	MotionManager::GetInstance()->SetEnable(true);
	Walking::GetInstance()->Start();
	usleep(3000000);
	Walking::GetInstance()->Stop();*/
}

void MotionClass::rotateRight()
{
	/* Walking::GetInstance()->X_MOVE_AMPLITUDE = 0;
	Walking::GetInstance()->A_MOVE_AMPLITUDE = 30;
	MotionManager::GetInstance()->StopLogging();
	MotionManager::GetInstance()->SetEnable(true);
	Walking::GetInstance()->Start();
	usleep(3000000);
	Walking::GetInstance()->Stop();*/
}
void MotionClass::grab()
{


	printf( "\n===== Grab this bitch =====\n\n");

   	this->change_current_dir();
    minIni* ini = new minIni(INI_FILE_PATH); 


    //////////////////// Framework Initialize ////////////////////////////
	LinuxCM730 linux_cm730(U2D_DEV_NAME);
    CM730 cm730(&linux_cm730);

	if(MotionManager::GetInstance()->Initialize(&cm730) == false)
    {
       	printf("Fail to initialize Motion Manager!\n");
         
    }
    MotionManager::GetInstance()->LoadINISettings(ini);
    Walking::GetInstance()->LoadINISettings(ini);
	
	MotionManager::GetInstance()->AddModule((MotionModule*)Head::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Walking::GetInstance());
    MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance    ());
	
    LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
    motion_timer->Start();
    /////////////////////////////////////////////////////////////////////
	
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
        if( wDistance < 8 )
            wDistance = 8;

        param[n++] = id;
        param[n++] = CM730::GetLowByte(wGoalPosition);
        param[n++] = CM730::GetHighByte(wGoalPosition);
        param[n++] = CM730::GetLowByte(wDistance);
        param[n++] = CM730::GetHighByte(wDistance);
    }
    cm730.SyncWrite(MX28::P_GOAL_POSITION_L, 5, JointData::NUMBER_OF_JOINTS - 1, param); // Opstaan gedeelte.

    usleep(1500000);
    
    
	Action::GetInstance()->m_Joint.SetEnableRightArmOnly(true, true);
	Action::GetInstance()->m_Joint.SetEnableLeftArmOnly(true, true);
	Head::GetInstance()->m_Joint.SetEnableHeadOnly(true, true);
	Walking::GetInstance()->m_Joint.SetEnableBodyWithoutHead(true, true);

	MotionManager::GetInstance()->SetEnable(true);
	Action::GetInstance()->LoadFile("/robotis/Data/motion_4096.bin");

	Walking::GetInstance()->LoadINISettings(ini);

	
	Action::GetInstance()->m_Joint.SetEnableBody(true, true);
	Action::GetInstance()->Start(60);
	while(Action::GetInstance()->IsRunning());
	Action::GetInstance()->m_Joint.SetEnableBody(false,false);

}

MotionClass::~MotionClass(){

}

