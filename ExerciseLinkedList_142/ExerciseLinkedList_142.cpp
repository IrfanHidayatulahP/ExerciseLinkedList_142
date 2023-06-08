#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;
public:
    CircularLinkedList() {
        LAST = NULL;
    }
    void addNode();
    bool search(int rollno, Node** Putra, Node** Irfan);
    bool listEmpty();
    bool delNode(int rollno);
    void traverse();
};

void CircularLinkedList::addNode() {
    string nm;
    cout << "\nEnter the name of the Student: ";
    cin >> nm;
    Node* newNode = new Node();
    newNode->name = nm;

    /*Insert a node in the beginning of the list*/
    if (LAST == NULL || nm <= LAST->name) {
        if (LAST != NULL && nm == LAST->name) {
            cout << "\nDuplicate Name not Allowed" << endl;
            return;
        }
        newNode->next = LAST;
        if (LAST != NULL)
            LAST->next = NULL;
        newNode->next = NULL;
        LAST = newNode;
        return;
    }
    
    /*Insert a Node Between Two Nodes in the List*/
    Node* Irfan = LAST;
    Node* Putra = NULL;
    while (Irfan->next != NULL && Irfan->next->name < nm) {
        Putra = Irfan;
        Irfan = Irfan->next;
    }

    if (Irfan->next != NULL && nm == Irfan->next->name) {
        cout << "\n Duplicate Name is not Allowed" << endl;
        return;
    }
    
    newNode->next = Irfan->next;
    if (Irfan->next != NULL)
        Irfan->next = newNode;
}

bool CircularLinkedList::search(int rollno, Node** Putra, Node** Irfan) {
    *Putra = LAST->next;
    *Irfan = LAST->next;

    while (*Irfan != LAST) {
        if (rollno == (*Irfan)->rollNumber) {
            return true;
        }

        if (rollno == LAST->rollNumber) {
            return true;
        }
        else {
            return false;
        }
    }
}
    
bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode(int rollno) {
    Node* Putra, * Irfan;
    Putra = Irfan = NULL;
    if (search(rollno, &Putra, &Irfan) == false)
    return false;
    if (Irfan->next != NULL)
        Irfan->next = Putra;
    if (Putra != NULL)
        Putra->next = Irfan->next;
    else
        LAST = Irfan->next;
    delete Irfan;
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList Empty\n";
    }
    else {
        cout << "\nRecord in the list are: \n";
        Node* IrfanNode = LAST->next;
        while (IrfanNode != LAST) {
            cout << IrfanNode->rollNumber << " " << IrfanNode->name << endl;
            IrfanNode = IrfanNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;
    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "\n1. Add a record to the List" << endl;
            cout << "\n2. Delete Record from the List" << endl;
            cout << "\n3. View all the record in the List" << endl;
            cout << "\n4. Exit " << endl;
            cout << "\nEnter your Choice (1-5): ";

            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                if (obj.listEmpty()) {
                    cout << "\nList is Empty" << endl;
                    break;
                }
                cout << "\nEnter the name of the student whose record is to be deleted: ";
                int rollno;
                cin >> rollno;
                cout << endl;
                if (obj.delNode(rollno) == false)
                    cout << "Record Not Found" << endl;
                else
                    cout << "Record with Name" << rollno << "Deleted" << endl;
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid Option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
   