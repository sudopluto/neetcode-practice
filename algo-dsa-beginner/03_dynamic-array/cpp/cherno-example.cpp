#include <iostream>

template<typename T>
class Vector
{
   T* m_data{nullptr};
   size_t m_size{0};
   size_t m_capacity{2};

   void resize() {
       std::cout << "Vector::resize() called\n";
       resize(m_capacity * 2);
       std::cout << "Vector::resize() end\n";
   }

   void resize(size_t new_capacity) {
       auto align_val = static_cast<std::align_val_t>(alignof(T));

       // resize() is just special case of erasing underying container, can handle that in explict case
       if (new_capacity == 0) {
           clear();
           ::operator delete(m_data, m_capacity * sizeof(T), align_val);
           m_data = nullptr;
           m_size = 0;
           m_capacity = 0;
           return;
       }

       // never really need to call default constructor T() since we are copying over data anyways
       // just need to alloc memory block of correct size
       //T* new_data = new T[m_capacity];
       T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T), align_val));

       for (size_t i = 0; i < m_size; i++) {
           new (&new_data[i]) T(std::move(m_data[i]));
       }

       // need to cache size since clear sets size back to zero
       size_t size_temp = m_size;
       clear();
       m_size = size_temp;

       // again don't really need to call destructors, just need to delete memory block
       // let clear() & std::move() handle memory management
       //delete[] m_data;
       ::operator delete(m_data, m_capacity * sizeof(T), align_val);
       m_data = new_data;
       m_capacity = new_capacity;
   }

public:

    // empty vec still has capacity of 2
    Vector() {
        std::cout << "Vector::Vector()\n";
        resize(2);
    }

    ~Vector() {
        std::cout << "Vector::~Vector()\n";
        // don't really need to call destructors,
        // call clear and then delete memory block
        // delete[] m_data;
        resize(0);
    }

    void push_back(const T& val) {
        std::cout << "Vector::push_back<copy>() called with: " << val << "\n";
        if (m_size == m_capacity) {
            resize();
        }
        new (&m_data[m_size]) T(val);
        ++m_size;
        std::cout << "Vector::push_back<copy>() end\n";
    }

    void push_back(T&& val) {
        std::cout << "Vector::push_back<move>() called with: " << val << "\n";
        if (m_size == m_capacity) {
            resize();
        }
        new (&m_data[m_size++]) T(std::move(val));
        std::cout << "Vector::push_back<move>() end\n";
    }

    template<typename... Args>
    T& emplace_back(Args&&... args) {
        std::cout << "Vector::emplace_back() called: " << "\n";
        if (m_size == m_capacity) {
            resize();
        }
        new (&m_data[m_size++]) T(std::forward<Args>(args)...);
        std::cout << "Vector::push_back() end\n";

        return m_data[m_size - 1];
    }

    void pop_back() {
        std::cout << "Vector::pop_back() called: " << "\n";
        if (m_size > 0) {
            m_data[--m_size].~T();
        }
        std::cout << "Vector::pop_back() end: " << "\n";
    }

    void clear() {
        std::cout << "Vector::clear() called: " << "\n";
        if (m_size > 0) {
            for (size_t i = 0; i < m_size; i++) {
                m_data[i].~T();
            }
            m_size = 0;
        }
        std::cout << "Vector::clear() end: " << "\n";
    }

    const T& operator[](size_t idx) const { return m_data[idx]; }
    T& operator[](size_t idx) { return m_data[idx]; }

    size_t size() const { return m_size; }

    size_t capacity() const { return m_capacity; }

};

template<typename T>
void print_vec(const Vector<T>& vec) {
    std::cout << "vec size: " << vec.size() << ", vec capacity: " << vec.capacity();
    std::cout << " elements: [ ";
    for (size_t i = 0; i < vec.size(); i++) {
        auto append = i == vec.size() -1 ? " " : ", ";
        std::cout << vec[i] << append;
    }
    std::cout << "] \n";
}

struct Vec3 {
    float x{0.0f}, y{0.0f}, z{0.0f};
    float* test_buff{nullptr};

public:
    // base cons dest
    Vec3() {
        std::cout << "Vec3 Const \n";
        test_buff = new float[3];
        test_buff[0] = 1;
        test_buff[1] = 2;
        test_buff[2] = 3;
    }

    ~Vec3() {
        std::cout << "Vec3 Destruct \n";
        if (test_buff != nullptr) {
            delete[] test_buff;
        }
    }

    // data cons
    Vec3(float scalar) : x{scalar}, y{scalar}, z{scalar} {
        std::cout << "Vec3 Const Scalar\n";
        test_buff = new float[3];
        test_buff[0] = 1;
        test_buff[1] = 2;
        test_buff[2] = 3;
    }

    Vec3(float x, float y, float z) : x{x}, y{y}, z{z} {
        std::cout << "Vec3 Const Explicit\n";
        test_buff = new float[3];
        test_buff[0] = 1;
        test_buff[1] = 2;
        test_buff[2] = 3;
    }

    // copy cons and assign
    Vec3(const Vec3& other) : Vec3(other.x, other.y, other.z) {
        std::cout << "Vec3 Copy Construct \n";
        test_buff[0] = other.test_buff[0];
        test_buff[1] = other.test_buff[1];
        test_buff[2] = other.test_buff[2];
    }

    Vec3& operator=(const Vec3& other) {
        std::cout << "Vec3 Copy Assign \n";
        x = other.x;
        y = other.y;
        z = other.z;
        if (other.test_buff != nullptr) {
            if (test_buff == nullptr) {
               test_buff = new float[3];
            }
            test_buff[0] = other.test_buff[0];
            test_buff[1] = other.test_buff[1];
            test_buff[2] = other.test_buff[2];
        } else {
            if (test_buff != nullptr) {
                delete[] test_buff;
                test_buff = nullptr;
            }
        }
        return *this;
    }

    // move cons and assign
    Vec3(Vec3&& other) : Vec3(other.x, other.y, other.z) {
        std::cout << "Vec3 Move Construct \n";

        if (this != &other) {
            if (test_buff != nullptr) {
                delete[] test_buff;
            }

            test_buff = other.test_buff;
            other.test_buff = nullptr;
        }
    }

    Vec3& operator=(Vec3&& other) {
        std::cout << "Vec3 Move Assign \n";

        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;

            if (test_buff != nullptr) {
                delete[] test_buff;
            }
            test_buff = other.test_buff;
            other.test_buff = nullptr;
        }
        return *this;
    }

    // impl stream output
    friend std::ostream& operator<<(std::ostream& out, const Vec3& vec);
};

std::ostream& operator<<(std::ostream& out, const Vec3& vec) {
    out << "Vec3{" << vec.x << "," << vec.y << "," << vec.z << "}";
    return out;
}

int main() {

    //string example
    bool string_example{false};
    if (string_example) {
        std::cout << "====================\n";
        Vector<std::string> vector;
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "push_back(): Cherno\n";
        vector.push_back("Cherno");
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "push_back(): C++\n";
        vector.push_back("C++");
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "push_back(): Vector\n";
        vector.push_back("Vector");
        print_vec(vector);
        std::cout << "====================\n";
    }

    //vec3 example
    bool vec3_example{true};
    if (vec3_example) {
        std::cout << "====================\n";
        Vector<Vec3> vector;
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "push_back(): Vec3(1)\n";
        Vec3 temp{1};
        if (temp.test_buff == nullptr) {
            std::cout << "somehow test test_buff nullptr here \n";
        } else {
            std::cout << "temp test_buff still good \n";
        }
        vector.push_back(temp);
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "push_back(): Vec3(1, 2, 4)\n";
        vector.push_back(Vec3(1, 2, 4));
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "push_back(): Vec3()\n";
        vector.push_back(Vec3());
        print_vec(vector);
        std::cout << "--------------------\n";


        std::cout << "push_back(): Vec3(vector[0])\n";
        vector.push_back(Vec3(vector[0]));
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "push_back(): const Vec3()\n";
        const auto const_vec3 = Vec3();
        vector.push_back(const_vec3);
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "pop_back()\n";
        vector.pop_back();
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "clear()\n";
        vector.clear();
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "emplace_back(): (1)\n";
        vector.emplace_back(1);
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "emplace_back(): (1, 2, 4)\n";
        vector.emplace_back(1, 2, 4);
        print_vec(vector);
        std::cout << "--------------------\n";

        std::cout << "emplace_back(): ()\n";
        vector.emplace_back();
        print_vec(vector);
        std::cout << "--------------------\n";


        std::cout << "emplace_back(): (vector[0])\n";
        vector.emplace_back(vector[0]);
        print_vec(vector);
        std::cout << "====================\n";
    }

}
