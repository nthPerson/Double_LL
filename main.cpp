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
//    cout << value << ", " << name << endl;
//    cout << name << " " << endl;
    }
};

// Node Class : Node for the LinkedList
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
//      cout << "contents of list:" << endl;
        value->print();
    }
};

// LinkedList Class : Container for Nodes
template<typename T>
class DoubleLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;

public:
    // No-arg constructor
//    DoubleLinkedList() {
//        head = nullptr;
//        tail = nullptr;
//        length = 0;
//    }

    // Constructor
    DoubleLinkedList(T *value) {
        Node<T> *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    // Destructor
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

    // get and set
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

    // All insert methods
    // Insert at end
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

    // Insert at beginning

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

    // Insert at Index

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
        Node<T> *prev1 = get(index - 1);
        Node<T> *next1 = prev1->next;
        newNode->prev = prev1;
        newNode->next = next1;
        prev1->next = newNode;
        next1->prev = newNode;
        length++;
        return true;
    }

    // All delete Methods
    // Write DeleteHead, DeleteTail & DeleteAtIndex here

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
            cout << "Success.  Head node '" << temp->value->name << "' with data value " << temp->value->value
                 << " was deleted." << endl;
        } else {
            // update head reference to 'delete' head node
            head = head->next;
            cout << "Success.  Head node '" << temp->value->name << "' with data value " << temp->value->value
                 << " was deleted." << endl;
        }
        delete temp;
        length--;
    }

    void deleteAtTail() {
        if (length == 0) {
//            cout << "The list is empty, nothing can be deleted." << endl;
            return;
        }
        // if the list is not empty, create temporary pointer to node that is to be deleted
        Node<T> *temp = tail;
        if (length == 1) {
            head = nullptr;
            tail = nullptr;
//            cout << "Success.  Tail node '" << temp->value->name << "' with data value " << temp->value->value
//                 << " was deleted." << endl;
        } else {
            // update tail pointer to 'delete' tail node
            tail = temp->prev;
            // set the tail's next pointer to nullptr, ending the list
            tail->next = nullptr;
//            cout << "Success.  Tail node '" << temp->value->name << "' with data value " << temp->value->value
//                 << " was deleted." << endl;
        }
        length--;
        delete temp;
    }

    void deleteAtIndex(int index) {
        // check if index is within the bounds of the list
        if (index < 0 || index >= length) {
//            cout << "Index is outside the bounds of the list." << endl;
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
            // update nodeToDelete's previous and next pointers, deleting the node at index
            nodeToDelete->prev->next = nodeToDelete->next;
            nodeToDelete->next->prev = nodeToDelete->prev;
//            cout << "Success.  Node '" << nodeToDelete->value->name << "' with data value " << nodeToDelete->value->value << " was deleted.";
        }
        length--;
        delete nodeToDelete;
    }

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

        // if firstNode is not head node, make its next pointer point to the second node
        if (firstNodePrev != nullptr) {
            firstNodePrev->next = secondNode;
        // if firstNode is head node, make the head point to the second node
        } else {
            head = secondNode;
        }

        // if secondNode is not the tail, make its previous pointer point to the first node
        if (secondNodeNext != nullptr) {
            secondNodeNext->prev = firstNode;
        // if secondNode is the tail, make the tail point to the first node
        } else {
            tail = firstNode;
        }

        // swap firstNode and secondNode
        firstNode->next = secondNode->next;
        secondNode->prev = firstNode->prev;
        firstNode->prev = secondNode;
        secondNode->next = firstNode;
    }

    void sortList() {
        // using bubble sort algorithm, O(n^2)
        for (int i = 0; i < length; ++i) {
            Node<T> *currentNode = head;
            Node<T> *nextNode = currentNode->next;

            // this loop runs for the unsorted part of the list,
            // aka the remaining number of iterations of the first loop
            for (int j = 0; j < length - i - 1; ++j) {
                if (currentNode->value->value > nextNode->value->value) {
                    swapNodes(currentNode, nextNode);
                } else {
                    currentNode = nextNode;
                }
                nextNode = currentNode->next;
            }
        }

    }

    void removeMultiples() {
        // set the key to the head of the list
        Node<T> *key = head;
        // node to traverse the list
        Node<T> *current;
        // temporary node to keep track of pointer after node to be deleted so deleteAtIndex can be used
        Node<T> *nextCurrent;
        // node to hold the position of the next key in case a multiple is found and deleteAtIndex is called
        Node<T> *nextKey;
        // keep track of the index of the key
        int keyIndex = 0;
        // keep track of the index of the current node
        int currentIndex;
        // keep track of multiples found
        int multipleCount;

        while (key != nullptr) {
            // this includes the key in the multiple count
            multipleCount = 1;
            // set current node to the node after the key
            current = key->next;
            // keep track of the index of the current node
            currentIndex = keyIndex + 1;

            while (current != nullptr) {
                if (key->value->value == current->value->value) {
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
                // if a multiple was not found, the key index will need to be incremented
                ++keyIndex;
            }
            // after checking all the nodes for a multiple of key, move to the next node and repeat
            key = nextKey;
        }

//        // make the head node the first multipleKey to check against other nodes
//        Node<T> *Key = head;
//        int multipleCount = 0;
//
//        // iterate multipleKey over entire list
//        while (Key != nullptr) {
//
//            // start each multipleKey/current comparison with the node after multipleKey
//            Node<T> *current = Key->next;
//
//            // iterate current over all nodes in list (except for the multipleKey node)
//            while (current != nullptr) {
//
//                // check if the values match
//                if (Key->value->value == current->value->value) {
//                    ++multipleCount;
//
//                    // if the values match, create a temp pointer for the node to be deleted from list
//                    // this ensures the node to be deleted is kept track of, so it can be deleted successfully
//                    Node<T> *temp = current;
//
//                    if (multipleCount > 0) {
//                        // If the current pointer is the tail, it will skip this if statement because the tail does not need its prev pointer moved
//                        // Alternatively, if the current node is not the tail, make the next node point to the previous node
//                        if (current->next != nullptr) {
//                            current->next->prev = current->prev;
//                        }
//
//                        // If the current pointer is the head, it will skip this if statement because the head does not need its next pointer moved
//                        // Alternatively, if the current node is not the head, make the previous node point to the next node
//                        if (current->prev != nullptr) {
//                            current->prev->next = current->next;
//                        }
//                        --length;
//                    }
//                    // move the current pointer to the following node for the next comparison
//                    current = current->next;
//
//                    // Delete the node that had matching data
//                    delete temp;
//
//                    // If the comparison did not find a match, move the current pointer to the following node for the next comparison
//                } else {
//                    current = current->next;
//                }
//            }
//            // After comparing each current node to Key, move Key to the next node for the next round of comparisons
//            Key = Key->next;
//
//            // if a multiple of key was found, delete key, which will always be the head node
//            if (multipleCount > 0) {
//                deleteAtHead();
//                multipleCount = 0;
//            }
//
//        }
    }

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

//    bool compareData(Data *userVal, Data *nodeData) {
//
//
//
//        return true;
//    }

    int countMultiples(T *value) {
        Node<T> *current = head;
        Data *userVal = value;
//        int userVal = value->value;
        int count = 0;

        while (current != nullptr) {

//            if (compareData(userVal, current->value)) {
//
//            }


            if (current->value->value == userVal->value) {
                ++count;
            }
            current = current->next;
        }
        return count;
    }

    void evenOddSplit() {
        DoubleLinkedList<T> evenList;
        DoubleLinkedList<T> oddList;
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
                evenList.append(current->value);
                ++index;

                // if index is odd, add to oddList
            } else {
                oddList.append(current->value);
                ++index;
            }
            // move current to next node
            current = current->next;
            delete temp;
        }
        evenList.printList();
        oddList.printList();

        // deleting the original list must happen in the main function, but list resources can be reset here
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    void reverseList() {
        Node<T> *current = head;
        Node<T> *temp = nullptr;
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

// Main Program

int main() {
    string input;
    int userChoice = 0;
    DoubleLinkedList<Data> *ll1;


    cout << "Hello!  Welcome to the Doubly-Linked List Program!" << endl;
    cout << "To start, enter any letter.  To quit at any time, enter the letter 'q'." << endl;
    cin >> input;

    if (input != "q") {
        cout << "This is the Main Menu:" << endl;
    } else {
        cout << "Goodbye!" << endl;
    }
    while (input != "q") {
        // main menu

        cout << "Choose any of the options by entering the number next to it: " << endl;
        cout << "1: Create new list." << endl;
        cout << "2: Delete a list" << endl;
        cout << "3: Insert a new entry at the beginning of the list." << endl;
        cout << "4: Insert a new entry at the end of the list." << endl;
        cout << "5: Insert a new entry at the index you provide." << endl;
        cout << "6: Delete entry at beginning of list." << endl;
        cout << "7: Delete entry at end of list." << endl;
        cout << "8: Delete entry at the index you provide." << endl;
        cout << "9: Reverse the list." << endl;
        cout << "10: Sort the list in ascending order." << endl;
        cout << "11: Count the number of entries that match a number you provide." << endl;
        cout << "12: Delete entries that have matching data." << endl;
        cout << "13: Split the list by even and odd indices." << endl;
        cout << "Enter the letter 'q' to quit." << endl;

        cin >> userChoice;

        switch (userChoice) {
            case 1: // Create new list
                ll1->createList();
                break;
            case 2:
                // Delete a list

                ll1->printList();
//                delete ll1;
//                ll1->printList();
//                delete ll1;
                break;
            case 3:
                // insert at head
                break;
            case 4:
                // insert at tail
                break;
            case 5:
                // insert at index
                break;
            case 6:
                // delete at head
                break;
            case 7:
                // delete at tail
                break;
            case 8:
                // delete at index
                break;
            case 9:
                // reverse list
                break;
            case 10:
                // sort list
                break;
            case 11:
                // count multiples, need to create a data object with user input to pass to function
                break;
            case 12:
                // delete multiples
                break;
            case 13:
                // split list
                break;

        }


//        cin >> input;
//        if (input != "q") {
//            cout << "Main Menu:" << endl;
//        } else {
//            cout << "Goodbye!" << endl;
//        }

    }
    



        // creating data object
//    Data *d1 = new Data(10, "a");
//    Data *d2 = new Data(20, "b");
//    Data *d3 = new Data(10, "c");
//    Data *d4 = new Data(40, "d");
//    Data *d5 = new Data(50, "e");
//    Data *d6 = new Data(20, "f");
//    Data *d7 = new Data(50, "g");
//    Data *d8 = new Data(10, "h");
//
//    Data *d9 = new Data(11, "h");
//    Data *d10 = new Data(12, "h");
//    Data *d11 = new Data(1, "h");
//    Data *d12 = new Data(1, "h");
//    Data *d13 = new Data(15, "h");
//    Data *d14 = new Data(10, "h");


    // Creating Linked List
//    DoubleLinkedList<Data> *ll1 = new DoubleLinkedList<Data>(d1);
//    ll1->append(d2);
//    ll1->append(d3);
//    ll1->append(d4);
//    ll1->append(d5);
//    ll1->append(d6);
//    ll1->append(d7);
//    ll1->append(d8);
//
//    ll1->append(d9);
//    ll1->append(d10);
//    ll1->append(d11);
//    ll1->append(d12);
//    ll1->append(d13);
//    ll1->append(d14);
//
//    ll1->printList();

    // testing evenOddSplit
//    ll1->evenOddSplit();



    // testing list creation
//    DoubleLinkedList<Data> ll1;
//    ll1.append(d1);
//    ll1->append(d2);
//    ll1->append(d3);
//    ll1->append(d4);
//    ll1.printList();


    // testing reverseList
//    ll1->reverseList();
//    ll1->printList();
//    ll1->getHead();
//    ll1->getTail();

    // testing removeDuplicates
//    ll1->removeDuplicates();
//    ll1->printList();

    // testing removeMultiples
//    ll1->removeMultiples();
//    ll1->printList();

    // testing removeMultiplesUsingIndex
//    ll1->removeMultiplesUsingIndex();
//    ll1->printList();

    // testing countMultiples
//    int multipleCount = ll1->countMultiples(d6);
//    cout << "Number of multiples found in list: " << multipleCount << endl;

    // testing sortList
//    ll1->sortList();
//    ll1->printList();

//     testing deleteAtIndex
//    ll1->deleteAtIndex(0);
//    ll1->printList();




    // Calling operations on Linked List
//    ll1->deleteAtTail(ll1);
//    cout << endl;
//    ll1->printList();
//    ll1->deleteAtTail(ll1);
//    ll1->printList();



    return 0;
}