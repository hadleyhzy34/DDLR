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
        for(int i = 0; i < 1000; ++i)
        {
            std::lock(my_mutex_1, my_mutex_2);
            //my_mutex_1.lock(); //lock mutex 1
            //...
            //my_mutex_2.lock(); //lock mutex 2
            std::cout<<"MSG received: "<<i<<std::endl;
            msgRecvQueue.push_back(i);
            my_mutex_2.unlock();
            my_mutex_1.unlock();
        }
    }
    
    bool outMsgCheck(int &command)
    {
        std::lock(my_mutex_1,my_mutex_2);
        //std::adapt_lock assuem the calling thread already has onwership of the mutex
        std::lock_guard<std::mutex> guard_1(my_mutex_1, std::adopt_lock);
        std::lock_guard<std::mutex> guard_2(my_mutex_2, std::adopt_lock);

        if(!msgRecvQueue.empty()){
            command = msgRecvQueue.front(); //return first element without checking if it existed
            msgRecvQueue.pop_front(); //remove first element without return
            //my_mutex_2.unlock();
            //my_mutex_1.unlock();
            return true;
        }
        //my_mutex_2.unlock();
        //my_mutex_1.unlock();
        return false;
    }

    //entry of thread for sending message
    void outMsgRecvQueue()
    {
        int command = -1;
        for(int i = 0; i < 1000; ++i)
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
    std::mutex my_mutex_1; //build a new mutex obj1
    std::mutex my_mutex_2; //build a new mutex obj2
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
