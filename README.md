# FTServo_Linux
FEETECH BUS Servo Linux library， add some HLSCL files written by ourselves
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

# 舵机运动范围限制
- ID:1 2040-2700
- ID:2 1500-2600
- ID:3 1100-2200
- ID:4 1050-2240