#include "test_runner.h"
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
    SimpleVector() = default;
    explicit SimpleVector(size_t size);
    ~SimpleVector();

    T& operator[](size_t index);

    T* begin();
    T* end();

    size_t Size() const;
    size_t Capacity() const;
    void Push_Back(const T& v);

};

template <typename T>
SimpleVector<T>::SimpleVector(size_t _size) : 
    value(new T[_size]), size(_size), capacity(_size)
{}

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
T* SimpleVector<T>::begin()
{ return value; }

template <typename T>
T* SimpleVector<T>::end()
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
    sv[1] = 1.2;
    sv[2] = 5.5;
    sv[3] = 4.4;
    sv[4] = 3.0;
    sv[0] = 2.7;
    //sv[5] = 3; 
    float array[SPECIAL_SIZE] = { 2.7, 1.2, 5.5, 4.4, 3.0};

    for (size_t i = 0; i < SPECIAL_SIZE; ++i)
    {
        ASSERT_EQUAL(sv[i], array[i]);
    }
}

void TestEqual_3()
{
    const size_t SPECIAL_SIZE = 5;
    SimpleVector<float> sv(5);
    sv[1] = 1.2;
    sv[2] = 5.5;
    sv[3] = 4.4;
    sv[4] = 3.0;
    sv[0] = 2.7;
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
    return 0;
}