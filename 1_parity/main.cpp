#include <iostream>
using namespace std;

template<typename T>
bool parity(T val) {
    bool ret = false;
    while(val) {
        ret ^= (val & 0x1);
        val >>= 1;
    }
    return ret;
}

int main() {
    int x = 7;
    cout<<"parity of " << x << " i.e. "<< hex << x <<" is "<< parity(x)<<endl;
    return 0;
}