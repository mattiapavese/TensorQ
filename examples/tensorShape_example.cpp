#include "tensor.hpp"

int main()
{

    tensor::TensorShape t1 { 0, 1, 2, 3 };
    std::cout<<"\norder t1: "<<t1.order()<<"\n\n";
    std::cout<<"shape t1: "<<t1<<"\n\n";
    
    tensor::TensorShape t2 { t1, { 4,5,6 }, { 7 } };  
    std::cout<<"\norder t2: "<<t2.order()<<"\n\n";
    std::cout<<"shape t2: "<<t2<<"\n\n";

    tensor::TensorShape t3 { t2, tensor::TensorShape { 8,9,10 }};
    std::cout<<"\norder t3: "<<t3.order()<<"\n\n";
    std::cout<<"shape t3: "<<t3<<"\n\n";

    std::cout<<t3[9]<<"\n"; //returns an unsigned int
    std::cout<<t3[-1]<<"\n"; //returns an unsigned int

    std::cout<<"\n\n";

    std::cout<<"xxx\n\n";

    tensor::TensorShape t3_rev = t3.reverse();
    std::cout<<t3_rev<<"\n";

    std::cout<<t3[{8}]<<"\n"; //returns a TensorShape
    std::cout<<t3[{-3}]<<"\n"; //returns a TensorShape
    std::cout<<t3[{2,-3}]<<"\n"; //returns a TensorShape

    std::cout<<t3[{-6,-2}]<<"\n"; //returns a TensorShape
    std::cout<<t3[{4,4}]<<"\n"; //returns a TensorShape
    std::cout<<t3[{4,2}]<<"\n"; //returns a TensorShape (in reversed order)
    std::cout<<t3[{-1, -6}]<<"\n";

    //std::cout<<t3[{1,2,3}]<<"\n"; //throws exception (wrong number of arguments)
    //std::cout<<t3[{}]<<"\n"; //throws exception (wrong number of arguments)

    std::cout<<"\n\nEND";

}