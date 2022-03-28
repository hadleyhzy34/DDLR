#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <thread>

class threadTest
{
public:
    //default constructor
    threadTest(int id):myid(id){
        std::cout<<"constructor is called at this address: "<<this<<std::endl;
    }
    
    //copy constructor
    threadTest(const threadTest &tt):myid(tt.myid){
        std::cout<<"copy constructor is callled at this address: "<<this<<std::endl;
    }
    
    //move constructor
    threadTest(threadTest&& tt):myid(tt.myid){
        std::cout<<"move constructor is called at this address: "<<this<<std::endl;
    }

    ~threadTest(){
        std::cout<<"destructor is called at this address: "<<this<<std::endl;
    }

    void operator() ()
    {
        //std::this_thread::sleep_for(std::chrono::seconds(3));   //stay for 3 seconds
        std::cout<<"operator() is started"<<std::endl;
        //...
        std::cout<<"operator() is finished"<<std::endl;
    }

    void printtest(){
        std::cout<<"printtest is started"<<std::endl;
        //...
        //std::cout<<"this is test to see private data could be called."<<this->name<<std::endl;
        std::cout<<"printtest is finished"<<std::endl;
    }
private:
    int &myid;
    std::string name = "test";
};

int main(){ //main thread is generated and executed
    int myid = 5;
    
    threadTest tt(myid); 
    std::thread myfirstjob(&threadTest::printtest, tt); //std::thread obj(<class_static_member_function>, <obj/this pointer/reference obj>)
    myfirstjob.join();

    std::cout<<"--------------main thread is running 0--------------"<<std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(3));   //stay for 3 seconds

    threadTest ttt(myid); 
    
    threadTest &t = ttt;
    std::this_thread::sleep_for(std::chrono::seconds(3));   //stay for 3 seconds

    std::thread mysecondjob(t); //std::thread obj(<class_static_member_function>, <obj/this pointer/reference obj>)
    mysecondjob.join();

    std::cout<<"main thread is running 1"<<std::endl;
    

    return 0;
}
