#include "..\ToyLib\Toy.h"
#include <memory>
#include <string>
#include <iostream>

class A
{
public:
    A() {}
    void Foo() { std::cout << "Foo" << std::endl; }
    ~A() { std::cout << "~A" << std::endl; }
};



int main(int argc, char** argv)
{
    A* a = new A();
    std::shared_ptr<A> sp(a);
    std::shared_ptr<A> sp2 = sp;
    std::weak_ptr<A> wp = sp;
    wp.lock()->Foo();
    //std::shared_ptr<std::string> sp = std::shared_ptr<std::string>(new std::string("ggg"));
    //std::weak_ptr<std::string> wp = sp;
    //std::weak_ptr<std::string> wp2;
    //wp2 = sp;
    //auto p2 = wp2.lock();
    //if (wp2 == nullptr)
    //{
    //    std::cout << "empty" << std::endl;
    //}
    //auto p = wp.lock();
    return 0;
}