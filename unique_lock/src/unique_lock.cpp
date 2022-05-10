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
            my_mutex.lock();
            std::unique_lock<std::mutex> guard(my_mutex, std::adopt_lock);
            std::cout<<"MSG received: "<<i<<std::endl;
            msgRecvQueue.push_back(i);
        }
    }
    
    bool outMsgCheck(int &command)
    {
        std::unique_lock<std::mutex> guard(my_mutex);

        std::chrono::milliseconds duration(5000); //5s
        std::this_thread::sleep_for(duration);

        if(!msgRecvQueue.empty()){
            command = msgRecvQueue.front(); //return first element without checking if it existed
            msgRecvQueue.pop_front(); //remove first element without return
            return true;
        }
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
    std::mutex my_mutex; //build a new mutex obj1
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
