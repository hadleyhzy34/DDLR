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

            //std::chrono::milliseconds duration(2000);
            //std::this_thread::sleep_for(duration);

            if(lck.owns_lock()){  //lck always owns lock at this time, '*' should never be printed
                std::cout<<"T";
                lck.unlock();
            }else{
                std::cout<<"*";
            }
            std::cout<<"/";
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
