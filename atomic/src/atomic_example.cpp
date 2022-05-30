#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>

std::atomic<int> g_count(0); //global variable
std::mutex g_mtx;
int count = 0;

void newthread()
{
    for(int i = 0; i < 1000000; i++)
    {
        //g_mtx.lock();
        g_count++;
        //g_mtx.unlock();
    }
    return;
}

void mythread()
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
    auto start = std::chrono::system_clock::now();
    std::thread th1(newthread);
    std::thread th2(newthread);

    th1.join();
    th2.join();
    
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout<<"count value is: "<< g_count <<std::endl;
    std::cout<< elapsed_seconds.count() <<std::endl;
    
    auto start1 = std::chrono::system_clock::now();
    std::thread th3(mythread);
    std::thread th4(mythread);

    th3.join();
    th4.join();
    
    auto end1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
    std::cout<<"count value is: "<< count <<std::endl;
    std::cout<< elapsed_seconds1.count() <<std::endl;

    return 0;
}
