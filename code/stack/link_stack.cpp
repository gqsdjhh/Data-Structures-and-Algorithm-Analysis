#include <iostream>
using namespace std;

class LinkStack {
public:
    LinkStack() : size_(0) {
        head_ = new Node();
    }

    ~LinkStack() {
        Node* p = head_;
        while (p != nullptr) {
            head_ = head_->next;
            delete p;
            p = head_;
        }
    }

public:
    // 入栈  把新节点插入到头结点之后
    auto push(int value) {
        Node* newNode = new Node(value);
        newNode->next = head_->next;
        head_->next = newNode;
        ++size_;
    }

    auto pop() {
        if (head_->next == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        Node* temp = head_->next;
        head_->next = temp->next;
        delete temp;
        --size_;
    }

    auto top() const {
        if (head_->next == nullptr) {
            throw std::out_of_range("Stack is empty");
        }
        return head_->next->data;
    }

    auto size() const {
        return size_;
    }

    bool empty() const {
      return head_->next == nullptr;
    }
private:
    struct Node {
        int data;
        Node* next;
        Node(int value = 0) : data(value), next(nullptr) {}
    };

    Node* head_;
    int size_;
};

int main()  
{  
    LinkStack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    cout << "Top element: " << stack.top() << endl; // 输出 3
    cout << "Stack size: " << stack.size() << endl; // 输出 3

    stack.pop();
    cout << "Top element after pop: " << stack.top() << endl; // 输出 2
    cout << "Stack size after pop: " << stack.size() << endl; // 输出 2

    return 0;
}