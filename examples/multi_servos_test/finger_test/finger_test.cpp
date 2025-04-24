#include<iostream>
#include"Finger.h"

u8 ID[4] = {1, 2, 3, 4};
s16 Position[4];
u16 Speed[4] = {2400, 2400, 2400, 2400};
u8 ACC[4] = {50, 50, 50, 50};
s16 pos_upper_lim[4] = {4095, 4095, 4095, 4095};
s16 pos_lower_lim[4] = {0, 0, 0, 0};

int main(int argc, char** argv)
{   
    //check the number of arguments
    //argv[1] are the serial ports for 4 servos
    if(argc<2){
        std::cout<<"argc error!"<<std::endl;
        return 0;
	}
    std::cout<<"serial:"<<argv[1]<<std::endl;
    
    //create a finger object
    Finger thumb(argv[1], ID, Speed, ACC, pos_upper_lim, pos_lower_lim);
    thumb.Info();
    thumb.SyncWritePos(Position);
    thumb.SyncRead();

    return 0;
}