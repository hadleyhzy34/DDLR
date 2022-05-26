#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>

class user{
public:
    //demo to show how object-oriented new async thread
    int mythread(int temp)
    {
        std::cout<<"mythread started: "<<std::this_thread::get_id()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"mythread end"<<std::this_thread::get_id()<<std::endl;
        return temp;
    }
    //demo to show how object-oriented new async thread with extra argument
    //std::launch::deferred: thread is started to be executed until std::future::wait() or std::future::get()
    //question: will it be executed when get/wait is not called: thread will not be created
    //this thread will be executed in main thread
    //std::launch::async: thread is started once thread is declared
    int newthread(int temp)
    {
        std::cout<<"mythread started: "<<std::this_thread::get_id()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"mythread end"<<std::this_thread::get_id()<<std::endl;
        return temp;
    }
};

int main(){
    user a;
    int temp = 12;
    std::cout<<"main thread is: "<<std::this_thread::get_id()<<std::endl;
    //std::future<int> result = std::async(&user::newthread, &a, temp); //start a new thread, which defaulty uses std::launch::async
    //std::future<int> result = std::async(std::launch::deferred, &user::newthread, &a, temp); //start a new thread
    std::future<int> result = std::async(std::launch::async, &user::newthread, &a, temp); //start a new thread
    std::cout<<"continue...!\n";
    std::cout<<"continue...!\n";
    std::cout<<"continue...!\n";
    std::cout<<"continue...!\n";
    std::cout<<"continue...!\n";

    //result.wait();
    std::cout<<result.get()<<std::endl;
    //std::cout<<result.get()<<std::endl;// async method cannot be called twice
    std::cout<<"main thread is gonna ended\n"; //even comment get() or wait(), system would still wait async thread to be returned to return main program
    return 0;
}
