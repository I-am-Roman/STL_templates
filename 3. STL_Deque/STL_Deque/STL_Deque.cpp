// STL_Deque.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "test_runner.h"

#include <vector>
#include <utility>

using namespace std;
/****************************************************************/
/*                         Q U E U E                            */
/****************************************************************/
//deque based on two vectors
template <typename T>
class deque
{
private:
    // ------>
    // 8 6 5 2 4 7 
    // 2 4 7 ------>
    vector<T> front;
    // <------ 8 6 5
    vector<T> back;

public:

    deque() = default;
    


    void push_front(const T& value);
    void push_back(const T& value);
    bool empty() const;
    size_t size() const;
    void clear();

    const T& Front() const;
    const T& Back() const;
    const T& At(const size_t index) const;
    const T& operator[](size_t index);

};
//////////////////////////////////////////////////

template <typename T>
void deque<T>::push_front(const T& value)
{
    front.push_back(value);
}

template <typename T>
void deque<T>::push_back(const T& value)
{
    back.push_back(value);
}

template <typename T>
bool deque<T>::empty() const
{
    return (front.empty() && back.empty());
}

template <typename T>
size_t deque<T>::size() const
{
    return (front.size() + back.size());
}

template <typename T>
void deque<T>::clear() 
{
    if (!front.empty())
    {
        front.clear();
    }
    if (!back.empty())
    {
        back.clear();
    }
}

template <typename T>
const T& deque<T>::Front() const
{
    if (front.empty())
    {
        return back.front();
    }
    return front.back();
}

template <typename T>
const T& deque<T> :: Back() const
{
    if (back.empty())
    {
        return front.front();
    }
    return back.back();
}

template <typename T>
const T& deque<T> :: At(const size_t index) const
{
    if (index >= size())
    {
        throw out_of_range("Out_of_range");
    }

    if (index < front.size())
    {
        return front[(front.size() - 1) - index];
    }

    return back[index - front.size()];
}

template <typename T>
const T& deque<T> :: operator[](size_t index) 
{
    if (index < front.size())
    {
        return front[(front.size() - 1) - index];
    }
    return back[index - front.size()];
}
/****************************************************************/
/*                         T E S T                              */
/****************************************************************/

//1
void Test_on_push()
{
    deque<int> dec;
    dec.push_back(2);
    dec.push_back(4);
    dec.push_back(5);
    dec.push_back(6);
    dec.push_back(7);
    dec.push_back(8);

    vector<int> true_res_1 = { 2,4,5,6,7,8 };
    for (size_t i = 0; i < true_res_1.size(); i++)
    {
        ASSERT_EQUAL(true_res_1[i], dec[i]);
    }
    
    dec.clear();
    dec.push_front(2);
    dec.push_front(4);
    dec.push_front(5);
    dec.push_front(6);
    dec.push_front(7);
    dec.push_front(8);

    vector<int> true_res_2 (true_res_1.rbegin(), true_res_1.rend());
    for (size_t i = 0; i < true_res_1.size(); i++)
    {
        ASSERT_EQUAL(true_res_2[i], dec[i]);
    }

    true_res_2.clear();
    dec.clear();

    dec.push_front(2);
    dec.push_front(4);
    dec.push_back(5);
    dec.push_back(6);
    dec.push_front(7);
    dec.push_back(8);

    true_res_2 = { 7,4,2,5,6,8 };
    for (size_t i = 0; i < true_res_1.size(); i++)
    {
        ASSERT_EQUAL(true_res_2[i], dec[i]);
    }

}

//2
void Test_on_iterator()
{
    deque<float> dec;
    dec.push_front(-13.4);
    dec.push_front(1.74);
    dec.push_back(-50.4);
    dec.push_back(67.2);
    dec.push_front(7.7777);
    dec.push_back(8.0000);
    dec.push_front(-87.5);

    auto front = dec.Front();
    ASSERT_EQUAL(-87.5, front);
    auto back = dec.Back();
    ASSERT_EQUAL(8, back);
    auto middle = dec.At(3);
    ASSERT_EQUAL(float(-13.4), middle);
}


/****************************************************************/
/*                         M A I N                              */
/****************************************************************/
int main()
{
    TestRunner tr;
    RUN_TEST(tr, Test_on_push);
    RUN_TEST(tr, Test_on_iterator);
    return 0;
}
