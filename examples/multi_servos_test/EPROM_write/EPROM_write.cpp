#include <iostream>
#include "SCServo.h"

SMS_STS sm_st;

int main(int argc, char **argv)
{
	if(argc<2){
        std::cout<<"argc error!"<<std::endl;
        return 0;
	}
	std::cout<<"serial:"<<argv[1]<<std::endl;
    if(!sm_st.begin(1000000, argv[1])){
        std::cout<<"Failed to init sms/sts motor!"<<std::endl;
        return 0;
    }
	

	//choose to write the ID or baud rate to EPROM, or skip
	while(1){
		//Ping servo ID, check the ID of the servo used now 
		int ID = sm_st.Ping(0xFE);
		if(ID!=-1){
			std::cout<<"connect servo ID:"<<ID<<std::endl;
		}else{
			std::cout<<"Ping servo ID error!"<<std::endl;
		}

		std::cout<<"choose to write the ID(1) or baud rate to EPROM(2), or skip(0):"<<std::endl;
		int choice;
		std::cin>>choice;
		switch(choice){
			case 0:
				std::cout<<"skip"<<std::endl;
				sm_st.end();
				return 0;
			
			case 1: //write ID to EPROM
				//input the ID of the servo you want to write to EPROM
				int ID_new;
				std::cout<<"input the ID you want to write to EPROM:"<<std::endl;
				std::cin>>ID_new;
				std::cout<<"ID_new:"<<ID_new<<std::endl;

				sm_st.unLockEprom(ID);//打开EPROM保存功能
				std::cout<<"unLock Eprom"<<std::endl;
				sm_st.writeByte(ID, SMS_STS_ID, ID_new);//ID
				std::cout<<"Servo "<<ID<<" write ID:"<<ID_new<<std::endl;
				sm_st.LockEprom(ID_new);//关闭EPROM保存功能
				std::cout<<"Servo "<<sm_st.readByte(ID_new, SMS_STS_ID)<<"Lock Eprom"<<std::endl;
				
				break;

			case 2: //write baud rate to EPROM
		
				//input the ID of the servo you want to write to EPROM
				int baud_new;
				std::cout<<"input the baud rate you want to write to EPROM:"<<std::endl;
				std::cin>>baud_new;
				std::cout<<"input baud:"<<baud_new<<std::endl;

				sm_st.unLockEprom(ID);//打开EPROM保存功能
				std::cout<<"unLock Eprom"<<std::endl;
				sm_st.writeByte(ID, SMS_STS_BAUD_RATE, baud_new);//change baud rate
				std::cout<<"Servo "<<ID<<" write baud rate:"<<sm_st.readByte(ID, SMS_STS_BAUD_RATE)<<std::endl;
				sm_st.LockEprom(ID);//关闭EPROM保存功能
				std::cout<<"Servo "<<ID<<"Lock Eprom"<<std::endl;
				
				break;
		
		}


	}

	return 0;
}
