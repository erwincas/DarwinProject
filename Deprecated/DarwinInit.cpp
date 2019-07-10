/* Initialise Darwin class file */
#include "DarwinInit.hpp"

DarwinInit::DarwinInit() {
	printf(" In constructor \n" );	
	change_current_dir();

	linux_cm730 = new LinuxCM730(U2D_DEV_NAME);
	cm730 = new CM730(linux_cm730);
	ini = new minIni(INI_FILE_PATH);

	framework_init();
}

 
void DarwinInit::change_current_dir()
{
     char exepath[1024] = {0};
     if(readlink("/proc/self/exe", exepath, sizeof(exepath)) != -1)
     chdir(dirname(exepath));
}

bool DarwinInit::framework_init(void) {
     printf(" In Framework init \n" );
     if(MotionManager::GetInstance()->Initialize(cm730) == false)
     {
         printf("Fail to initialize Motion Manager!\n");
         return 0;
     }
 
     MotionManager::GetInstance()->AddModule((MotionModule*)Action::GetInstance());
     LinuxMotionTimer *motion_timer = new LinuxMotionTimer(MotionManager::GetInstance());
     motion_timer->Start();

     MotionManager::GetInstance()->LoadINISettings(ini);

     Action::GetInstance()->LoadFile(MOTION_FILE_PATH);

     Action::GetInstance()->m_Joint.SetEnableBody(true, true);
     MotionManager::GetInstance()->SetEnable(true);
     Action::GetInstance()->Start(15);
     while(Action::GetInstance()->IsRunning()) usleep(8*1000);

     return true;
} 


