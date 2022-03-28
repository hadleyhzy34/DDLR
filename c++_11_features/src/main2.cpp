#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <thread>


void swap(int& a, int& b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void printReference(int &&a){
    std::cout<<a<<std::endl;
}

int main(){ //main thread is generated and executed
    int a = 10;
    int b = -10;

    std::cout<<a<<" "<<b<<std::endl;

    swap(a,b);

    std::cout<<a<<" "<<b<<std::endl;

    printReference(100);
    return 0;
}
