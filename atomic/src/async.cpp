#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>

int mythread()
{
    std::cout<<"mythread started: "<<std::this_thread::get_id()<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"mythread end"<<std::this_thread::get_id()<<std::endl;
    return 1;
}

int main(){
    std::cout<<"main thread is: "<<std::this_thread::get_id()<<std::endl;
    std::future<int> result = std::async(mythread); //start a new thread
    std::cout<<"continue...!\n";
    
    result.wait();
    //std::cout<<result.get()<<std::endl;
    //std::cout<<result.get()<<std::endl;// async method cannot be called twice
    return 0;
}
