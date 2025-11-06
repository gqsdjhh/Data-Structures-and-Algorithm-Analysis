#include <iostream>
#include <ctime>

using namespace std;

//单向循环链表
class CircleLink
{
public:
    CircleLink(){
        head_ = new Node();
        tail_ = head_;
        head_->next_ = head_;
    }

    ~CircleLink(){
        Node* p = head_->next_;
        
        while(p != head_){
            head_->next_ = p->next_;
            delete p;
            p = head_->next_;
        }

        delete head_;
    }

    void InsertTail(int val){
        Node* node = new Node(val);

        node->next_ = tail_->next_;
        tail_->next_ = node;

        // 更新尾节点指针
        tail_ = node;
    }

    void InsertHead(int val){
        // 创建新节点
        Node* node = new Node(val);
        
        node->next_ = head_->next_;;
        head_->next_ = node;

        // 如果链表之前为空，更新尾节点指针
        if(node->next_ == head_){
            tail_ = node;
        }
    }

    void Remove(int val) {
        Node* p = head_;
        Node* q = head_->next_;

        while (q->next_ != head_) {
            if (q->data_ == val) {
                p->next_ = q->next_;
                delete q;

                // 如果删除的是尾节点，更新尾节点指针
                if(p->next_ == head_){
                    tail_ = p;
                }

                return;
            }
            p = q;
            q = q->next_;
        }
    }

    bool Find(int val) const {
        Node* p = head_->next_;

        while(p != head_){
            if(p->data_ == val){
                return true;
            }
            else{
                p = p->next_;
            }
        }

        return false;
    }
    
    void Show() const {
        Node* p = head_->next_;
        while(p != head_){
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

private:
    struct Node
    {
        Node(int data = 0) : data_(data), next_(nullptr) {};
        int data_;
        Node* next_;
    };

    Node* head_;
    Node* tail_;
};

int main(){
    CircleLink clink;
    srand(time(NULL));

    for(int i = 0; i < 10; ++i){
        clink.InsertTail(rand() % 100);
    }
    clink.Show();
    clink.InsertHead(50);
    clink.Show();
    clink.Remove(50);
    clink.Show();
    clink.InsertTail(75);
    clink.Show();
    clink.Find(75) ? cout << "Found 75" << endl : cout << "75 Not Found" << endl;

    return 0;
}