/*
舵机出厂速度单位是0.0146rpm，速度改为V=2400
*/

#include <iostream>
#include "SCServo.h"

HLSCL hlscl;

u8 ID[4] = {1, 2, 3, 4};
s16 Position[4];
u16 Speed[4] = {200, 200, 200, 200};
u8 ACC[4] = {20, 20, 20, 20};
u16 Torque[4] = {600, 600, 600, 600};
int main(int argc, char **argv)
{
	if(argc<2){
        std::cout<<"argc error!"<<std::endl;
        return 0;
	}
	std::cout<<"serial:"<<argv[1]<<std::endl;
    if(!hlscl.begin(115200, argv[1])){
        std::cout<<"Failed to init sms/sts motor!"<<std::endl;
        return 0;
    }
/*- ID:1 2040-2700
- ID:2 1500-2600
- ID:3 1100-2200
- ID:4 1050-2240*/
	while(1){
		Position[0] = 2500;
		Position[1] = 2300;
		Position[2] = 2000;
		Position[3] = 2040;
		hlscl.SyncWritePosEx(ID, sizeof(ID), Position, Speed, ACC, Torque);//舵机(ID1/ID2)以最高速度V=2400(步/秒)，加速度A=50(50*100步/秒^2)，运行至P1=4095位置
		std::cout<<"state 1"<<std::endl;
		usleep(3000*1000);//[(P1-P0)/V]*1000+[V/(A*100)]*1000
  
		Position[0] = 2300;
		Position[1] = 1800;
		Position[2] = 1500;
		Position[3] = 1550;
		hlscl.SyncWritePosEx(ID, sizeof(ID), Position, Speed, ACC, Torque);//舵机(ID1/ID2)以最高速度V=2400(步/秒)，加速度A=50(50*100步/秒^2)，运行至P0=0位置
		std::cout<<"state 2"<<std::endl;
		usleep(3000*1000);//[(P1-P0)/V]*1000+[V/(A*100)]*1000
	}
	hlscl.end();
	return 1;
}

