#include <vector>
#include <iostream>
#include <initializer_list>
#include <numeric>

namespace tensorQ
{
    class TensorShape
    {
        public:
            TensorShape(std::initializer_list<unsigned int> init);
            TensorShape(std::initializer_list<TensorShape> init);
            TensorShape(std::vector<unsigned int> init);
            unsigned int order() { return order_; };
            unsigned int operator[](int idx);
            TensorShape reverse();
            TensorShape operator[](std::initializer_list<int> slicer);
            std::vector<unsigned int> to_vector();
            friend std::ostream& operator<<(std::ostream& os, const TensorShape &shape);
            unsigned int n_entries(){ return std::accumulate(dimensions_.begin(), dimensions_.end(), 1, std::multiplies<int>());}

        private:
            unsigned int order_;
            std::vector<unsigned int> dimensions_;

    };

    template<typename T>
    class Tensor
    {
        public:
            TensorShape shape;
            Tensor(TensorShape shape_);
            Tensor(std::initializer_list<T> init);
            Tensor(std::initializer_list<Tensor<T>> init);
            TensorShape assert_all_shapes_are_equal_and_return_shape_
                (const std::initializer_list<Tensor<T>> & init);
            ~Tensor();
            T at(int idx);
            unsigned int order(){return shape.order();}
            unsigned int n_entries(){return shape.n_entries();}

        private:
            std::vector<T> values_;

    };
}