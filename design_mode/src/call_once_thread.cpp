#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

std::mutex src;
std::once_flag g_flag;

class player{
private:
    player(){}; //constructor in privacy
    static player *user_instance; //static member

public:
    static player *getInstance(){
        std::call_once(g_flag,CreateInstance);
        std::cout<<"call_once is called"<<std::endl;
        return user_instance;
    }

    void func(){
        std::cout<<"to testify singleton mode point to same object"<<this<<std::endl;
    }
    
    static void CreateInstance(){
        std::chrono::milliseconds duration(2000);
        std::this_thread::sleep_for(duration);

        user_instance = new player();
        static destructPlayer dp; //instantiate static member so that it will be called() when the object destructed
    }

    class destructPlayer{
    public:
        ~destructPlayer(){
            if(player::user_instance){
                delete user_instance;
                player::user_instance = NULL;
            }
            std::cout<<"user_instance is destructed"<<std::endl;
        }
    };
};

void mythread(){
    player *user = player::getInstance();
    user->func();
    return;
}

//static member initializaton
player *player::user_instance = NULL;

int main(int, char**) {
    //player *robot1 = player::getInstance();
    //robot1->func();

    //player *robot2 = player::getInstance();
    //robot2->func();

    std::thread thread1(mythread);
    std::thread thread2(mythread);
    
    thread1.join();
    thread2.join();

    return 0;
}
