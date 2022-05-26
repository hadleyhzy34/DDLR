#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>

//demo to show how object-oriented new async thread
int mythread(int temp)
{
    std::cout<<"mythread started: "<<std::this_thread::get_id()<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"mythread end "<<std::this_thread::get_id()<<std::endl;
    return temp;
}

int main(){
    std::cout<<"main thread is: "<<std::this_thread::get_id()<<std::endl;

    std::packaged_task<int(int)> myobj(mythread);
    std::thread p1(std::ref(myobj), 2); //pass 2 as user::mythread input argument
    p1.join();
    
    std::future<int> res0 = myobj.get_future(); //std::future contains return result for packaged thread
    std::cout<<res0.get() <<std::endl; 
    
    //lambda function as args for packaged_task
    std::packaged_task<int(int)> newPkg([](int args){
        std::cout<<"mythread started: "<<std::this_thread::get_id()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"mythread end "<<std::this_thread::get_id()<<std::endl;
        return args;
    });
    
    std::thread p2(std::ref(newPkg), 5); //pass 2 as user::mythread input argument
    p2.join();
    
    std::future<int> res1 = newPkg.get_future(); //std::future contains return result for packaged thread
    std::cout<<res1.get() <<std::endl; 

    std::packaged_task<int(int)> newPkg1([](int args){
        std::cout<<"mythread started: "<<std::this_thread::get_id()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"mythread end "<<std::this_thread::get_id()<<std::endl;
        return args;
    });
    
    std::cout<<"before lambda function is called\n";
    newPkg1(100); //call this lambda function directly in the main thread
    std::cout<<"package task is called"<<std::endl;
    std::future<int> res2 = newPkg1.get_future();
    std::cout<<res2.get()<<std::endl;
    
    std::packaged_task<int(int)> newPkg2([](int args){
        std::cout<<"mythread started: "<<std::this_thread::get_id()<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"mythread end "<<std::this_thread::get_id()<<std::endl;
        return args;
    });
    

    std::vector<std::packaged_task<int(int)>> tasks; //vector container for packaged_task
    //demo to show how to call element/packaged_task in vector container
    tasks.push_back(std::move(newPkg2)); //move a new container
    
    //pass to another packaged_task
    std::packaged_task<int(int)> newPkg3;
    auto iter = tasks.begin();
    newPkg3 = std::move(*iter); //delete first iter
    tasks.erase(iter); //no longer available to use iter

    newPkg3(200);
    std::future<int> res3 = newPkg3.get_future();
    std::cout<<res3.get()<<std::endl;
    return 0;
}
