#include <iostream>
#include <unordered_set>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data {
public:
    int value;
    string name;

    Data(int value, string name) {
        this->value = value;
        this->name = name;
    }

    void print() {
        cout << name << ", " << value << endl;
    }
};

template<typename T>
class Node {
public:
    T *value;
    Node<T> *next;
    Node<T> *prev;

    Node(T *value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }

    void print() {
        value->print();
    }
};

template<typename T>
class DoubleLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;

public:
    // No-arg constructor
    DoubleLinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    DoubleLinkedList(T *value) {
        Node<T> *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    ~DoubleLinkedList() {
        Node<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void printList() {
        Node<T> *temp = head;
        cout << "Current contents of list:" << endl;
        while (temp != nullptr) {
            temp->print();
            temp = temp->next;
        }
    }

    Node<T> *getHead() {
        if (head == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << head->value << endl;
        }
        return head;
    }

    Node<T> *getTail() {
        if (tail == nullptr) {
            cout << "Tail: nullptr" << endl;
        } else {
            cout << "Tail: " << tail->value << endl;
        }
        return tail;
    }

    int getLength() {
        cout << "Length: " << length << endl;
        return length;
    }

    Node<T> *get(int index) {
        if (index < 0 || index >= length)
            return nullptr;
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, T *value) {
        Node<T> *temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }


    // insert at tail
    void append(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }

    // Insert at head
    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    // Insert at index
    bool insert(int index, T *value) {
        if (index < 0 || index > length)
            return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }
        Node<T> *newNode = new Node<T>(value);
        Node<T> *prevNode = get(index - 1);
        Node<T> *nextNode = prevNode->next;
        newNode->prev = prevNode;
        newNode->next = nextNode;
        prevNode->next = newNode;
        nextNode->prev = newNode;
        length++;
        return true;
    }

    // delete at head
    void deleteAtHead() {
        if (length == 0) {
            cout << "The list is empty, nothing can be deleted." << endl;
            return;
        }
        // if the list is not empty, create temporary pointer to node that is to be deleted
        Node<T> *temp = head;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            // update head reference to remove the node from the list
            head = head->next;
            head->prev = nullptr;
        }
        cout << "Success.  Head node '" << temp->value->name << "' with data value " << temp->value->value
             << " was deleted." << endl;
        delete temp;
        length--;
    }

    // delete at tail
    void deleteAtTail() {
        if (length == 0) {
            // if the list is empty, nothing can be deleted
            return;
        }
        // if the list is not empty, create temporary pointer to node that is to be deleted
        Node<T> *temp = tail;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
        } else {
            // update tail pointer to remove the node from the list
            tail = temp->prev;
            // set the tail's next pointer to nullptr, ending the list
            tail->next = nullptr;
        }
        cout << "Success.  Tail node '" << temp->value->name << "' with data value " << temp->value->value
             << " was deleted." << endl;
        length--;
        delete temp;
    }

    // delete at index
    void deleteAtIndex(int index) {
        // check if index is within the bounds of the list
        if (index < 0 || index >= length) {
            // if index is out of bounds, do not delete anything
            cout << "Invalid node index, please try again." << endl;
            return;
        }
        Node<T> *nodeToDelete = get(index);
        if (nodeToDelete == head) {
            deleteAtHead();
            return;
        } else if (nodeToDelete == tail) {
            deleteAtTail();
            return;
        } else {
            // update nodeToDelete's previous and next pointers to remove the node from the list
            nodeToDelete->prev->next = nodeToDelete->next;
            nodeToDelete->next->prev = nodeToDelete->prev;
        }
        length--;
        delete nodeToDelete;
    }

    // delete list
    void deleteList() {
        Node<T> *current = head;

        while (current != nullptr) {

            if (length == 0) {
                return;
            }
            Node<T> *temp = current;
            if (length == 1) {
                head = nullptr;
                tail = nullptr;
            } else {
                current = current->next;
            }
            delete temp;
            --length;
        }
    }

    // sortList helper function
    void swapNodes(Node<T> *firstNode, Node<T> *secondNode) {
        Node<T> *firstNodePrev = firstNode->prev;
        Node<T> *secondNodeNext = secondNode->next;

        // If firstNode is not head node, make its next pointer point to the second node
        // Otherwise, if firstNode is the head node, update the head to point to the second node.
        if (firstNodePrev != nullptr) {
            firstNodePrev->next = secondNode;
        // if firstNode is head node, make the head point to the second node
        } else {
            head = secondNode;
        }

        // If secondNode is not the tail, make its previous pointer point to the first node
        // Otherwise, if secondNode is the tail node, update the tail to point to the first node.
        if (secondNodeNext != nullptr) {
            secondNodeNext->prev = firstNode;
        // if secondNode is the tail, make the tail point to the first node
        } else {
            tail = firstNode;
        }

        // Update the next and previous pointers of firstNode and secondNode to complete the swap.
        firstNode->next = secondNode->next;
        secondNode->prev = firstNode->prev;
        firstNode->prev = secondNode;
        secondNode->next = firstNode;
    }

    // sort list
    void sortList() {
        for (int i = 0; i < length; ++i) {
            Node<T> *currentNode = head;
            Node<T> *nextNode = currentNode->next;

            // this loop runs for the unsorted part of the list,
            // aka the remaining number of iterations of the first loop
            for (int j = 0; j < length - i - 1; ++j) {
                if (currentNode->value->value > nextNode->value->value) {
                    swapNodes(currentNode, nextNode);
                // if a swap was not necessary, move on to check the next node
                } else {
                    currentNode = nextNode;
                }
                nextNode = currentNode->next;
            }
        }
    }

    // remove multiples
    void removeMultiples() {
        // set the key to the head of the list
        Node<T> *key = head;
        // node to traverse the list
        Node<T> *current;
        // temporary node to keep track of pointer after node to be deleted so deleteAtIndex can be used
        Node<T> *nextCurrent;
        // node to hold the position of the next key in case a multiple is found and deleteAtIndex is called
        Node<T> *nextKey;
        // to keep track of the index of the key
        int keyIndex = 0;
        // to keep track of the index of the current node
        int currentIndex;
        // to keep track of multiples found
        int multipleCount;

        while (key != nullptr) {
            // this includes the key in the multiple count
            multipleCount = 1;
            // set current node to the node after the key
            current = key->next;
            // keep track of the index of the current node, will always be at least one greater than the key index
            currentIndex = keyIndex + 1;

            while (current != nullptr) {
                if ((key->value->value == current->value->value) || (key->value->name == current->value->name)) {
                    ++multipleCount;
                    // keep track of node after current because it would be lost if delete at index was called without it
                    nextCurrent = current->next;
                    deleteAtIndex(currentIndex);
                    // this moves current to the next node
                    current = nextCurrent;
                } else {
                    // if a match was not found, move to the next node
                    current = current->next;
                    ++currentIndex;
                }

            }
            // save the next key in case a multiple of the key was found, so it can be deleted
            nextKey = key->next;
            // if multipleCount is > 1, a multiple was found
            if (multipleCount > 1) {
                deleteAtIndex(keyIndex);
            } else {
                // if a multiple was not found, the key index needs to be incremented to properly keep track of the key index
                ++keyIndex;
            }
            // after checking all the nodes for a multiple of key, move to the next node and repeat
            key = nextKey;
        }
    }

    // misinterpreted remove multiples
    void removeDuplicates() {
        // make the head node the first duplicateKey to check against other nodes
        Node<T> *duplicateKey = head;

        // iterate duplicateKey over entire list
        while (duplicateKey != nullptr) {

            // start each duplicateKey/current comparison with the node after duplicateKey
            Node<T> *current = duplicateKey->next;

            // iterate current over all nodes in list (except for the duplicateKey node)
            while (current != nullptr) {

                // check if the values match
                if (duplicateKey->value->value == current->value->value) {

                    // if the values match, create a temp pointer for the node to be deleted from list
                    // this ensures the node to be deleted is kept track of, so it can be deleted successfully
                    Node<T> *temp = current;

                    // If the current pointer is the tail, it will skip this if statement because the tail does not need its prev pointer moved
                    // Alternatively, if the current node is not the tail, make the next node point to the previous node
                    if (current->next != nullptr)
                        current->next->prev = current->prev;

                    // If the current pointer is the head, it will skip this if statement because the head does not need its next pointer moved
                    // Alternatively, if the current node is not the head, make the previous node point to the next node
                    if (current->prev != nullptr)
                        current->prev->next = current->next;

                    // move the current pointer to the following node for the next comparison
                    current = current->next;

                    // Delete the node that had matching data
                    delete temp;

                // If the comparison did not find a match, move the current pointer to the following node for the next comparison
                } else {
                    current = current->next;
                }
            }
            // After comparing each current node to duplicateKey, move multkey to the next unique node for the next round of comparisons
            duplicateKey = duplicateKey->next;
        }
    }

    // count multiples
    void countMultiples(T *value) {
        Node<T> *current = head;
        Data *userVal = value;
        int count = 0;

        while (current != nullptr) {

            if (current->value->value == userVal->value) {
                ++count;
            }
            current = current->next;
        }
        if (count == 1) {
            cout << "*    *    *    *    *    *    *    *    *    *    *" << endl;
            cout << "There was " << count << " multiple of " << userVal->value << " in the list" << endl;
//            cout << "There was " << count << " multiple of the entry you provided." << endl;
            cout << "*    *    *    *    *    *    *    *    *    *    *" << endl;
        } else {
            cout << "*    *    *    *    *    *    *    *    *    *    *" << endl;
            cout << "There were " << count << " multiples of " << userVal->value << " in the list" << endl;
//            cout << "There were " << count << " multiples of the entry you provided." << endl;
            cout << "*    *    *    *    *    *    *    *    *    *    *" << endl;
        }
    }

    // split list, even odd split
    void evenOddSplit() {
        DoubleLinkedList<T> *evenList = new DoubleLinkedList<Data>();
        DoubleLinkedList<T> *oddList = new DoubleLinkedList<Data>();
        Node<T> *current = head;
        // for safe deletion of nodes
        Node<T> *temp;
        // index of DoubleLinkedList starts at 0
        int index = 0;

        while (current != nullptr) {
            // Keep track of node so it can be deleted safely
            temp = current;
            // if index is even, add to evenList
            if (index % 2 == 0) {
                evenList->append(current->value);
                ++index;

                // if index is odd, add to oddList
            } else {
                oddList->append(current->value);
                ++index;
            }
            // move current to next node
            current = current->next;
            delete temp;
        }
        cout << "Even indices:" << endl;
        evenList->printList();
        cout << "Odd indices:" << endl;
        oddList->printList();
    }

    // reverse list
    void reverseList() {
        Node<T> *current = head;
        Node<T> *temp;
        tail = head;

        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr) {
            head = temp->prev;
        }

    }

    void createList() {
        string name;
        int value;
        char keepAdding;
        Data *newData;
        DoubleLinkedList<Data> *ll1;

        cout << "Enter the name and value of the first node, separated by a space: " << endl;
        cin >> name;
        cin >> value;

        newData = new Data(value, name);
        ll1 = new DoubleLinkedList<Data>(newData);

        keepAdding = 'y';
        while (keepAdding == 'y' || keepAdding == 'Y') {
            cout << "Add another node? y/n: " << endl;
            cin >> keepAdding;

            if (keepAdding == 'y' || keepAdding == 'Y') {
                cout << "Enter the name and value of the next node you want to add: " << endl;
                cin >> name;
                cin >> value;

                newData = new Data(value, name);
                ll1->append(newData);
            }
        }
    }

    void autoCreateList() {
        Data *d1 = new Data(10, "a");
        Data *d2 = new Data(20, "b");
        Data *d3 = new Data(30, "c");
        Data *d4 = new Data(40, "d");
        Data *d5 = new Data(50, "e");
        Data *d6 = new Data(60, "f");
        Data *d7 = new Data(70, "g");
        Data *d8 = new Data(80, "h");

        DoubleLinkedList<Data> *ll1 = new DoubleLinkedList<Data>(d1);
        ll1->append(d2);
        ll1->append(d3);
        ll1->append(d4);
        ll1->append(d5);
        ll1->append(d6);
        ll1->append(d7);
        ll1->append(d8);
        ll1->printList();
    }

};


int main() {
    // for menu functions
    string input;
    int userChoice = 0;

    // create list
    DoubleLinkedList<Data> *ll1;

    // for create list
    char keepAdding;

    // for insert functions
    Data *newData;
    string name;
    int value;
    int index;

    cout << "\nHello!  Welcome to the Doubly-Linked List Program!\n" << endl;
    cout << "This program was written by Robert Ashe in CS210: Data Stuctures,\nunder the instruction of Professor Manju Muralidharan." << endl;
    cout << "\nTo navigate to the main menu, enter a positive number: " << endl;

    cin >> userChoice;

    while (userChoice > 0) {
        // main menu
        cout << "Main Menu" << endl;
        cout << "Choose any of the options by entering the number next to it: " << endl;
        cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;

        cout << "1: Create a list." << endl;
        cout << "2: Delete a list" << endl;
        cout << "3: Insert a new entry at the beginning of the list. (Insert at Head)" << endl;
        cout << "4: Insert a new entry at the end of the list. (Insert at Tail)" << endl;
        cout << "5: Insert a new entry at the index you provide. (Insert at Index)" << endl;
        cout << "6: Delete entry at beginning of list. (Delete at Head)" << endl;
        cout << "7: Delete entry at end of list. (Delete at Tail)" << endl;
        cout << "8: Delete entry at the index you provide. (Delete at Index)" << endl;
        cout << "9: Reverse the list. (Reverse List)" << endl;
        cout << "10: Sort the list in ascending order. (Sort List)" << endl;
        cout << "11: Count the number of entries that match a number you provide. (Count Multiples)" << endl;
        cout << "12: Delete entries that have matching data. (Delete Multiples)" << endl;
        cout << "13: Split the list by even and odd indices. Also quits program. (Split List)" << endl;
        cout << "14: Quit." << endl;

        cout << "***************************************************************************" << endl;

        cin >> userChoice;

        if (userChoice > 0) {
            switch (userChoice) {
                case 1: // Create new list

                    cout << "Enter the name and value of the first node, separated by a space: " << endl;
                    cin >> name;
                    cin >> value;

                    newData = new Data(value, name);
                    ll1 = new DoubleLinkedList<Data>(newData);

                    keepAdding = 'y';
                    while (keepAdding == 'y' || keepAdding == 'Y') {
                        cout << "Add another node? y/n: " << endl;
                        cin >> keepAdding;

                        if (keepAdding == 'y' || keepAdding == 'Y') {
                            cout << "Enter the name and value of the next node you want to add, separated by a space: " << endl;
                            cin >> name;
                            cin >> value;

                            newData = new Data(value, name);
                            ll1->append(newData);
                        }
                    }
                    ll1->printList();
                    cout << endl;
                    break;
                case 2:
                    // Delete a list
                    ll1->deleteList();

                    // no existing list to print, but helpful if user knows that the list is empty
                    cout << "Current contents of list:\nList is empty" << endl;

                    // this ends the program
                    userChoice = -1;
                    break;
                case 3:
                    // insert at head
                    cout << "Enter the name and value of the node you wish to insert, separated by a space: " << endl;
                    cin >> name;
                    cin >> value;

                    newData = new Data(value, name);
                    ll1->prepend(newData);
                    ll1->printList();
                    cout << endl;
                    break;
                case 4:
                    // insert at tail
                    cout << "Enter the name and value of the node you wish to insert, separated by a space: " << endl;
                    cin >> name;
                    cin >> value;

                    newData = new Data(value, name);
                    ll1->append(newData);
                    ll1->printList();
                    cout << endl;
                    break;
                case 5:
                    // insert at index
                    cout << "Enter the name and value of the node you wish to insert, separated by a space: " << endl;
                    cin >> name;
                    cin >> value;
                    cout << "Enter the index where you want the node inserted.  Node indices start at 0: " << endl;
                    cin >> index;

                    newData = new Data(value, name);
                    ll1->insert(index, newData);
                    ll1->printList();
                    cout << endl;
                    break;
                case 6:
                    // delete at head
                    ll1->deleteAtHead();
                    ll1->printList();
                    cout << endl;
                    break;
                case 7:
                    // delete at tail
                    ll1->deleteAtTail();
                    ll1->printList();
                    cout << endl;
                    break;
                case 8:
                    // delete at index
                    cout << "Enter the index of the entry you with to delete: " << endl;
                    cin >> index;

                    ll1->deleteAtIndex(index);
                    ll1->printList();
                    cout << endl;
                    break;
                case 9:
                    // reverse list
                    ll1->reverseList();
                    ll1->printList();
                    cout << endl;
                    break;
                case 10:
                    // sort list
                    ll1->sortList();
                    ll1->printList();
                    cout << endl;
                    break;
                case 11:
                    // count multiples
                    // set name to an empty string because it's not being used, but it's necessary to create the node
                    name = "";
                    cout << "Enter the value of the entry you wish to find the number of multiples for: " << endl;
                    cin >> value;

                    newData = new Data(value, name);
                    ll1->countMultiples(newData);

                    ll1->printList();
                    cout << endl;
                    break;
                case 12:
                    // delete multiples
                    ll1->removeMultiples();
                    ll1->printList();
                    cout << endl;
                    break;
                case 13:
                    // split list and end the program
                    ll1->evenOddSplit();
                    // delete original list
                    ll1->deleteList();

                    cout << "Thanks for using the Doubly-Linked List Program!  Have a great Day!" << endl;

                    // this ends the program
                    userChoice = -1;
                    break;
                case 14:
                    cout << "Thanks for using the Doubly-Linked List Program!  Have a great day!" << endl;

                    // this ends the program
                    userChoice = -1;
                default:
                    cout << "Invalid choice, please enter a number from 1 to 13.  Unless you want to quit, then enter 14.." << endl;
            }
        }
        cout << "***************************************************************************" << endl;
    }
    return 0;
}