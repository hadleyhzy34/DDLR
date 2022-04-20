#include <list>
#include <mutex>
#include <algorithm>

class some_data
{
	int a;
	std::string b;
public:
	void do_something();
};

class data_warpper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> l(m);
		func(data);		                    //pass 'protected_data' to user-supplied function
	}
};
some_data* unprotected;

void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}

data_warpper x;

void foo()
{
	x.process_data(malicious_function); //pass in a malicious_function
	unprotected->do_something();	    //unprotected access to protected_data
}
