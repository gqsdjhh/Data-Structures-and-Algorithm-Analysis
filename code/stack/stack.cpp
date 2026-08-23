# include <iostream>  
using namespace std;

//栈 

class SeqStack {
public:
    SeqStack(int size = 10)
      : mtop(0), mcap(size) {
        mpStack = new int[mcap];
    }

    ~SeqStack() {
        delete[] mpStack;
        mpStack = nullptr;
    }

public:
    auto push(int value) {
        if (mtop == mcap) {
            expand(2 * mcap);
        }
        mpStack[mtop++] = value;
    }

    auto pop() {
        if (mtop == 0) {
            throw std::out_of_range("Stack is empty");
        }
        --mtop;
    }

    auto top() const {
        if (mtop == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return mpStack[mtop - 1];
    }
     
    auto size() const {
        return mtop;
    }

private:
    void expand(int newCap) {
        int* newStack = new int[newCap];
        memcpy(newStack, mpStack, mtop * sizeof(int));
        delete[] mpStack;
        mpStack = newStack;
        mcap = newCap;
    }

private:
    int mtop;  
    int mcap;  
    int* mpStack;
};

int main()  
{  
    SeqStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << "Top element: " << stack.top() << endl;
    stack.pop();
    cout << "Top element after pop: " << stack.top() << endl;
    cout << "Stack size: " << stack.size() << endl;
    
    return 0;  
}