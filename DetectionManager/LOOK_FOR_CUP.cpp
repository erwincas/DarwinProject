/*
 * StoppedState.cpp
 *
 *  Created on: May 7, 2017
 *      Author: rlarson
 */

#include "LOOK_FOR_CUP.h"
#include "DetectionManager.h"
#include "opencv2/opencv.hpp"


#include <iostream>

LOOK_FOR_CUP::LOOK_FOR_CUP()
: DetectionManagerState(std::string("LOOK FOR CUP")) {
}

LOOK_FOR_CUP::~LOOK_FOR_CUP() {
}

void LOOK_FOR_CUP::next(DetectionManager * manager)
{
	if(manager->cup.x >= 0)
	{
		manager->SetState(DetectionManager::ST_CALC);
	}
	else
	{
		manager->SetState(DetectionManager::ST_SEND);
	}
	
}
void LOOK_FOR_CUP::prev(DetectionManager * manager)
{

}
void LOOK_FOR_CUP::handle(DetectionManager * manager)
{
	std::cout << "Looking for cup..."<< std::endl;
	manager->cup = Rect(-1,-1,-1,-1);
	manager->distance = -1;	
	manager->detector->getPhoto();
	Mat filtered = manager->detector->filterRed();
	vector<RotatedRect> Rois = manager->detector->detectRoi(filtered);
    
	if(Rois.size()>0)
    {
	   std::cout << "Rois detected, detecting cup..."<< std::endl;
       //manager->cup = manager->detector->detectCup(Rois);
	   manager->cup = manager->detector->biggestROI(Rois);
    }

	std::cout << "cup x:" << manager->cup.x<< std::endl;
	
}


