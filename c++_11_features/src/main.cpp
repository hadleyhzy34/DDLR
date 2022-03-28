#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <thread>

int main(){ //main thread is generated and executed
    int a = 10;

    //declaring lvalue reference
    int& lref = a;

    //declaring rvalue reference
    int&& rref = 20;

    // Print the values
    std::cout << "lref = " << lref << std::endl;
    std::cout << "rref = " << rref << std::endl;
 
    // Value of both a
    // and lref is changed
    lref = 30;
 
    // Value of rref is changed
    rref = 40;
    std::cout << "lref = " << lref << std::endl;
    std::cout << "rref = " << rref << std::endl;
 
    // This line will generate an error
    // as l-value cannot be assigned
    // to the r-value references
    // int &&ref = a;
    const int &ref = 20;
    std::cout<< "ref = " << ref << std::endl;

    int c = 10;
    int d = 20;

    std::cout<<"c: "<<c<<" "<<&c<<std::endl;
    std::cout<<"d: "<<d<<" "<<&d<<std::endl;
    
    c = d;
    std::cout<<"c: "<<c<<" "<<&c<<std::endl;
    std::cout<<"d: "<<d<<" "<<&d<<std::endl;
   
    int e{10}, f{20};
    std::cout<<"e: "<<e<<" "<<&e<<std::endl;
    std::cout<<"f: "<<f<<" "<<&f<<std::endl;

    e = std::move(f);
    std::cout<<"e: "<<e<<" "<<&e<<std::endl;
    std::cout<<"f: "<<f<<" "<<&f<<std::endl;
    
    return 0;
}
