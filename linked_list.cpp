#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Node
{
    int data;
    Node *next;
    
    // default constructor
    Node(int new_data) : data(new_data) {
        next = nullptr;
    }

};

class LinkedList
{
  public:
    LinkedList(int value);
    ~LinkedList();
    void prepend(int value);                // insert value to the front
    void append(int value);                 // append value to the end
    void remove(int value);                 // remove node with the specified value
    void sort();                            // Main sort function call
    void _mergeSort(Node** start_node);     // helper function for sort
    Node* _sortedMerge(Node* a, Node* b);   // helper function for sort
    void _splitList(Node** start_node, Node** first, Node** second); // helper function for sort
    void swap(LinkedList* target);          // swap two linked lists
    void swapNode(int a, int b);            // swap nodes within the linked list
    vector<int> toList() const;             // convert to vector
    int size();

  private:
    Node* head;
    int size;
};

// default constructor
LinkedList::LinkedList(int value) : head(new Node(value)) {
    head->next = nullptr;
    ++size;
}

// destructor to free all allocated memory
LinkedList::~LinkedList() {
    cout << "Linked list destructor called." << endl;
    Node* curr_node = head;
    while (curr_node != nullptr) {
        head = head->next;
        delete curr_node;
    }
}

// add node with new data to the front of the linked list
void LinkedList::prepend(int new_data)
{
    Node* new_node = new Node(new_data);
    Node* temp = head;
    head = new_node;
    new_node->next = temp;
    ++size;
}

// add node with new data to the end of the linked list
void LinkedList::append(int new_data)
{
    Node* curr_node = head;
    while (curr_node->next != nullptr)
    {
        curr_node = curr_node->next;
    }
    curr_node->next = new Node(new_data);
    ++size;
}

// remove all nodes with the given value
void LinkedList::remove(int value)
{
    Node* curr = head;
    Node* prev = nullptr;
    while (curr != nullptr) {
        if (curr->data == value) {
            Node* temp = curr->next;
            if (curr == head) {
                head = temp;
                delete curr;
                curr = temp;
                --size;
            }
            else {
                prev->next = temp;
                delete curr;
                curr = temp;
                --size;
            }
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }

}

// NEW: sort the Linked List
void LinkedList::sort() {
    _mergeSort(&head);
}

// NEW: helper function to sort a linked list with merge sort algorithm
void LinkedList::_mergeSort(Node** start_node) {
    if (*start_node == nullptr || (*start_node)->next == nullptr) return;

    Node* first;
    Node* second;

    _splitList(start_node, &first, &second);

    _mergeSort(&first);
    _mergeSort(&second);

    *start_node = _sortedMerge(first, second);
}

// NEW: helper function to merged two sorted linked lists
Node* LinkedList::_sortedMerge(Node* a, Node* b) {
    Node* start_ptr;

    if (a == nullptr) return b;
    else if (b == nullptr) return a;

    // recursively merge two lists in ascending order
    if (a->data <= b->data) {
        start_ptr = a;
        a->next = _sortedMerge(a->next, b);
    }
    else {
        start_ptr = b;
        b->next = _sortedMerge(a, b->next);
    }

    return start_ptr;
}

// NEW: helper function to split the linked list into two equal halves
void LinkedList::_splitList(Node** start_node, Node** first, Node** second) {
    Node* slow;
    Node* fast;
    slow = *start_node;
    fast = (*start_node)->next;
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *first = *start_node;
    *second = slow->next;
    slow->next = nullptr;
}

// NEW: swap current linked list with another
void LinkedList::swap(LinkedList* target) {
    Node* temp(head);
    int temp_size(size);

    head = target->head;
    size = target->size;

    target->head = temp;
    target->size = temp_size;
}

// New: swap the first occurences of two values in a linked list
void LinkedList::swapNode(int a, int b) {
    Node* prev_a;
    Node* curr_a = head;
    while (curr_a != nullptr) {
        if (curr_a->data == a) {
            break;
        }
        prev_a = curr_a;
        curr_a = curr_a->next;
    }

    if (curr_a == nullptr) return;

    Node* prev_b;
    Node* curr_b = head;
    while (curr_b != nullptr) {
        if (curr_b->data == b) {
            break;
        }
        prev_b = curr_b;
        curr_b = curr_b->next;
    }

    if (curr_b == nullptr) return;

    prev_a->next = curr_b;
    Node* temp = curr_b->next;
    curr_b->next = curr_a->next;
    prev_b->next = curr_a;
    curr_a->next = temp;
}

// return the linked list in vector form
vector<int> LinkedList::toList() const
{
    vector<int> output;
    Node* curr_node = head;
    while (curr_node)
    {
        output.push_back(curr_node->data);
        curr_node = curr_node->next;
    }
    return output;
}

// print vector form linked list
void printVector(const vector<int>& target) {
    for (auto elem:target) {
        cout << elem << " ";
    }
    cout << endl;
}

int main()
{
    LinkedList* linked_list_1 = new LinkedList(30);
    linked_list_1->append(20);
    linked_list_1->append(0);
    linked_list_1->append(40);
    linked_list_1->prepend(10);
    linked_list_1->prepend(60);
    linked_list_1->prepend(70);
    linked_list_1->prepend(50);

    LinkedList* linked_list_2 = new LinkedList(25);
    linked_list_2->append(22);  
    linked_list_2->append(4);
    linked_list_2->append(47);
    linked_list_2->prepend(11);
    linked_list_2->prepend(62);
    linked_list_2->prepend(65);

    // test swap method
    linked_list_1->swap(linked_list_2);
    assert(linked_list_1->toList() == vector<int>({65, 62, 11, 25, 22, 4, 47}));
    assert(linked_list_2->toList() == vector<int>({50, 70, 60, 10, 30, 20, 0, 40}));
    
    // test swapNode method
    linked_list_2->swapNode(70, 0);
    assert(linked_list_2->toList() == vector<int>({50, 0, 60, 10, 30, 20, 70, 40}));

    // test sort method
    linked_list_2->sort();
    assert(linked_list_2->toList() == vector<int>({0, 10, 20, 30, 40, 50, 60, 70}));

    return 0;
}
