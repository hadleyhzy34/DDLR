#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>

int g_count = 0; //global variable
std::mutex g_mtx;

void newthread()
{
    for(int i = 0; i < 1000000; i++)
    {
        g_mtx.lock();
        g_count++;
        g_mtx.unlock();
    }
    return;
}

int main(){
    std::thread th1(newthread);
    std::thread th2(newthread);

    th1.join();
    th2.join();
    
    std::cout<<"count value is: "<<g_count<<std::endl;
    return 0;
}
