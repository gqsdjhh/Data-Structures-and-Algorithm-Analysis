#include <iostream>

using namespace std;

struct Node {
    int data_;
    Node* prev_;
    Node* next_;

    Node(int val = 0) : data_(val), prev_(nullptr), next_(nullptr) {}
};

class DoubleLinkedList {
public:
    DoubleLinkedList() {
      head_ = new Node();
    }

    ~DoubleLinkedList() {
        Node* curr = head_;
        while (curr != nullptr) {
            head_ = head_->next_;
            delete curr;  
            curr = head_;
        }
    }

    void InsertHead(int val) {
        Node* node = new Node(val);
        node->next_ = head_->next_;
        node->prev_ = head_;
        if (head_->next_ != nullptr) {
            head_->next_->prev_ = node;
        }
        head_->next_ = node;
    }

    void InsertTail(int val) {
        Node* curr = head_;
        while (curr->next_ != nullptr) {
            curr = curr->next_;
        }
        Node* node = new Node(val);
        curr->next_ = node;
        node->prev_ = curr;
    }

    void Remove(int val) {
        Node* curr = head_->next_;
        while (curr != nullptr) {
            if (curr->data_ == val) {
                if (curr->prev_ != nullptr) {
                    curr->prev_->next_ = curr->next_;
                }
                if (curr->next_ != nullptr) {
                    curr->next_->prev_ = curr->prev_;
                }
                delete curr;
                return;
            }
            curr = curr->next_;
        }
    }

    void show() {
        Node* curr = head_->next_;
        while (curr != nullptr) {
            cout << curr->data_ << " ";
            curr = curr->next_;
        }
        cout << endl;
    }

private:
    Node* head_;
};

int main(){
    DoubleLinkedList dll;
    dll.InsertHead(10);
    dll.InsertTail(20);
    dll.InsertHead(5);
    dll.InsertTail(6);
    dll.show();
    dll.Remove(20);
    dll.show();

    return 0;
}