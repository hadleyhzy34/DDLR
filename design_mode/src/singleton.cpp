#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

class player{
private:
    player(){}; //constructor in privacy
    static player *user_instance; //static member

public:
    static player *getInstance(){
        if(user_instance == NULL){
            user_instance = new player();
            static destructPlayer dp; //instantiate static member so that it will be called() when the object destructed
        }
        return user_instance;
    }

    void func(){
        std::cout<<"to testify singleton mode point to same object"<<this<<std::endl;
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

void threadTask(){
    player *user = player::getInstance();
    user->func();
    return;
}

//static member initializaton
player *player::user_instance = NULL;

int main(int, char**) {
    player *robot1 = player::getInstance();
    robot1->func();

    player *robot2 = player::getInstance();
    robot2->func();
}
