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
    //std::future<int> result = std::async(mythread); //start a new thread
    std::future<int> result = std::async(std::launch::deferred, mythread); //start a new thread
    std::cout<<"continue...!\n";
        
    std::future_status status = result.wait_for(std::chrono::seconds(2));

    if(status == std::future_status::timeout)
    {
        //when thread is not fully executed and not returned yet
        std::cout<<"thread time out\n";
    }else if(status == std::future_status::ready)
    {
        //when main thread is finished here
        std::cout<<"mythread is executed"<<result.get()<<"\n";    
    }else if(status == std::future_status::deferred)
    {
        std::cout<<"thread deferred to be started\n";
        std::cout<<"result: "<<result.get()<<std::endl;
    }

    std::cout<<"main thread is ended here\n";
    return 0;
}
