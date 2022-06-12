/*  ПРИМЕР
first->[NULL]
last ->[NULL]
Добавляется элемент : 5
[5 - first]
Добавляется элемент : 6
[6 - last] <- [5 - first]
Добавляется элемент : 7
[7 - last] <-[6] <- [5 - first] */

#include <iostream>
#include "test_runner.h"

using namespace std;
/****************************************************************/
/*                         Q U E U E                            */
/****************************************************************/
template<typename T>
class node
{
public:
    T data;
    node* next;
};

template<typename T>
class  Queue
{
private: 
    node<T>* first = NULL;
    node<T>* last = NULL;
    size_t size = 0;

public:
    Queue() = default;
    ~Queue();

    void clear();
    bool empty();
    void insert(const T& value);
    T pop_front();
    void print(ostringstream& queue_output);

    node<T>* begin();
    node<T>* end();

};
////////////////////////////////////////////////////////////////

template<typename F>
node<F>* Queue<F> ::begin()
{
    return first;
}

template<typename F>
node<F>* Queue<F> ::end()
{
    return last;
}

template<typename F>
bool Queue<F> ::empty()
{
    return (first == NULL);
}

template<typename F>
void Queue<F> ::insert(const F& value)
{
    // the one who was last is now the penultimate
    node<F>* before_the_last = last;
    // we allocate a clean place for the last element
    last = new node<F>;
    last->next = NULL;
    last->data = value;
    size++;
    if (empty())
    {
        first = last;
    }
    else    // behind the penultimate is the last
    {
        before_the_last->next = last;
    }
}

template<typename F>
F Queue<F> ::pop_front()
{
    // saving the value to be deleted
    // the first one goes away
    if (first == NULL)
    {
        //cout << "Queue is empty" << endl;
        return {};
    }
    F val = first->data;

    auto del_node = first;
    // the first one becomes the one who stood behind him
    first = first->next;
    delete del_node;
    size--;

    if (empty())
    {
        last = NULL;
    }
    return val;
}

template<typename F>
void Queue<F> ::print(ostringstream& queue_output)
{
    if (first == NULL)
    {
        queue_output << "Queue is empty!" << endl;
        return;
    }

    auto it_begin = first;
    auto it_end = last;
    size_t cope_size = size;

    while (cope_size)	
    {
        queue_output << it_begin->data << " ";
        it_begin = it_begin->next;
        cope_size--;
    }
    queue_output << "\n";
}

template<typename F>
void Queue<F> ::clear()
{
    if (first == NULL)
    {
        cout << "Queue is empty!" << endl;
        return;
    }

    while (size)
    {
        auto del_node = first;
        first = first->next;
        delete del_node;
        size--;
    }
}

template<typename F>
Queue<F> ::~Queue()
{
    while (size) 
    {
        auto del_node = first;
        first = first->next;
        delete del_node;
        size--;
    }
}

/****************************************************************/
/*                         T E S T S                            */
/****************************************************************/
//1
void Test_on_insert()
{
    Queue<int> que;
    que.insert(3);
    que.insert(4);
    que.insert(-5);
    que.insert(6);
    que.insert(-1);
    que.insert(0);

    ostringstream queue_output;
    que.print(queue_output);

    const string result = queue_output.str();
    const string true_result = "3 4 -5 6 -1 0 \n";
    ASSERT_EQUAL(true_result, result);
}
//2
void Test_on_clear()
{
    Queue<float> que;
    que.insert(3.3);
    que.insert(4.4);
    que.insert(-5.1);
    que.insert(6.7);
    que.insert(-1.4);
    que.insert(0.002);
    que.clear();

    ostringstream queue_output;
    que.print(queue_output);

    const string result = queue_output.str();
    const string true_result = "Queue is empty!\n";
    ASSERT_EQUAL(true_result, result);
}
//3
void Test_on_begin_and_end()
{
    Queue<string> que;
    que.insert("Red belt be C++");
    que.insert("Green belt be C++");
    que.insert("Programming is cool");
    que.insert("Yandex, mail, mozilla");    
    que.insert("   ");
    que.insert("Sunny, cloudy, rainy");

    ostringstream queue_output;
    auto it_begin = que.begin();
    auto it_end = que.end();

    queue_output << it_begin->data << endl;
    queue_output << it_end->data << endl;

    const string result = queue_output.str();
    const string true_result = "Red belt be C++\nSunny, cloudy, rainy\n";
    ASSERT_EQUAL(true_result, result);
}
//4
void Test_on_pop_front()
{
    Queue<double> que;
    que.insert(3.3333);
    que.insert(4.2346);
    que.insert(-5.456);
    que.insert(123.4362);
    que.insert(5673.3);
    que.insert(3264.345);

    double value_1 = que.pop_front();
    double true_result_1 = 3.3333;
    ASSERT_EQUAL(true_result_1, value_1);

    double value_2 = que.pop_front();
    double true_result_2 = 4.2346;
    ASSERT_EQUAL(true_result_2, value_2);

    double value_3 = que.pop_front();
    double true_result_3 = -5.456;
    ASSERT_EQUAL(true_result_3, value_3);

    que.clear();
    double value_4 = que.pop_front();
    ASSERT_EQUAL(NULL, value_4);
}

/****************************************************************/
/*                         M A I N                              */
/****************************************************************/

int main()
{
    TestRunner tr;
    RUN_TEST( tr,Test_on_insert);
    RUN_TEST(tr, Test_on_clear);
    RUN_TEST(tr, Test_on_begin_and_end);
    RUN_TEST(tr, Test_on_pop_front);
   
    system("PAUSE");
    return 0;
}