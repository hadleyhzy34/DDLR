#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <future>

/*reference:
 * https://www.cplusplus.com/reference/future/future/
 * https://en.cppreference.com/w/cpp/thread/future
 */
/*
Future
A future is an object that can retrieve a value from some provider object or function, properly synchronizing this access if in different threads.

"Valid" futures are future objects associated to a shared state, and are constructed by calling one of the following functions:
async
promise::get_future
packaged_task::get_future

future objects are only useful when they are valid. Default-constructed future objects are not valid (unless move-assigned a valid future).

Calling future::get on a valid future blocks the thread until the provider makes the shared state ready (either by setting a value or an exception to it). This way, two threads can be synchronized by one waiting for the other to set a value.

The lifetime of the shared state lasts at least until the last object with which it is associated releases it or is destroyed. Therefore, if associated to a future, the shared state can survive the object from which it was obtained in the first place (if any).
*/


// a non-optimized way of checking for prime numbers:
bool is_prime (int x) {
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}

int main ()
{
  // call function asynchronously:
  // if not using async to start a another thread, then function has to return a value so as to start rest of code
  // async could synchronously start a new thread handling is_prime task while main thread is still running
  // std::future<bool> fut:
  // 1.as a return value, hold the value while not blocking the main thread
  // 2.std::future<>::get method block the current thread until provider makes valid shared_state
  std::future<bool> fut = std::async (is_prime,444444443); 

  // do something while waiting for function to set future:
  std::cout << "checking, please wait";
  //std::chrono::milliseconds span (100);
  //while (fut.wait_for(span)==std::future_status::timeout)
    //std::cout << '.' << std::flush;

  bool x = fut.get();     // retrieve return value

  std::cout << "\n444444443 " << (x?"is":"is not") << " prime.\n";

  return 0;
}
