// 04_双向链表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

// 定义双向链表的节点类型
struct Node
{
    Node(int data=0)
        : _data(data)
        , _next(nullptr)
        , pre_(nullptr)
    {}
    int _data;   // 数据域
    Node* _next; // 指向下一个节点
    Node* pre_;  // 指向前一个节点
};

// 双向链表
class DoubleLink
{
public:
    DoubleLink()
    {
        head_ = new Node();
    }
    ~DoubleLink()
    {
        Node* p = head_;
        while (p != nullptr)
        {
            head_ = head_->_next;
            delete p;
            p = head_;
        }
    }

public:
    // 头插法
    void InsertHead(int val)
    {
        Node* node = new Node(val);
        node->_next = head_->_next;
        node->pre_ = head_;
        if (head_->_next != nullptr)
        {
            head_->_next->pre_ = node;
        }
        head_->_next = node;
    }

    // 尾插法
    void InsertTail(int val)
    {
        Node* p = head_;
        while (p->_next != nullptr)
        {
            p = p->_next;
        }

        // p->尾节点
        Node* node = new Node(val);
        node->pre_ = p;
        p->_next = node;
    }

    // 节点删除
    void Remove(int val)
    {
        Node* p = head_->_next;
        while (p != nullptr)
        {
            if (p->_data == val)
            {
                // 删除p指向的节点
                p->pre_->_next = p->_next;
                if (p->_next != nullptr)
                {
                    p->_next->pre_ = p->pre_;
                }
                //Node* next = p->next_;
                delete p;
                //p = next;
                return;
            }
            else
            {
                p = p->_next;
            }
        }
    }

    // 节点搜索
    bool Find(int val)
    {
        Node* p = head_->_next;
        while (p != nullptr)
        {
            if (p->_data == val)
            {
                return true;
            }
            else
            {
                p = p->_next;
            }
        }
        return false;
    }

    // 链表节点输出
    void Show()
    {
        Node* p = head_->_next;
        while (p != nullptr)
        {
            cout << p->_data << " ";
            p = p->_next;
        }
        cout << endl;
    }

private:
    Node* head_; // 指向头节点
};

int main()
{
    DoubleLink dlink;

    dlink.InsertHead(100);

    dlink.InsertTail(20);
    dlink.InsertTail(12);
    dlink.InsertTail(78);
    dlink.InsertTail(32);
    dlink.InsertTail(7);
    dlink.InsertTail(90);
    dlink.Show();

    dlink.InsertHead(200);
    dlink.Show();

    dlink.Remove(200);
    dlink.Show();

    dlink.Remove(90);
    dlink.Show();

    dlink.Remove(78);
    dlink.Show();
}