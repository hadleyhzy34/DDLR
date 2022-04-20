#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

void myprint(std::unique_ptr<int> ptr)
{
    std::cout<<"unique_ptr address: "<<&ptr<<" thread_id: "<<std::this_thread::get_id()<<" function\n";
}

int main()
{
    std::cout<<"main thread is: "<<std::this_thread::get_id()<<"\n";
    
    //smart pointer
    std::unique_ptr<int> ptr(new int(100));

    std::cout<<"unique_ptr address: "<<&ptr<<std::endl;

    //std::move to move unique_ptr to thread
    std::thread myobj(myprint, std::move(ptr));
    myobj.join();
    //myobj.detach();
    
    std::cout<<"unique_ptr value in main thread is: "<<ptr.get()<<std::endl;
    return 0;
}
