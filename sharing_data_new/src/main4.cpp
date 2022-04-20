#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class some_big_object {
public:
	some_big_object(std::vector<int> &v_)
	{
		swap(v, v_);
	}
	friend void swap(some_big_object &lhs, some_big_object &rhs);
	friend std::ostream & operator<<(std::ostream &os, some_big_object &rhs)//返回流的引用
	{
		os << rhs.v[0];
		return os;
	}
private:
	std::vector<int> v;
};

void swap(some_big_object& lhs, some_big_object& rhs)
{
	swap(lhs.v, rhs.v);
}
 
class X
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(const some_big_object & sd) :some_detail(sd) {}
	friend void swap(X& lhs, X& rhs)
	{
		if (&lhs == &rhs)
			return;
		std::lock(lhs.m, rhs.m); // <mutex>
		/*一次锁住两个（只有一个线程参与）。
		*防止A线程将lhs，B线程将rhs锁住，
		*然后试图在相同的两个实例间进行数据交换时，产生死锁。
		*比如调用时参数传入顺序不同
		*A:swap(a,b);先锁a
		*B:swap(b,a);先锁b
		*A、B进程无法继续
		*/
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // 2
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock); // 3
		//提供 std::adopt_lock 参数除了表示 std::lock_guard 对象已经上锁外，还表示现成的锁，而非尝试创建新的锁。
		
		//std::lock_guard<std::mutex> lock_a(lhs.m); 
		//std::lock_guard<std::mutex> lock_b(rhs.m); 
 
		swap(lhs.some_detail, rhs.some_detail);
	}
	friend std::ostream & operator<<(std::ostream &os,X &rhs)
	{
		os << rhs.some_detail;
		return os;
	}
};
void fun(X &a, X &b)
{
	swap(a, b);
}
int main()
{
	std::vector<int> va(1000, 0), vb(1002, 1);
	X a(va), b(vb);
	bool flag = false;
	std::cout << a << "\t" << b << std::endl;

    /*
	std::thread ta{ fun,std::ref(a),std::ref(b) },
		tb{ fun,std::ref(b),std::ref(a) };
	ta.join();
	tb.join();//暂时还无法一定产生死锁	
	std::cout << a << "\t" << b <<std::endl;
    */

    std::thread ta{fun, std::ref(a), std::ref(b)};
    
    ta.join();
    std::cout<<a <<"\t"<<b<<std::endl;

    
    std::thread tb{fun, std::ref(a), std::ref(b)};
    tb.join();
    std::cout<<a <<"\t"<<b<<std::endl;
    
    std::thread tc{fun, std::ref(a), std::ref(b)};
    std::thread td{fun, std::ref(a), std::ref(b)};
    tc.join(); 
    td.join();
    std::cout<<a <<"\t"<<b<<std::endl;


	system("pause");
	return 0;
}
