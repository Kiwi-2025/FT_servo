# FTServo_Linux
FEETECH BUS Servo Linux library

## File-tree structure

├── examples 
│   ├── multi_servos_test
│   └── SMS_STS
├── README.md
└── src
    ├── CMakeCache.txt
    ├── CMakeFiles
    ├── cmake_install.cmake
    ├── CMakeLists.txt
    ├── Finger.cpp
    ├── Finger.h    # 自制Finger系列串行舵机应用层程序
    ├── INST.h      # 飞特串行舵机协议指令定义                  *
    ├── libSCServo.a
    ├── Makefile
    ├── SCSCL.cpp
    ├── SCSCL.h     # 飞特SCSCL系列串行舵机应用层程序
    ├── SCS.cpp
    ├── SCSerial.cpp
    ├── SCSerial.h  # 飞特串行舵机硬件接口层程序                *
    ├── SCServo.h   # 飞特串行舵机接口                        *
    ├── SCS.h       # 飞特串行舵机通信层协议程序                *
    ├── SMSBL.cpp
    ├── SMSBL.h     # 飞特SMSBL系列串行舵机应用层程序
    ├── SMSCL.cpp
    ├── SMSCL.h     # 飞特SMSCL系列串行舵机接口             
    ├── SMS_STS.cpp
    └── SMS_STS.h   # 飞特SMS/STS系列串行舵机应用层程序         *

带星号的文件是比较重要的文件，其中应用层程序比硬件接口层程序更常用一些

# Static library libSCServo.a
- cd src
- cmake .
- make

# TEST
- cd examples/SMS_STS/WritePos
- cmake .
- make
- sudo ./WritePos /dev/ttyUSB0

# 手动更改内存表操作步骤
- Ping舵机，确定现在的舵机的ID
- ProgramEPROM，将舵机的ID写入EPROM
- Ping不需要断电，重新上电
- 运动之前需要断电，重新上电