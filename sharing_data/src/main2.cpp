#include <iostream>
#include <exception>
#include <memory>
#include <mutex>
#include <stack>
#include <thread>

struct empty_stack : std::exception  //exception
{
	const char* what() const throw() {
		return "empty stack!";
	};
};
 
template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;//与互斥量放在一起的是要保护的数据
	mutable std::mutex m;//可变数据成员，const函数：empty()
	//在const对象中或const成员函数中，该值依然可变
public:
	threadsafe_stack()
		: data(std::stack<T>()) {}
 
	threadsafe_stack(const threadsafe_stack& other)//复制构造函数
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data; //  在构造函数体中的执行拷贝
	}
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;//不可以赋值
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}
	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack(); // 在调用pop前，检查栈是否为空
		std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在修改堆栈前，分配出返回值
			data.pop();
		return res;
	}
	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();//子线程内报错，主线程提示还有未处理的异常
		value = data.top();
		data.pop();
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};
void fun_push(threadsafe_stack<unsigned> &ts)
{
	for (unsigned i = 0;i < 100;++i)
	{
		ts.push(i);
		std::cout << i << std::endl;
	}
}
void fun_pop(threadsafe_stack<unsigned> &ts)
{
	for (unsigned i = 0;i < 1000000;++i);
	for (unsigned i = 0, top = 0;i < 100;++i)
	{		
		ts.pop(top);
		std::cout << "\t"<<top << std::endl;
	}
}
int main()
{
	std::cout << "push" << "\tpop" << std::endl;
	threadsafe_stack<unsigned> ts;
	std::thread tpush{ fun_push,std::ref(ts) }, tpop{ fun_pop,std::ref(ts) };
	tpush.join();
	tpop.join();
	system("pause");
	return 0;
}
