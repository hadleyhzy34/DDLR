# lvalue references, rvalue references, copy constructor, std::move, move constructor

## lvalues references and rvalues references

`l-value` refers to a memory location that identifies an object. `r-value` refers to data value that is stored at some address in memory.

`References` in C++ are nothing but the alternative to the already existing variable.

## example:

```
int main(){ //main thread is generated and executed
    int a = 10;

    //declaring lvalue reference
    int& lref = a;

    //declaring rvalue reference
    int&& rref = 20;

    // Print the values
    std::cout << "lref = " << lref << std::endl;
    std::cout << "rref = " << rref << std::endl;
 
    // Value of both a
    // and lref is changed
    lref = 30;
 
    // Value of rref is changed
    rref = 40;
    std::cout << "lref = " << lref << std::endl;
    std::cout << "rref = " << rref << std::endl;
 
    // This line will generate an error
    // as l-value cannot be assigned
    // to the r-value references
    // int &&ref = a;

    //r-value cannot be assigned to l-value references when it's const
    const int &ref = 20;
    std::cout<< "ref = " << ref << std::endl;
    return 0;
}
```

## Uses of the lvalue references:
1.lvalue references can be used to alisas an existing object
2.they can also be used to implement pass-by-reference semantics

```
void swap(int& a, int& b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main(){ //main thread is generated and executed
    int a = 10;
    int b = -10;

    std::cout<<a<<" "<<b<<std::endl;

    swap(a,b);

    std::cout<<a<<" "<<b<<std::endl;
    return 0;
}
```

## Uses of the rvalue references:
1.working with the move constructor and move assignment
2.cannot bind non-const lvalue reference of type `int&` to an rtype of type `int`
3.cannot bind rvalue references of type `int&&` to lvalue of type `int`



## std::move

! `std::move()` is a cast that produces an rvalue-reference to an object, to enable moving from it.

```
template <class T>
typename remove_reference<T>::type&&
std::move(T&& a)
{
    return a;
}
```

```
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
 
int main()
{
    std::string str = "Salut";
    std::vector<std::string> v;
 
    // uses the push_back(const T&) overload, which means 
    // we'll incur the cost of copying str
    v.push_back(str);
    std::cout << "After copy, str is " << std::quoted(str) << '\n';
 
    // uses the rvalue reference push_back(T&&) overload, 
    // which means no strings will be copied; instead, the contents
    // of str will be moved into the vector.  This is less
    // expensive, but also means str might now be empty.
    v.push_back(std::move(str));
    std::cout << "After move, str is " << std::quoted(str) << '\n';
 
    std::cout << "The contents of the vector are { " << std::quoted(v[0])
                                             << ", " << std::quoted(v[1]) << " }\n";
}
```

## reference

[1] (GeeksforGeeks: lvalfues references and rvalues references in C++ with Examples)[https://www.geeksforgeeks.org/lvalues-references-and-rvalues-references-in-c-with-examples/]
[2] (Move Constructors in C++ with Examples)[https://www.geeksforgeeks.org/move-constructors-in-c-with-examples/]
[3] (stackoverflow: std::move)[https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used]
[4] (Forcing Move Semantics) [http://thbecker.net/articles/rvalue_references/section_04.html]
[5] (cppreference: std::move) [https://en.cppreference.com/w/cpp/utility/move]
[6] (C++ Rvalue References Explained) [http://thbecker.net/articles/rvalue_references/section_01.html]
