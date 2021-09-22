#include <iostream>
#include <vector>

using namespace std;
class Stack
{
private:
    std::vector<int> vect;

public:
    Stack()
    {
        vect.empty();
    }
    void Push(int val)
    {
        vect.push_back(val);
    }
    void Pop()
    {
        vect.pop_back();
    }
    void Top()
    {
        auto i = vect.size();
        std::cout << vect[i - 1];
    }
    bool IsEmpty()
    {
        return vect.empty();
    }
};
int main()
{
    auto stack = new Stack();
    stack->Push(2);
    stack->Push(4);
    stack->Push(7);
    stack->Top();
    stack->Pop();
    stack->Top();
}
