#include <stdexcept>
#include "tensorQ.hpp"



//tensorQ::TensorShape

tensorQ::TensorShape::TensorShape(std::initializer_list<unsigned int> init)
{
    dimensions_.reserve(init.size());
    for (int i=0; i<init.size(); i++) dimensions_.push_back(init.begin()[i]);
    order_ = dimensions_.size();
}


tensorQ::TensorShape::TensorShape(std::initializer_list<tensorQ::TensorShape> init)
{
    unsigned int reserve_size_ = 0;
    for (int i=0; i<init.size(); i++) reserve_size_ += init.begin()[i].order_;
    dimensions_.reserve(reserve_size_);
    for (int i=0; i<init.size(); i++){
        for (int j=0; j<init.begin()[i].order_; j++){
            dimensions_.push_back(init.begin()[i].dimensions_.at(j));
        }
    }
    order_ = dimensions_.size();
}


tensorQ::TensorShape::TensorShape(std::vector<unsigned int> init)
{
    dimensions_ = init;
    order_ = dimensions_.size();
}
        
unsigned int tensorQ::TensorShape::operator[](int idx)
{
    return (idx<0) ? dimensions_.at(order_+idx) : dimensions_.at(idx); 
}


tensorQ::TensorShape tensorQ::TensorShape::reverse()
{
    std::vector <unsigned int> new_dims_ (dimensions_.rbegin(), dimensions_.rend());
    return tensorQ::TensorShape {new_dims_};
}


tensorQ::TensorShape tensorQ::TensorShape::operator[](std::initializer_list<int> slicer)
{
    switch (slicer.size())
    {
        case 1:
        {
            int idx=slicer.begin()[0];
            return tensorQ::TensorShape {(idx<0) ? dimensions_.at(order_+idx) : dimensions_.at(idx)};
            break;
        }

        case 2:
        {
            auto start_idx = slicer.begin()[0];
            auto end_idx = slicer.begin()[1];

            start_idx = (start_idx<0) ? order_+start_idx : start_idx;
            end_idx = (end_idx<0) ? order_+end_idx : end_idx;

            bool reverse_ = false;
            if (start_idx>end_idx)
            {
                std::swap(start_idx, end_idx);
                reverse_=true;
            }

            std::vector<unsigned int>  new_dims_;
            new_dims_.reserve(end_idx - start_idx + 1);

            for (int i=0; i<end_idx - start_idx + 1; i++) new_dims_.push_back(this->to_vector().at(start_idx+i));

            return reverse_ ? tensorQ::TensorShape {new_dims_} .reverse() : tensorQ::TensorShape {new_dims_};
        }

        default:
        {
            throw std::runtime_error("Unable to slice "
                "TensorShape object: wrong number of arguments in std::initializer_list<int> slicer."
                " Please provide 1 or 2 arguments.");
            break;
        }
    }
}


std::vector<unsigned int> tensorQ::TensorShape::to_vector()
{   
    return dimensions_;
}


std::ostream& tensorQ::operator<<(std::ostream& os, const tensorQ::TensorShape& shape)
{
    os << "TensorShape(";
    for (size_t i = 0; i < shape.order_; ++i) {
        os << shape.dimensions_.at(i);
        if (i < shape.order_ - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

//#######################################################################################
//tensor::Tensor

template <typename T>
tensorQ::Tensor<T>::Tensor(tensorQ::TensorShape shape_) : shape{shape_}
{   
    std::cout<<"called delegated constructor \n";
    values_.reserve(shape.n_entries());
    std::cout<<"reserved "<<shape.n_entries()<<"\n";
}

template <typename T> //TODO: FIX THE CONSTRUCTOR TO AVOID STATIC CAST
tensorQ::Tensor<T>::Tensor(std::initializer_list<T> init) : 
    tensor::Tensor<T>::Tensor( tensor::TensorShape { static_cast<unsigned int>(init.size())} )
{
    std::cout<<"called delegator constructor Tensor(std::initializer_list<T>) \n";
    for (auto it=init.begin(); it!=init.end(); ++it) values_.push_back(*it);
}

template <typename T>
tensorQ::Tensor<T>::Tensor(std::initializer_list<tensorQ::Tensor<T>> init)
    : tensor::Tensor<T>::Tensor(
        tensor::TensorShape { {static_cast<unsigned int>(init.size()) },
            assert_all_shapes_are_equal_and_return_shape_(init)}
    )
{
    std::cout<<"called delegator constructor Tensor(std::initializer_list<tensor::Tensor<T>>) \n";
}

template <typename T>
tensorQ::TensorShape tensorQ::Tensor<T>
    ::assert_all_shapes_are_equal_and_return_shape_(
        const std::initializer_list<tensorQ::Tensor<T>> & init)
{   
    std::cout<<"called assert_all_shapes_are_equal_and_return_shape_ method \n";
    //TODO implement check 
    return (init.begin()[0]).shape;
}

template <typename T>
tensorQ::Tensor<T>::~Tensor(){
    std::cout<<"called destuctor\n";
}

//TODO: REPLACE THIS FUNC WITH []
template <typename T>
T tensorQ::Tensor<T>::at(int idx)
{
    return values_.at(idx);
}
 
//template
// template class tensor::Tensor<short>;
// template class tensor::Tensor<unsigned short>;
template class tensorQ::Tensor<int>;
// template class tensor::Tensor<unsigned int>;
// template class tensor::Tensor<long>;
// template class tensor::Tensor<unsigned long>;
// template class tensor::Tensor<long long>;
// template class tensor::Tensor<unsigned long long>;
// template class tensor::Tensor<float>;
template class tensorQ::Tensor<double>;
// template class tensor::Tensor<long double>;





