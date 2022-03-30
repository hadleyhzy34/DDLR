#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>
#include <thread>

class protected_data
{
	std::list<int> some_list; // 1
	std::mutex mutex_a; // 2
    std::mutex mutex_b;
public:
	void add_to_list(int new_value);
	bool list_contains(int value_to_find);
};


void protected_data::add_to_list(int new_value)
{
	//std::lock_guard<std::mutex> guard(mutex_a); // 3
	some_list.push_back(new_value);
}

bool protected_data::list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(mutex_b); // 4
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}

void fun_add(protected_data &pd)
{
	for (unsigned i = 1000;i >0;--i)
	{
        //std::cout<<i<<" added to list"<<"\t";
		pd.add_to_list(i);
	}
}

void fun_contains(protected_data &pd)
{
	for (unsigned i = 0;i < 1000;++i)
	{
		//std::cout << i <<"checked"<< "\t";
		if (!pd.list_contains(i))
		{
			std::cout << "no " <<i<< "\t";
		}
	}	
}

int main()
{
	protected_data pd;
	//std::thread t1(fun_add,std::ref(pd));
    std::thread t1(fun_add, std::ref(pd));
	std::thread t2(fun_contains, std::ref(pd));
	t1.join();
	t2.join();
	system("pause");
	return 0;
}
