#include <iostream>
#include <ctime>

using namespace std;

struct Node
{
    Node(int data = 0) : _data(data), _next(nullptr) {};
    int _data;
    Node* _next;
};

class Clink
{
public:
    Clink(){
        _head = new Node();
    }

    ~Clink(){
        Node* p = _head;
        
        while(p != nullptr){
            _head = _head->_next;
            delete p;
            p = _head;
        }

        _head = nullptr;
    }

    void InsertTail(int val){
        // 先找到尾节点
        Node* p = _head;
        while(p->_next != nullptr){
            p = p->_next;
        }

        // 创建新节点
        Node* node = new Node(val);

        // 尾节点的next指向新节点
        p->_next = node;
        node->_next = nullptr;
    }

    void InsertHead(int val){
        // 创建新节点
        Node* node = new Node(val);
        // 新节点的next指向头节点的下一个节点
        node->_next = _head->_next;
        // 头节点的next指向新节点
        _head->_next = node;
    }

    void Remove(int val){
        Node* p = _head;
        Node* q = _head->_next;
        
        while(q != nullptr){
            if(q->_data == val){
                p->_next = q->_next;
                delete q;
                return;
            }
            else{
                p = q;
                q = q->_next;
            }
        }
    }

    void RemoveAll(int val){
        Node* p = _head;
        Node* q = _head->_next;

        while(q != nullptr){
            if(q->_data == val){
                p->_next = q->_next;
                delete q;
                q = p->_next;
            }
            else{
                p = q;
                q = q->_next;
            }
        }
    }
    
    void Show(){
        Node* p = _head->_next;
        while(p != nullptr){
            cout << p->_data << " ";
            p = p->_next;
        }
        cout << endl;
    }

private:
    Node* _head;
};

int main() {
    Clink cl;
    srand((unsigned int)time(nullptr));
    for(int i = 0; i < 10; ++i){
        int val = rand() % 100;
        cl.InsertHead(val);
    }
    cl.InsertHead(10);
    cl.InsertHead(10);
    cl.Show();
    cl.RemoveAll(10);
    cl.Show();

    return 0;
}