#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

/*
 * std::this_thread::get_id()
 */

class test_obj
{
public:
    int m_i;
    test_obj(int a):m_i(a){
        std::cout<<"address: "<<this<<" thread_id: "<<std::this_thread::get_id()<<" constructed\n";
    }
    
    test_obj(const test_obj &obj):m_i(obj.m_i){
        std::cout<<"address: "<<this<<" thread_id: "<<std::this_thread::get_id()<<" copied\n";
    }

    ~test_obj(){
        std::cout<<"address: "<<this<<" thread_id: "<<std::this_thread::get_id()<<" destructed\n";
    }
};

//void myprint(const int &i, const std::string &mybuf)
void myprint(const int &i, const test_obj &mybuf)
{
    std::cout<<"address: "<<&mybuf<<" thread_id: "<<std::this_thread::get_id()<<" function\n";
}

int main()
{
    std::cout<<"main thread is: "<<std::this_thread::get_id()<<"\n";
    
    int myfirstPar = 1;
    int mysecondPar = 12;
    
    //implicit type conversion contructor, which is constructed from child thread
    //std::thread myobj(myprint, myfirstPar, mysecondPar);
    
    //temporary object constructed, copied from main thread
    std::thread myobj(myprint, myfirstPar, test_obj(mysecondPar));
    myobj.join();
    //myobj.detach();
    
    return 0;
}
