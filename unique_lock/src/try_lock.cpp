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
            std::unique_lock<std::mutex> lck(my_mutex,std::try_to_lock);
            if(lck.owns_lock()){
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
            std::unique_lock<std::mutex> lck(my_mutex,std::try_to_lock);
            if(lck.owns_lock()){
                std::cout<<"T";
            }else{
                std::cout<<"*";
            }
        }
    }

private:
    std::list<int> msgRecvQueue; //message sent by player
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
