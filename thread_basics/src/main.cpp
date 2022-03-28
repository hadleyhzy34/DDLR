#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <thread>

void myprint(){
    std::cout<<"thread is started "<<std::endl;

    std::cout<<"thread is finished "<<std::endl;
}

void printtest(){
    std::cout<<"thread is running 1\n"<<std::endl;
    std::cout<<"thread is running 2\n"<<std::endl;
    std::cout<<"thread is running 3\n"<<std::endl;
    std::cout<<"thread is running 4\n"<<std::endl;
    std::cout<<"thread is running 5\n"<<std::endl;
    //std::cout<<"thread is running 6\n"<<std::endl;
    //std::cout<<"thread is running 7\n"<<std::endl;
    //std::cout<<"thread is running 8\n"<<std::endl;
    //std::cout<<"thread is running 9\n"<<std::endl;
}

class threadTest
{
    void operator() ()
    {
        std::cout<<"operator() is started"<<std::endl;
        //...
        std::cout<<"operator() is finished"<<std::endl;
    }
};

int main(){ //main thread is generated and executed
    //std::thread myjob(myprint); //child thread is generated, thread execution entry point is function myprint and executed
    std::thread myjob(printtest);

    //joinable
    if(myjob.joinable())
    {
        std::cout<<"1: joinable == true"<<std::endl;
    }else{
        std::cout<<"1: joinable == false"<<std::endl;
    }

    //myjob.join(); 
    myjob.detach();
    
    if(myjob.joinable())
       {
           std::cout<<"2: joinable == true"<<std::endl;
       }else{
           std::cout<<"2: joinable == false"<<std::endl;
       }


    std::cout<<"main thread is running 0"<<std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(3));   //stay for 3 seconds
    return 0;
}
