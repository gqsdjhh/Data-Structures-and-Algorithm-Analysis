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

    void Remove(int val) {
        Node* p = _head;
        Node* q = _head->_next;

        while (q != nullptr) {
            if (q->_data == val) {
                p->_next = q->_next;
                delete q;
                return;
            }
            p = q;
            q = q->_next;
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

    bool Find(int val){
        Node* p = _head->_next;

        while(p != nullptr){
            if(p->_data == val){
                return true;
            }
            else{
                p = p->_next;
            }
        }

        return false;
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

    friend void ReverseLink(Clink &link);
    friend bool GetlastKNode(Clink &link, int k, int &value);
    friend void MergeLink(Clink &link1, Clink &link2);
    friend bool IsLinkHasCircle(Clink &link, int &val);
};

#if 0
//单链表逆序
void ReverseLink(Clink &link)
{
    Node* head = link._head;
    Node* p = head->_next;
    if(p == nullptr){
        return;
    }

    head->_next = nullptr;

    while(p != nullptr){
        Node* q = p->_next;

        //头插法
        p->_next = head->_next;
        head->_next = p;
        p = q;
    }

}

int main() {
    Clink link;
    srand((unsigned int)time(nullptr));
    for(int i = 0; i < 10; ++i){
        int val = rand() % 100;
        link.InsertHead(val);
    }
    link.Show();
    ReverseLink(link);
    link.Show();

    return 0;
}
#endif

#if 0
//单链表倒数第k个节点
bool GetlastKNode(Clink &link, int k, int &val)
{
    if(k <= 0){
        return false;
    }
    Node* head = link._head;

    Node* pre = head;
    Node* p = head;

    for(int i = 0; i < k; ++i){
        p = p->_next;
    
        if(p == nullptr){
            return false;
        }
    }

    //pre在头节点，p在正数第k个节点
    while(p != nullptr){
        pre = pre->_next;
        p = p->_next;
    }

    val = pre->_data;
    return true;
}


int main() {
    Clink link;
    srand((unsigned int)time(nullptr));
    for(int i = 0; i < 10; ++i){
        int val = rand() % 100;
        link.InsertHead(val);
    }
    link.Show();
    int k = 3;
    int value = 0;
    if(GetlastKNode(link, k, value)){
        cout << "The " << k << "th to last node value is: " << value << endl;
    }
    else{
        cout << "No such node." << endl;
    }

    return 0;
}
#endif

#if 0
//合并两个有序单链表
void MergeLink(Clink &link1, Clink &link2)
{
    Node *p = link1._head->_next;
    Node *q = link2._head->_next;
    Node *last = link1._head;

    while(p != nullptr && q != nullptr){
        if(p->_data < q->_data){
            last->_next = p;
            p = p->_next;
            last = last->_next;
        }
        else{
            last->_next = q;
            q = q->_next;
            last = last->_next;
        }
    }

    if(p != nullptr){
        last->_next = p;
    }
    else if(q != nullptr){
        last->_next = q;
    }
}


int main() {
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int brr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    Clink link1;
    Clink link2;

    for(int i = 0; i < 10; ++i){
        link1.InsertTail(arr[i]);
        link2.InsertTail(brr[i]);
    }
    link1.Show();
    link2.Show();

    MergeLink(link1, link2);
    link1.Show();
    //link2.Show();    

    return 0;
}
#endif

#if 0
//单链表是否有环，求环的入口
bool IsLinkHasCircle(Node *head, int &val)
{
    //使用快慢指针法
    Node* slow = head;
    Node* fast = head;

    //fast快，不用判断slow
    while(fast != nullptr && fast->_next != nullptr){
        slow = slow->_next;
        fast = fast->_next->_next;

        if(slow == fast){
            //有环，求环的入口
            slow = head;
            while(slow != fast){
                slow = slow->_next;
                fast = fast->_next;
            }
            val = slow->_data;
            return true;
        }
    }

    return false;
}

int main(){
    Node head;

    Node n1(25), n2(27), n3(32), n4(18);
    head._next = &n1;
    n1._next = &n2;
    n2._next = &n3;
    n3._next = &n4;
    n4._next = &n2;

    int val;
    if(IsLinkHasCircle(&head, val)){
        cout << "链表有环，入口节点值为: " << val << endl;
    }
    else{
        cout << "链表无环" << endl;
    }

    return 0;
}
#endif

#if 0
//判断两个单链表是否相交
bool IsLinkHasMerge(Node *head1, Node *head2, int &val)
{
    int cnt1 = 0, cnt2 = 0;
    Node* p = head1->_next;
    Node* q = head2->_next;

    while(p != nullptr){
        cnt1++;
        p = p->_next;
    }

    while(q != nullptr){
        cnt2++;
        q = q->_next;
    }

    p = head1->_next;
    q = head2->_next;

    //如果长度不相等，先走长的
    if(cnt1 > cnt2){
        for(int i = 0; i < cnt1 - cnt2; ++i){
            p = p->_next;
        }
    }
    else{
        for(int i = 0; i < cnt2 - cnt1; ++i){
            q = q->_next;
        }
    }

    while(p != nullptr && q != nullptr){
        if(p == q){
            val = p->_data;
            return true; //相交
        }
        p = p->_next;
        q = q->_next;
    }
}


int main(){
    Node head1, head2;
    Node n1(25), n2(27), n3(32), n4(18);
    head1._next = &n1;
    n1._next = &n2;
    n2._next = &n3;
    n3._next = &n4;
    Node n5(30), n6(35);
    head2._next = &n5;
    n5._next = &n6;
    n6._next = &n3; //让两个链表相交
    int val;
    if(IsLinkHasMerge(&head1, &head2, val)){
        cout << "两个链表相交，交点值为: " << val << endl;
    }
    else{
        cout << "两个链表不相交" << endl;
    }

    return 0;
}
$#endif

#if 0
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
#endif