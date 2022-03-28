#include <iostream>
#include <thread>

void myprint()
{
    std::cout<<"thread is started"<<std::endl;
    //..
    //..
    std::cout<<"thread is finished"<<std::endl;
}

int main(int, char**) {
    std::cout << "main thread is started!\n";
    std::thread myobj(myprint);
    //myobj.join();
    std::cout << "main thread is finished\n";
}
