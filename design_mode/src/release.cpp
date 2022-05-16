#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>



class player{
public:
    //entry of thread for receiving message
    void printX()
    {
        for(int i = 0; i < 1000; ++i)
        {
            std::unique_lock<std::mutex> lck(my_mutex,std::defer_lock);
            if(lck.try_lock() == true){
                std::cout<<"X";
            }else{
                std::cout<<"-";
            }
        }        
        return;
    }
    
    //entry of thread for sending message
    void printT()
    {
        for(int i = 0; i < 1000; ++i)
        {
            std::unique_lock<std::mutex> lck(my_mutex,std::defer_lock);
            lck.lock(); //std::unique_lock::lock()
            
            //lck no longer owns the mutex and mutex is locked
            std::mutex *ptx = lck.release(); //at this moment, pointer ptx that pointed to my_mutex is still locked
            std::cout<<lck.owns_lock();
            
            std::cout<<"/";
            ptx->unlock(); //otherwise both threads wouldnt run
        }
    }

private:
    std::mutex my_mutex; //build a new mutex obj1
};


int main(int, char**) {
    player user;
    std::thread myOutMsgObj(&player::printX, &user); //pass by reference
    std::thread myInMsgObj(&player::printT, &user);

    myOutMsgObj.join();
    myInMsgObj.join();

    //myobj.join();
    std::cout << "main thread is finished\n";
}
