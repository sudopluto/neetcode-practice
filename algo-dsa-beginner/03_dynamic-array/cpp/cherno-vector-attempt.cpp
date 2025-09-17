#include <iostream>
#include <initializer_list>
#include <print>

template <typename T> class Vector {
    int size{0};
    int capacity{0};
    int* buff{nullptr};

    void resize() {

        // if underlying vector is empty
        if (this->buff == nullptr) {
            this->capacity = 2;
            this->buff = new T[2];
            return;
        }

        this->capacity *= 2;
        int* new_buff = new T[this->capacity];

        for (int i = 0; i < this->size; i++) {
           new_buff[i] = this->buff[i];
        }

        delete[] this->buff;
        this->buff = new_buff;
    }

public:
    Vector() = default;
    ~Vector() { delete[] buff; }

    Vector(int capacity) : capacity{capacity}, buff{new T[capacity]} {}

    Vector(std::initializer_list<T> ilist) : Vector(ilist.size()) {
        std::copy(ilist.begin(), ilist.end(), this->buff);
        this->size = this->capacity;
    }

    void push_back(T val) {
        if (this->size == this->capacity) {
            this->resize();
        }

        this->buff[this->size++] = val;
    }

    T& operator[](int idx) { return buff[idx]; }
    T& operator[](int idx) const { return buff[idx]; }

    const int* begin() { return this->buff; }
    const int* end() { return this->buff + this->size; }

    void print_vec() {
        std::print("vec size = {}, ", this->size);
        std::println("vec capacity = {}", this->capacity);

        std::print("[ ");
        for (int i = 0; i < this->size; i++) {
            std::print("{} ", this->buff[i]);
        }
        std::println("]");
    }
};

int main()
{
    // Create a vector containing integers
    Vector<int> v = {8, 4, 5, 9};

    v.print_vec();

    // Add two more integers to vector
    v.push_back(6);
    v.push_back(9);

    v.print_vec();

    // Overwrite element at position 2
    v[2] = -1;

    v.print_vec();

    // Print out the vector
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}
