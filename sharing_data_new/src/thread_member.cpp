#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

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

    void thread_work(int num)
    {
        std::cout<<"address: "<<this<<" thread_id: "<<std::this_thread::get_id()<<" child thread\n";
    }

    void operator()(int num)
    {
        std::cout<<"address: "<<this<<" thread_id: "<<std::this_thread::get_id()<<" child() thread\n";
    }
};

void myprint(const int &i, test_obj &mybuf)
{
    mybuf.m_i = 120; //it's not gonna change value in the main thread
    std::cout<<"address: "<<&mybuf<<" thread_id: "<<std::this_thread::get_id()<<" function\n";
}

int main()
{
    test_obj test(10);

    // &test == std::ref(test)
    //std::thread myobj(&test_obj::thread_work, std::ref(test), 15);
    
    //same address, &variable: reference of variable
    //std::thread myobj(&test_obj::thread_work, &test, 15);

    //construct + copy
    //std::thread myobj(&test_obj::thread_work, test, 15);

    //new thread based on object, construct and copy
    //std::thread myobj(test, 15);

    //new thread based on object, std::ref, construct without copy
    //in this case, &test != std::ref(), `&test` compiles with error
    std::thread myobj(std::ref(test), 15);
    myobj.join();
    
    std::cout<<"m_i value in main thread is: "<<std::endl;
    return 0;
}
