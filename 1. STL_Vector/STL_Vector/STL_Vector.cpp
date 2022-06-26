#include "test_runner.h"
#include <algorithm>
using namespace std;

/****************************************************************/
/*                          V E C T O R                         */
/****************************************************************/
template <typename T>
class SimpleVector
{
private:
    T* value = nullptr;
    size_t size;
    size_t capacity;
public:
    SimpleVector():size(0),capacity(0) {};
    explicit SimpleVector(size_t size) noexcept;
    //move constructor
    SimpleVector(SimpleVector<T>&& other);
    //copy constructor
    SimpleVector(const SimpleVector<T>& other);

    ~SimpleVector();

    T& operator[](size_t index);

    T* begin() const;
    T* end() const;

    size_t Size() const;
    size_t Capacity() const;
    void Push_Back(const T& v);

};

template <typename T>
SimpleVector<T>::SimpleVector(size_t _size) noexcept: 
    value(new T[_size]), size(_size), capacity(_size)
{}

//move constructor
template <typename T>
SimpleVector<T>::SimpleVector(SimpleVector<T>&& other):
    value(other.value), size(other.Size()), capacity(other.Capacity())
{
    cout << "Move constructor" << endl;
    other.value = nullptr;
    other.size = 0;
    other.capacity= 0;
}
//copy constructor
template <typename T>
SimpleVector<T>::SimpleVector(const SimpleVector<T>& other):
    value(new T[other.Size()]), size(other.Size()), capacity(other.Capacity())
{
    cout << "Copy constructor" << endl;
    copy(other.begin(), other.end(), begin());
}


template <typename T>
SimpleVector<T>::~SimpleVector()
{ delete[] value; }

template <typename T>
T& SimpleVector<T>::operator[](size_t index)
{ 
   // cout << "Capacity = " << capacity << endl;
    try 
    {
        if (index >= capacity)
        {
            char s[] = {"The element does not exist."};
            throw runtime_error(s);
        }
          return value[index]; 
    }
    catch (exception& ex)
    {
        cout << "Exception happens: " << ex.what();
    }
} 

template <typename T>
T* SimpleVector<T>::begin() const
{ return value; }

template <typename T>
T* SimpleVector<T>::end() const
{ return value + size; }

template <typename T>
size_t SimpleVector<T>::Size() const
{ return size; }

template <typename T>
size_t SimpleVector<T>::Capacity() const
{ return capacity; }

template <typename T>
void SimpleVector<T>::Push_Back(const T& v)
{
    if (Capacity() == 0)
    {
        T* temp = new T[++capacity]{ v };
        ++size;
        value = temp;
    }
    else
    {
        if (Size() == Capacity())
        {
            T* temp = new T[2 * capacity]{};
            capacity *= 2;

            for (size_t i = 0; i <= size; i++)
            {
                temp[i] = value[i];
            }
            delete[] value;
            value = temp;
        }
        value[size++] = v;
    }
}
/****************************************************************/
/*                          T E S T S                           */
/****************************************************************/

void TestEqual_1()
{
    const size_t SPECIAL_SIZE = 5;
    SimpleVector<int> sv;
    sv.Push_Back(-1);
    sv.Push_Back(9);
    sv.Push_Back(7);
    sv.Push_Back(-3);
    sv.Push_Back(-2);

    int array[SPECIAL_SIZE] = { -1,9,7,-3,-2 };

    for (size_t i = 0; i < SPECIAL_SIZE; ++i)
    {
        ASSERT_EQUAL(sv[i], array[i]);
    }
}

void TestEqual_2()
{
    const size_t SPECIAL_SIZE = 5;
    SimpleVector<float> sv(5);
    sv[1] = 1.2f;
    sv[2] = 5.5f;
    sv[3] = 4.4f;
    sv[4] = 3.0f;
    sv[0] = 2.7f;
    //sv[5] = 3; 
    float array[SPECIAL_SIZE] = { 2.7f, 1.2f, 5.5f, 4.4f, 3.0f};

    for (size_t i = 0; i < SPECIAL_SIZE; ++i)
    {
        ASSERT_EQUAL(sv[i], array[i]);
    }
}

void TestEqual_3()
{
    const size_t SPECIAL_SIZE = 5;
    SimpleVector<float> sv(5);
    sv[1] = 1.2f;
    sv[2] = 5.5f;
    sv[3] = 4.4f;
    sv[4] = 3.0f;
    sv[0] = 2.7f;
    //sv[5] = 3; 
    auto it_begin = sv.begin();
    auto it_end = sv.end();
    ASSERT_EQUAL(*it_begin, sv[0]);
    ASSERT_EQUAL(*(--it_end), sv[4]);

}


void TestEqual_4()
{
    const size_t SPECIAL_SIZE = 10;
    SimpleVector<char> sv(10);

    size_t equal_capacity = 10;
    size_t size = equal_capacity;
    ASSERT_EQUAL(equal_capacity, sv.Capacity());
    ASSERT_EQUAL(size, sv.Size());

    SimpleVector<char> sv_2;
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    sv_2.Push_Back('a');
    equal_capacity = 16;
    size = 9;

    ASSERT_EQUAL(equal_capacity, sv_2.Capacity());
    ASSERT_EQUAL(size, sv_2.Size());

}
/****************************************************************/
/*                          M A I N                             */
/****************************************************************/
int main()
{
   TestRunner tr;
   RUN_TEST(tr, TestEqual_1);
   RUN_TEST(tr, TestEqual_2);
   RUN_TEST(tr, TestEqual_3);
   RUN_TEST(tr, TestEqual_4);

    system("Pause");
    return 0;
}