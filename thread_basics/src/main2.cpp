#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <thread>


int main(){ //main thread is generated and executed
    auto mythread = [] {
        std::cout<<"my lamda thread is started"<<std::endl;
        //...
        std::cout<<"my lamda thread is finished"<<std::endl;
    };

    std::thread myobj(mythread);
    myobj.join();

    std::this_thread::sleep_for(std::chrono::seconds(3));   //stay for 3 seconds

    return 0;
}
