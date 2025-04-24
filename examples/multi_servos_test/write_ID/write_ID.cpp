#include <iostream>
#include "SCServo.h"

SMS_STS sm_st;

int main(int argc, char **argv)
{

    for(int i = 0; i < 10; i++){
        if(argc<2){
            std::cout<<"argc error!"<<std::endl;
            return 0;
        }
        std::cout<<"serial:"<<argv[1]<<std::endl;
        if(!sm_st.begin(115200, argv[1])){
            std::cout<<"Failed to init sms/sts motor!"<<std::endl;
            return 0;
        }
        sm_st.unLockEprom(i);//打开EPROM保存功能
        std::cout<<"unLock Eprom"<<i<<std::endl;
	    sm_st.LockEprom(i);////关闭EPROM保存功能
        sm_st.end();
    }

}

