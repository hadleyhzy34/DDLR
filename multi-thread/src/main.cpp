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
    std::cout << "Hello, world!\n";
    std::thread myobj(myprint);
    myobj.join();
}
