# FTServo_Linux
FEETECH BUS Servo Linux library
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