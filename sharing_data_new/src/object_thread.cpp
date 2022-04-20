#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>


/**************************summary************************
1.pass int, recommend to pass value instead of reference
2.pass object, not recommend to do implict conversion, recommend to construct temporary object
3.pass object, recommend to use reference
*/

class test_obj
{
public:
    int m_i;
    test_obj(int a):m_i(a){
        std::cout<<this<<" class new_thread is constructed\n";
    }
    
    test_obj(const test_obj &obj):m_i(obj.m_i){
        std::cout<<this<<" new_thread is copy constructed\n";
    }

    ~test_obj(){std::cout<<this<<" new_thread is destructed\n";}
};

//void myprint(const int &i, const std::string &mybuf)
void myprint(const int &i, const test_obj &mybuf)
{
    std::cout<<"mybuf address inside function is: "<<&mybuf<<std::endl;
}

int main()
{
    int myvar = 1;
    std::cout<<"address of myvar inside main is: "<<&myvar<<"\n";
    
    int mysecondPar = 12;
    
    //type conversion contructor
    //test_obj n_thread(mysecondPar);
    //std::thread myobj(myprint, myvar, mysecondPar);
    
    //temporary construct object, construct->copy construct, works for detach() method
    std::thread myobj(myprint, myvar, test_obj(mysecondPar));
    myobj.join();
    //myobj.detach();
    
    std::cout<<"this is thread basic testing"<<std::endl;
    return 0;
}
