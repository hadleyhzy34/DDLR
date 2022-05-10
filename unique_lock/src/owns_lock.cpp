#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>

std::mutex mtx;

void print_star(){
    std::unique_lock<std::mutex> lck(mtx, std::try_to_lock);
    //print '*' if successfully locked, 'x' otherwise;
    if(lck.owns_lock()){
        std::cout<<'*';
    }else{
        std::cout<<'x';
    }
}

int main(){
    std::vector<std::thread> threads;
    for(int i = 0; i < 5000; ++i)
        threads.emplace_back(print_star);

    for(auto &x:threads) x.join();

    return 0;
}
