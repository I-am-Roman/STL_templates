
#include <iostream>
#include "test_runner.h"
/****************************************************************/
/*                         Q U E U E                            */
/****************************************************************/
template<typename T>
class node
{
public:
    T data; 
    node* next;
    node* previous; 
};

template<typename T>
class list
{
    node<T>* head;
    node<T>* tail; 
    size_t _size = 0;

public:
    list() :head(NULL), tail(NULL) {};
    ~list(); 	

    void insert(const T& value);
    void print(ostringstream& list_output) const;
    bool empty() const;
    void clear();
    size_t size() const;

    T pop_front();
    T pop_back ();
    void push_front(const T& value);
    void push_back(const T& value);

    void erase(const T& value);
    node<T>* begin();
    node<T>* end();
};
//////////////////////////////////////////////////////////////////////////////
template<typename T>
list<T>::~list()
{
    while (head)
    {
        tail = head->next; 
        delete head;
        head = tail;
        _size--;
    }
}

template<typename T>
void list<T>::insert(const T& value)
{
    push_back(value);
}

template<typename T>
void list<T>::print(ostringstream& list_output) const
{
    node<T>* temp = head;
    while (temp != NULL)
    {
        list_output << temp->data<<" ";
        temp = temp->next;
    }
    list_output << endl;
}

template<typename T>
bool list<T>::empty() const
{
    return (head == NULL);
}

template<typename T>
void list<T>::clear() 
{
    while (head)
    {
        tail = head->next;
        delete head;
        head = tail;
    }
}

template<typename T>
size_t list<T>::size() const
{
    return _size;
}

template<typename T>
T list<T>::pop_front()
{
    node<T>* temp = head;
    if (temp == NULL)
    {
        cout << "List are empty!" << endl;
        return NULL;
    }
    if (_size == 1)
    {
        T some_value = temp->data;
        _size--;
        delete temp;
        tail = head = NULL;
        return some_value;
    }
    if (_size == 2)
    {
        head = tail;
        T some_value = temp->data;
        _size--;
        delete temp;
        head->next = NULL;
        head->previous = NULL;
        return some_value;
    }

    head = head->next;

    tail->next = NULL;
    head->previous = NULL;
    T some_value = temp->data;
    _size--;
    temp = NULL;
    return some_value;
}

template<typename T>
T list<T>::pop_back()
{
    node<T>* temp = tail;
    if (temp == NULL)
    {
        cout << "List are empty!" << endl;
        return NULL;
    }
    if (_size == 1)
    {
        T some_value = temp->data;
        _size--;
        delete temp;
        tail = head = NULL;
        return some_value;
    }
    if (_size == 2)
    {
        tail = head;
        T some_value = temp->data;
        _size--;
        delete temp;
        head->next = NULL;
        head->previous = NULL;
        return some_value;
    }
    tail = tail->previous;
    //if we just delete tempand use tail->previous
    //our current node will connect with the 
    //help next->with node  what was deleted
    tail->next = NULL;
    head->previous = NULL;
    T some_value = temp->data;
    _size--;
    delete temp;
    return some_value;
}

template<typename T>
void list<T>::push_front(const T& value)
{
    // create new element 
    node<T>* temp = new node<T>;
    // We reset its pointer to the next one.
    temp->next = temp->previous = NULL;
    temp->data = value;

    if (head != NULL)
    {
        temp->next = head;
        head->previous = temp;
        head = temp;
        _size++;
    }
    else
    {
        temp->previous = NULL;
        head = tail = temp;
        _size++;
    }
}

template<typename T>
void list<T>::push_back(const T& value)
{
    // create new element 
    node<T>* temp = new node<T>;
    // We reset its pointer to the next one.
    temp->next = temp->previous = NULL;
    temp->data = value;

    if (head != NULL)
    {
        temp->previous = tail;
        tail->next = temp;
        tail = temp;
        _size++;
    }
    else
    {
        temp->previous = NULL;
        head = tail = temp;
        _size++;
    }
}

template<typename T>
void list<T>::erase(const T& value)
{
    node<T>* temp = head;
    while (temp != NULL  && _size != 0)
    {
        T del_val = temp->data;
        if(del_val == value)
        {
                // if it's the far left
                if (temp->previous == NULL)
                {
                    pop_front();
                    return;
                }
                // if it's the far right
                if (temp->next == NULL)
                {
                    pop_back();
                    return;
                }

            node<T>* prev = temp->previous;
            // lose connection with next node
            prev->next = temp->next;
            // lose connectiont with previous node
            (temp->next)->previous = prev;
            _size--;
            delete temp;
            return;
        }
        temp = temp->next;
    }
}

template<typename T>
node<T>* list<T>::begin()
{
    return head;
}

template<typename T>
node<T>* list<T>::end()
{
    return tail;
}

/****************************************************************/
/*                         T E S T                              */
/****************************************************************/
void Test_insert()
{
    list<int> l; 
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    l.push_front(0);
    l.push_front(-1);
    l.push_front(-2);
    size_t lenght = l.size();
    size_t true_size = 8;
    ASSERT_EQUAL(true_size, lenght);

    ostringstream list_output;
    l.print(list_output);

    const string result = list_output.str();
    const string true_result = "-2 -1 0 1 2 3 4 5 \n";
    ASSERT_EQUAL(true_result, result);

    l.clear();
    ostringstream list_output_when_list_empty;
    l.print(list_output_when_list_empty);

    const string result_2 = list_output_when_list_empty.str();
    const string true_result_2 = "\n";
    ASSERT_EQUAL(true_result_2, result_2);


    

    

    //for (it_begin = l.begin(); it_begin != l.end(); it_begin+=3)
    //{
    //    cout << it_begin->data <<" " << endl;
    //}

  

}  

void Test_iterator()
{
    list<string> l;
    l.insert("one");
    l.insert("two");
    l.insert("three");
    l.insert("four");
    l.insert("five");

    auto it_begin = l.begin();
    const string true_result_1 = "one";
    ASSERT_EQUAL(true_result_1, it_begin->data);

    auto it_end = l.end();
    const string true_result_2 = "five";
    ASSERT_EQUAL(true_result_2, it_end->data);

    ostringstream print_all_list;
    for (it_begin; it_begin !=NULL; it_begin = it_begin->next)
    {
        print_all_list << it_begin->data << " ";
    }
    print_all_list << endl;

    const string result = print_all_list.str();
    const string true_result = "one two three four five \n";
    ASSERT_EQUAL(true_result, result);
}

void Test_erase()
{
   
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_front(0);
    l.push_front(-1);
    l.push_front(-2);
    // -2 -1 2 1 2 3 4 5

    l.erase(2);
    l.erase(0);
    l.erase(1);
    l.erase(-1);

    {
        ostringstream print_erase_list;
        l.print(print_erase_list);
        const string result = print_erase_list.str();
        const string true_result = "-2 3 4 5 \n";
        ASSERT_EQUAL(true_result, result);
    }

    l.erase(-2);
    l.erase(5);
    {
        ostringstream print_erase_list;
        l.print(print_erase_list);
        const string result = print_erase_list.str();
        const string true_result = "3 4 \n";
        ASSERT_EQUAL(true_result, result);
    }

    l.erase(3);
    l.erase(4);
    
    {
        ostringstream print_erase_list;
        l.print(print_erase_list);
        const string result = print_erase_list.str();
        const string true_result = "\n";
        ASSERT_EQUAL(true_result, result);
    }

    l.erase(5);
    l.erase(NULL);

    {
        ostringstream print_erase_list;
        l.print(print_erase_list);
        const string result = print_erase_list.str();
        const string true_result = "\n";
        ASSERT_EQUAL(true_result, result);
    }
}

void Test_pop()
{  
    list<uint8_t> l;

    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_front(0);
    l.push_front(35);
    // 35 0 3 4 5

    ostringstream delete_elemens_list;
    delete_elemens_list << unsigned(l.pop_back()) <<" ";
    delete_elemens_list << unsigned(l.pop_front()) << " " ;
    delete_elemens_list << unsigned(l.pop_back()) << " ";

    const string result = delete_elemens_list.str();
    const string true_result = "5 35 4 ";
    ASSERT_EQUAL(true_result, result);

    delete_elemens_list << unsigned(l.pop_back()) << " ";
    delete_elemens_list << unsigned(l.pop_back()) << " ";
    const string result2 = delete_elemens_list.str();
    const string true_result2 = "5 35 4 3 0 ";
    ASSERT_EQUAL(true_result2, result2);

    l.push_back(4);
    l.push_back(5);
    delete_elemens_list << unsigned(l.pop_front()) << " ";
    delete_elemens_list << unsigned(l.pop_front()) << " ";

    const string result3 = delete_elemens_list.str();
    const string true_result3 = "5 35 4 3 0 4 5 ";
    ASSERT_EQUAL(true_result3, result3);
    
}

/****************************************************************/
/*                         M A I N                              */
/****************************************************************/
int main()
{
    TestRunner tr;
    RUN_TEST(tr, Test_insert);
    RUN_TEST(tr, Test_iterator);
    RUN_TEST(tr, Test_erase);
    RUN_TEST(tr, Test_pop);

    return 0;
}

