#!/bin/sh

sudo ./StateServer/StateServer & > ~/logs/state_server.log
sudo ./DetectionManager/DetectionManager & > ~/logs/detection_manager.log
sudo ./MotionManager/MotionManager & > ~/logs/motion_manager.log
