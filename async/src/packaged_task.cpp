/*reference:
 * https://www.cplusplus.com/reference/future/future/
 * https://en.cppreference.com/w/cpp/thread/future
 * Promise
*/

// promise example
#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

int add(int a, int b){
    int res = a + b;
    std::cout<<"res operation is started and calculated\n";
    return res;
}

int main ()
{
    std::packaged_task<int(int,int)> pkg_tsk(add);

    std::future<int> result = pkg_tsk.get_future();
    
    int a = 3;
    int b = 4;
    
    std::cout<<"operation is not started yet\n";
    
    //pkg_tsk(a,b);
    std::thread th(std::move(pkg_tsk), a, b);
    th.join();

    std::cout<<"packaged result is: "<<result.get()<<std::endl;
    
    std::thread th1(add,a,b);
    th1.join();
    return 0;
}
