/*
同步读指令，回读ID1与ID2两个舵机的位置与速度信息
*/

#include <iostream>
#include "SCServo.h"

HLSCL hlscl;
uint8_t ID[] = {1, 2, 3, 4};
uint8_t rxPacket[4];
int16_t Position;
int16_t Speed;

int main(int argc, char **argv)
{
	if(argc<2){
        std::cout<<"argc error!"<<std::endl;
        return 0;
	}
	std::cout<<"serial:"<<argv[1]<<std::endl;
    if(!hlscl.begin(115200, argv[1])){
        std::cout<<"Failed to init HLSCL motor!"<<std::endl;
        return 0;
    }
	hlscl.syncReadBegin(sizeof(ID), sizeof(rxPacket));
	while(1){
		hlscl.syncReadPacketTx(ID, sizeof(ID), SMS_STS_PRESENT_POSITION_L, sizeof(rxPacket));//同步读指令包发送
		for(uint8_t i=0; i<sizeof(ID); i++){
			//接收ID[i]同步读返回包
			if(!hlscl.syncReadPacketRx(ID[i], rxPacket)){
				std::cout<<"ID:"<<(int)ID[i]<<" sync read error!"<<std::endl;
				continue;//接收解码失败
			}
			Position = hlscl.syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位,参数=0表示无方向位
			Speed = hlscl.syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位,参数=0表示无方向位
			std::cout<<"ID:"<<int(ID[i])<<" Position:"<<Position<<" Speed:"<<Speed<<std::endl;
		}
		usleep(1000*1000);
	}
	hlscl.syncReadEnd();
	hlscl.end();
	return 1;
}

