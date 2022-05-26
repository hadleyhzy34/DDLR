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

int step1(int para)
{
    std::cout<<"step1 started: "<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout<<"step1 end"<<std::endl;
    return 1;
}

int step2(std::shared_future<int> &temp)
{
    std::cout<<"step2 started: "<<std::this_thread::get_id()<<std::endl;
    auto result = temp.get();
    std::cout<<"step2 ended with result: "<<result<<std::endl;
    return 1;
}

int main ()
{
    std::packaged_task<int(int)> pkg_tsk(step1);

    int a = 3;
    std::cout<<"operation is not started yet\n";
    
    //pkg_tsk(a,b);
    std::thread th(std::ref(pkg_tsk), a);
    th.join();
    
    std::future<int> result = pkg_tsk.get_future();
    //bool result_status = result.valid();
    //std::shared_future<int> shared_result(std::move(result));
    std::shared_future<int> shared_result(result.share());

    //shared_future could also be constructed by calling packaged_task::get_future()
    //std::shared_future<int> shared_result(pkg_tsk.get_future());
    
    //this line demonstrates shared_future::get() could be called more than once without error
    auto step1Result = shared_result.get();
    std::thread th1(step2, std::ref(shared_result));
    th1.join();
    
    std::cout<<"main thread ended here\n";
    return 0;
}
