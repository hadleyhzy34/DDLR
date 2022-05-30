#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>

std::atomic<int> g_count(0); //global variable
std::atomic<bool> g_ifend(false);

void mythread()
{
    std::chrono::milliseconds duration(1000);
    while(g_ifend == false)
    {
        std::cout<<"thread id = "<<std::this_thread::get_id()<<"running ... \n";
        std::this_thread::sleep_for(duration);
    }
    std::cout<<"mythread ended here\n";
}



int main(){
    std::thread th1(mythread);
    std::thread th2(mythread);
    
    std::chrono::milliseconds duration(5000);
    std::this_thread::sleep_for(duration);
    g_ifend = true;
    th1.join();
    th2.join();
    
    return 0;
}
