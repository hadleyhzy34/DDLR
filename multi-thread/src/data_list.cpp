#include <iostream>
#include <vector>
#include <thread>
#include <list>

class player{
public:
    //entry of thread for receiving message
    void inMsgRecvQueue()
    {
        for(int i = 0; i < 100000; ++i)
        {
            //std::cout<<"MSG received: "<<i<<std::endl;
            msgRecvQueue.push_back(i);
        }
    }

    //entry of thread for sending message
    void outMsgRecvQueue()
    {
        for(int i = 0; i < 100000; ++i)
        {
            if(!msgRecvQueue.empty())
            {
                int command = msgRecvQueue.front(); //return first element without checking if it existed
                msgRecvQueue.pop_front(); //remove first element without return

                //handling incoming message
                //...
            }else
            {
                //std::cout<<"outMsgRecvQueue is empty: "<<i<<std::endl;
            }
        }
        std::cout<<"end"<<std::endl;
    }

private:
    std::list<int> msgRecvQueue; //message sent by player
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
