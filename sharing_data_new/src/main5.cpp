#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <string>

//void myprint(const int &i, const std::string &mybuf)
void myprint(const int &i, char* mybuf)
{
    //below print shows that address of i is not the same as one in the main function
    //which later proves that reference variable `i` is copied when calling std::thread
    std::cout<<"address of i inside function is: "<<&i<<"\n";
    std::cout<<"char array address in function is: "<<&mybuf<<"\n";
    std::cout<<i<<std::endl;
    std::cout<<mybuf<<std::endl;
}

int main()
{
    int myvar = 1;
    std::cout<<"address of myvar inside main is: "<<&myvar<<"\n";
    int &var = myvar;
    std::cout<<"reference of myvar address is: "<<&var<<"\n";
    char mybuf[] = "this is a test!";
    //char* mybuf = (char*)"this is a test!";
    std::cout<<"char array address in main is: "<<&mybuf<<"\n";

    std::thread myobj(myprint, myvar, mybuf);

    //if args in function is `const std::string`, there could be possible chance that
    //main thread is finished while mybuf is not converted yet
    //adding std::string() could prevent this case
    //std::thread myobj(myprint, myvar, std::string(mybuf));
    myobj.join();
    //myobj.detach();
    std::cout<<"this is thread basic testing"<<std::endl;
    return 0;
}
