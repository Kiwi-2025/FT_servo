#include "Finger.h"


Finger::Finger(const char* pin)
{
    sts = new SMS_STS();
    //check if the baud rate is correct
    if(!sts->begin(115200, pin)){
        std::cout<<"Failed to init sms/sts motor!"<<std::endl;
        return;
    }
    std::cout<<"Init port: "<<pin<<std::endl;

    //check if the motor is connected
    for(int i=0; i<4; i++){
        if(ID[i]!= sts->Ping(i)){
            std::cout<<"Ping servo"<<i+1<<" error!"<<std::endl;
            return;
        }
    }
    std::cout<<"Ping servo successfully connected!"<<std::endl;

    std::cout<<"Init sms/sts motor successfully!"<<std::endl;
}

Finger::Finger(const char* pin, u8 id[4], u16 speed[4], u8 acc[4], s16 upper_lim[4], s16 lower_lim[4])
{
    sts = new SMS_STS();
    //check if the baud rate is correct
    if(!sts->begin(115200, pin)){
        std::cout<<"Failed to init sms/sts motor!"<<std::endl;
        return;
    }
    std::cout<<"Init port: "<<pin<<std::endl;

    //check if the motor is connected
    for(int i=0; i<4; i++){
        if(ID[i]!= sts->Ping(i)){
            std::cout<<"Ping servo"<<i+1<<" error!"<<std::endl;
            return;
        }
    }
    std::cout<<"Ping servo successfully connected!"<<std::endl;

    //set ID, speed, acc, upper limit and lower limit
    SetID(id);
    SetSpeed(speed);
    SetACC(acc);
    SetUpperLim(upper_lim);
    SetLowerLim(lower_lim);

    std::cout<<"Init sms/sts motor successfully!"<<std::endl;
}

void Finger::SetPin(const char* pin)
{
    //check if finger is inited
    if (sts) {
        std::cout << "SMS_STS object has been initialized!" << std::endl;
        return;
    }
    sts->begin(115200, pin);
    std::cout<<"Init port: "<<pin<<std::endl;

    //check if the motor is connected
    for(int i=0; i<4; i++){
        if(ID[i]!= sts->Ping(i)){
            std::cout<<"Ping servo"<<i+1<<" error!"<<std::endl;
            return;
        }
    }
    std::cout<<"Ping servo successfully connected!"<<std::endl;

    std::cout<<"Init sms/sts motor successfully!"<<std::endl;
}

void Finger::Info()
{
    if (!sts) {
        std::cout << "SMS_STS object not initialized!" << std::endl;
        return;
    }

    // Sync read to update Position and Speed
    SyncRead(false);

    // Print table header
    std::cout << std::setw(10) << "Servo ID" 
              << std::setw(10) << "Speed" 
              << std::setw(10) << "ACC" 
              << std::setw(10) << "Position" 
              << std::setw(10) << "Upper Lim" 
              << std::setw(10) << "Lower Lim" 
              << std::endl;

    // Print separator line
    std::cout << std::setw(10) << "--------" 
              << std::setw(10) << "-----" 
              << std::setw(10) << "---" 
              << std::setw(10) << "--------" 
              << std::setw(10) << "---------" 
              << std::setw(10) << "---------" 
              << std::endl;

    // Print each motor's information
    for(int i = 0; i < 4; i++){
        std::cout << std::setw(10) << (int)ID[i] 
                  << std::setw(10) << Speed[i] 
                  << std::setw(10) << (int)ACC[i] 
                  << std::setw(10) << Position[i] 
                  << std::setw(10) << Pos_upper_lim[i] 
                  << std::setw(10) << Pos_lower_lim[i] 
                  << std::endl;
    }
}

void Finger::SyncWritePos(s16 pos[4])
{   
    //对pos进行检查，防止转动到超出范围区域
    for(int i=0; i<4; i++){
        pos[i] > Pos_upper_lim[i] ? Position[i] = Pos_upper_lim[i] : pos[i];
        pos[i] < Pos_lower_lim[i] ? Position[i] = Pos_lower_lim[i] : pos[i];
    }
    //同步写入位置
    sts->SyncWritePosEx(ID, sizeof(ID), Position, Speed, ACC);
    sts->end();
}

void Finger::SyncRead(bool infinite)
{   
    //check if finger is inited
    if (!sts) {
        std::cout << "SMS_STS object not initialized!" << std::endl;
        return;
    }

    uint8_t rxPacket[8];
    int16_t Pos, Velocity;
    sts->syncReadBegin(sizeof(ID), sizeof(rxPacket));

    //循环读取位置和速度
	while(infinite){
		sts->syncReadPacketTx(ID, sizeof(ID), SMS_STS_PRESENT_POSITION_L, sizeof(rxPacket));//同步读指令包发送
		for(uint8_t i=0; i<sizeof(ID); i++){
			//接收ID[i]同步读返回包
			if(!sts->syncReadPacketRx(ID[i], rxPacket)){
				std::cout<<"ID:"<<(int)ID[i]<<" sync read error!"<<std::endl;
				continue;//接收解码失败
			}
			Pos = sts->syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位,参数=0表示无方向位
			Velocity = sts->syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位,参数=0表示无方向位
			std::cout<<"Servo ID:"<<int(ID[i])<<" Position:"<<Pos<<" Speed:"<<Velocity<<std::endl;
		}
		usleep(10*1000);
	}

    //单次读取位置和速度
    sts->syncReadPacketTx(ID, sizeof(ID), SMS_STS_PRESENT_POSITION_L, sizeof(rxPacket));//同步读指令包发送
	for(uint8_t i=0; i<sizeof(ID); i++){
		//接收ID[i]同步读返回包
		if(!sts->syncReadPacketRx(ID[i], rxPacket)){
			std::cout<<"ID:"<<(int)ID[i]<<" sync read error!"<<std::endl;
			continue;//接收解码失败
		}
		Pos = sts->syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位,参数=0表示无方向位
		Velocity = sts->syncReadRxPacketToWrod(15);//解码两个字节 bit15为方向位,参数=0表示无方向位
		std::cout<<"ID:"<<int(ID[i])<<" Position:"<<Pos<<" Speed:"<<Velocity<<std::endl;
	}

	sts->syncReadEnd();
	sts->end();
}

void Finger::SetID(u8 id[4])
{
    //check if finger is inited
    if (!sts) {
        std::cout << "SMS_STS object not initialized!" << std::endl;
        return;
    }

    for(int i=0; i<4; i++){
        ID[i] = id[i];
    }
}

void Finger::SetSpeed(u16 speed[4])
{
    //check if finger is inited
    if (!sts) {
        std::cout << "SMS_STS object not initialized!" << std::endl;
        return;
    }

    for(int i=0; i<4; i++){
        Speed[i] = speed[i];
    }
}

void Finger::SetACC(u8 acc[4])
{
    //check if finger is inited
    if (!sts) {
        std::cout << "SMS_STS object not initialized!" << std::endl;
        return;
    }

    for(int i=0; i<4; i++){
        ACC[i] = acc[i];
    }
}

void Finger::SetUpperLim(s16 upper_lim[4])
{
    //check if finger is inited
    if (!sts) {
        std::cout << "SMS_STS object not initialized!" << std::endl;
        return;
    }

    for(int i=0; i<4; i++){
        Pos_upper_lim[i] = upper_lim[i];
    }
}

void Finger::SetLowerLim(s16 lower_lim[4])
{
    //check if finger is inited
    if (!sts) {
        std::cout << "SMS_STS object not initialized!" << std::endl;
        return;
    }

    for(int i=0; i<4; i++){
        Pos_lower_lim[i] = lower_lim[i];
    }
}