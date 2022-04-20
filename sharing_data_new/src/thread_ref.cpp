#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

/*
 using reference to pass object to thread will not affect object that declared in main thread
 since object in the main thread does not share the same memory as the one in child thread
 */

class test_obj
{
public:
    int m_i; //m_i can be modified regardless of const
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
//invoke reference must be added with `const` which means variables cannot be modified
//unless its invoked with std::ref
void myprint(const int &i, test_obj &mybuf)
{
    mybuf.m_i = 120; //it's not gonna change value in the main thread
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
    test_obj test_1(mysecondPar);
    //std::thread myobj(myprint, myfirstPar, test_1);
    std::thread myobj(myprint, myfirstPar, std::ref(test_1));
    myobj.join();
    //myobj.detach();
    
    std::cout<<"m_i value in main thread is: "<<test_1.m_i<<std::endl;
    return 0;
}
