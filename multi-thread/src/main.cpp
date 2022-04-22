#include <iostream>
#include <vector>
#include <thread>

void myprint(int inum)
{
    std::cout<<inum<<" thread is started"<<std::endl;
    //..
}

int main(int, char**) {
    //multi threads declaration
    std::vector<std::thread> mythreads;
    
    //multi threads initialized
    for(int i = 0; i < 10; i++)
    {
        mythreads.push_back(std::thread(myprint, i)); //initialize and execute
    }

    for(auto iter = mythreads.begin(); iter!=mythreads.end(); ++iter)
    {
        iter->join();
    }

    //myobj.join();
    std::cout << "main thread is finished\n";
}
