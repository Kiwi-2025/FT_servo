/*
 * Finger.h
 * 飞特串行舵机通信层协议程序
 * 日期: 2025.04.17
 * 作者: 
 */

#include"SMS_STS.h"
#include <iostream>
#include <iomanip>

#ifndef _FINGER_H
#define _FINGER_H
class Finger
{
private:
    SMS_STS *sts;
    u8 ID[4] = {1, 2, 3, 4};
    s16 Position[4];
    u16 Speed[4] = {2400, 2400, 2400, 2400};
    u8 ACC[4] = {50, 50, 50, 50};
    s16 Pos_upper_lim[4] = {4095, 4095, 4095, 4095};
    s16 Pos_lower_lim[4] = {0, 0, 0, 0};
public:
    Finger();
    Finger(const char* pin);
    Finger(const char* pin, u8 id[4], u16 speed[4], u8 acc[4], s16 upper_lim[4], s16 lower_lim[4]);
    void SetPin(const char* pin);
    void Info();
    void SyncWritePos(s16 pos[4]);//同步写入位置
    void SyncRead(bool infinite = false);//同步读取位置，支持循环读和单次读,默认单次读
    void SetID(u8 id[4]);//设置ID
    void SetSpeed(u16 speed[4]);//设置速度
    void SetACC(u8 acc[4]);//设置加速度
    void SetUpperLim(s16 upper_lim[4]);//设置运动上限
    void SetLowerLim(s16 lower_lim[4]);//设置运动下限

};

#endif // _FINGER_H
