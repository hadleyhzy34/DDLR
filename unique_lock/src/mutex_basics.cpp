#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

class player{
public:
    //entry of thread for receiving message
    void inMsgRecvQueue()
    {
        for(int i = 0; i < 100; ++i)
        {
            std::cout<<"MSG received: "<<i<<std::endl;
            
            my_mutex.lock();
            msgRecvQueue.push_back(i);
            my_mutex.unlock();
        }
    }
    
    bool outMsgCheck(int &command)
    {
        my_mutex.lock();
        if(!msgRecvQueue.empty()){
            command = msgRecvQueue.front(); //return first element without checking if it existed
            //std::cout<<"first element is: "<<command<<std::endl;
            msgRecvQueue.pop_front(); //remove first element without return
            my_mutex.unlock();
            return true;
        }
        my_mutex.unlock();
        return false;
    }

    //entry of thread for sending message
    void outMsgRecvQueue()
    {
        int command = -1;
        for(int i = 0; i < 100; ++i)
        {
            bool result = outMsgCheck(command);
            if(result == true)
            {
                std::cout<<"outMsg executed, "<<command<<std::endl;
            }
            else
            {
                std::cout<<"outMsgRecvQueue is empty: "<<i<<std::endl;
            }
        }
        std::cout<<"end front value is: "<<command<<std::endl;
    }

private:
    std::list<int> msgRecvQueue; //message sent by player
    std::mutex my_mutex; //build a new mutex obj
};


int main(int, char**) {
    player user;
    std::thread myOutMsgObj(&player::outMsgRecvQueue, &user); //pass by reference
    std::thread myInMsgObj(&player::inMsgRecvQueue, &user);

    myOutMsgObj.join();
    myInMsgObj.join();


    //myobj.join();
    std::cout << "main thread is finished\n";
}
