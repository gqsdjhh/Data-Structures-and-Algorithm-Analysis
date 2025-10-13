#include<iostream>
#include<ctime>

using namespace std;

#if 0
//逆序字符串
void reverse(char arr[], int size){
    char *p = arr;
    char *q = arr + size - 1;

    while(p < q){
        char tmp = *p;
        *p = *q;
        *q = tmp;

        ++p;
        --q;
    }
}

int main(){
    char arr[] = "abcdef";
    int size = sizeof(arr) / sizeof(arr[0]) - 1;

    cout << "Before reverse: " << arr << endl;
    reverse(arr, size);
    cout << "After reverse: " << arr << endl;

    return 0;
}

#endif

#if 0
class Array{
public:
    Array(int size =10) : mCap(size), mCur(0) {
        mpArr = new int[mCap]();
    }
    ~Array(){
        delete[] mpArr;
        mpArr = nullptr;
    }

    void push_back(int val)        // Add an element to the end of the array
    {
        if(mCur == mCap){
            expand(2 * mCap);
        }
        mpArr[mCur++] = val;
    }
    void pop_back()                // Remove the last element of the array
    {
        if(mCur > 0){
            --mCur;
        }
    }
    
    void insert(int pos, int val)  // Insert an element at a specific position
    {
        if(pos < 0 || pos > mCur){
            return;
        }

        if(mCur == mCap){
            expand(2 * mCap);
        }
        
        for(int i = mCur; i > pos; --i){
            mpArr[i] = mpArr[i - 1];
        }

        mpArr[pos] = val;
        ++mCur;
    }

    void erase(int pos)            
    {
        if(pos < 0 || pos >= mCur){
            return;
        }

        for(int i = pos; i < mCur - 1; ++i){
            mpArr[i] = mpArr[i + 1];
        }

        --mCur;
    }

    int find(int val)              // Find the index of a specific element
    {
        for(int i = 0; i < mCur; ++i){
            if(mpArr[i] == val){
                return i;
            }
        }
        return -1;
    }

    void show() const           // Display the elements of the array
    {
        for(int i = 0; i < mCur; ++i){
            cout << mpArr[i] << " ";
        }
        cout << endl;
    }
private:
    int* mpArr;   // Pointer to the array
    int mCap;    // Capacity of the array
    int mCur;     // Current number of elements in the array

    void expand(int size){
        int* p = new int[size]();
        memcpy(p, mpArr, sizeof(int) * mCap);
        delete[] mpArr;

        mpArr = p;
        mCap = size;
    }
};

int main() {
    Array arr;
    
    srand((unsigned)time(NULL));
    for(int i = 0; i < 20; ++i){
        arr.push_back(rand() % 100);
    }

    arr.show();
    arr.pop_back();
    arr.show();

    arr.insert(5, 999);
    arr.show();

    arr.erase(3);
    arr.show(); 

    int index = arr.find(999);
    if(index != -1){
        cout << "Found 999 at index: " << index << endl;
    } else {
        cout << "999 not found" << endl;
    }

    return 0;
}

#endif