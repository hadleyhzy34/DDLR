#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

class player{
public:
    std::unique_lock<std::mutex> get_unique_lock()
    {
        std::unique_lock<std::mutex> lck(my_mutex, std::defer_lock);
        lck.lock(); //std::unique_lock::lock()
            
        std::unique_lock<std::mutex> tmp_lck(std::move(lck));
        return tmp_lck;
    }

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
            //std::unique_lock<std::mutex> lck(my_mutex,std::defer_lock);
            //lck.lock(); //std::unique_lock::lock()
            //std::cout<<"my_mutex address: "<<&my_mutex;

            //move mutex ownership
            std::unique_lock<std::mutex> lck_new = get_unique_lock();
            
            if(lck_new.owns_lock()){
                std::cout<<"lck_new owns the lock\n";
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
