#include <iostream>

void print() {
    std::cout << std::endl;
}

template<typename T, typename... Args>
void print(const T& value, const Args&... args) {
    std::cout << value << " ";
    print(args...); 
}


int main(){
    print("hello", "world");
}