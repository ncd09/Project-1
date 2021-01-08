#include <iostream>

using namespace std;
class Product{
public:
    int key;
    string name;
    Product(int key = 0, string name = ""){
        this->key = key;
        this->name = name;
    }
};
class SLL{
public:
    class Node{
    public:
        Product* data;
        Node* next;
        Node(int key = 0, string name = ""){
            data = new Product(key,name);
            next = NULL;
        }
    };
    Node* first;
    Node* last;
    SLL();
    SLL(int key, string name);
    SLL(Node* first);
    void init(int key, string name);
    Node* createNode(int key, string name);
    bool checkNode(Node* node);
    void insertAtBegin(int key, string name);
    void insertAtEnd(int key, string name);
    void insertAtMiddle(int key, string name, int pos);
    void removeFirst();
    void removeLast();
    void removeMiddle(int pos);
    Node* searchNode(int key);
    void searchSpecial(int crite);
    void print();
    void pswap(Node* a, Node* b, Node* preva, Node* prevb);
    void selectionSort();
    Node* getTail(Node* cur);
    Node* part(Node* first, Node* last, Node** nfirst, Node** nlast);
    Node* recur(Node* first, Node* last);
    void quickSort();
    void removeSpecial(int crite);
    Node* mergeList(Node* first1, Node* first2);
    Node* splitList(int pos);
};
SLL::SLL(){
    first = NULL;
    last = NULL;
}
SLL::SLL(int key, string name){
    Node* node = new Node(key,name);
    first = node;
    last = node;
}
SLL::SLL(Node* first){
    this->first = first;
    this->last = first;
}
void SLL::init(int key, string name){
    Node* node = new Node(key,name);
    first = node;
    last = node;

}
typename SLL::Node* SLL::createNode(int key, string name){
    Node* node = new Node(key,name);
    return node;
}
bool SLL::checkNode(Node* node){
    if(node->data->name.empty())
        return false;
    return true;
}
void SLL::insertAtBegin(int key, string name){
    Node* node = createNode(key,name);
    if(first != NULL){
        node->next = first;
        first = node;
    }
    else{
        first = last = node;
    }
}
void SLL::insertAtEnd(int key, string name){
    Node* node = createNode(key,name);
    if(last != NULL){
        last->next = node;
        last = last->next;
    }
    else{
        first = last = node;
    }
}
void SLL::insertAtMiddle(int key, string name, int pos){
    Node* node = createNode(key,name);
    Node* curr = first;
    while(pos > 1 && curr != NULL){
        curr = curr->next;
        pos--;
    }
    if(pos == 1){
        node->next = curr->next;
        curr->next = node;
    }

}
void SLL::removeFirst(){
    if(first == last){
        delete(first);
    }else{
        Node* temp = first;
        first = temp->next;
        delete(temp);
    }
}
void SLL::removeLast(){
    if(first == last){
        delete(last);
    }else{
        Node* temp = first;
        while(temp->next != last){
            temp = temp->next;
        }
        delete(last);
        last = temp;
        last->next = NULL;

    }
}
void SLL::removeMiddle(int pos){
    Node* curr = first;
    while(pos > 1 && curr != NULL){
        curr = curr->next;
        pos--;
    }
    if(pos == 1){
        Node* temp = curr->next;
        curr->next = temp->next;
        delete(temp);
    }
}
typename SLL::Node* SLL::searchNode(int key){
    Node* curr = first;
    while(curr != NULL){
        if(curr->data->key == key)
            return curr;
        else
            curr = curr->next;
    }
    return NULL;
}
void SLL::searchSpecial(int crite){//search nodes having key < crite
    Node* curr = first;
    while(curr != NULL){
        if(curr->data->key < crite)
            cout << curr->data->key << " " << curr->data->name << endl;
        curr = curr->next;
    }
    cout << "Success\n" << endl;
}
void SLL::print(){
    Node* curr = first;
    while(curr != NULL){
        cout << curr->data->key << "  " << curr->data->name << endl;
        curr = curr->next;
    }
}
void SLL::pswap(Node* a, Node* b, Node* preva, Node* prevb){
    if(a != NULL && b != NULL){
        if (preva != NULL)
            preva->next = b;
        if (prevb != NULL)
            prevb->next = a;
        Node* temp = a->next;
        a->next = b->next;
        b->next = temp;
        if (preva == NULL)
            first = b;
        else if (prevb == NULL)
            first = a;
    }
}
typename SLL::Node* SLL::getTail(Node* cur)
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}
typename SLL::Node* SLL::part(Node* first, Node* last, Node** nfirst, Node** nlast){
    Node* pivot = last;
    Node* prev = NULL, *cur = first, *tail = pivot;
    while (cur != pivot)
    {
        if (cur->data->key < pivot->data->key)
        {
            if ((*nfirst) == NULL)
                (*nfirst) = cur;

            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            Node* tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if ((*nfirst) == NULL)
        (*nfirst) = pivot;
    (*nlast) = tail;
    return pivot;
}
typename SLL::Node* SLL::recur(Node* first, Node* last){
    if(first == NULL || first == last)
        return first;
    Node* nfirst = NULL, *nlast = NULL;
    Node* pivot = part(first,last,&nfirst,&nlast);
    if(nfirst != pivot){
        Node* temp = nfirst;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;
        nfirst = recur(nfirst,temp);
        temp = getTail(nfirst);
        temp->next = pivot;
    }
    pivot->next = recur(pivot->next,nlast);
    return nfirst;
}
void SLL::quickSort(){
    first = recur(first,last);
}
void SLL::selectionSort(){
    Node* x = first;
    Node* prevx = NULL;
    while(x != NULL){
        Node* prevmin = prevx;
        Node* pmin = x;
        Node* y = x->next;
        Node* prevy = x;
        while(y != NULL){
            if(y->data->key < pmin->data->key){
                pmin = y;
                prevmin = prevy;
            }
            prevy = y;
            y = y->next;
        }
        pswap(x,pmin,prevx,prevmin);
        prevx = pmin;
        x = pmin->next;
    }
}
void SLL::removeSpecial(int crite){//remove nodes having key < crite
    Node* curr = first;
    while(curr != NULL){
        if(curr->data->key < crite){
            if(curr == first)
                removeFirst();
            else if(curr == last)
                removeLast();
            else{
                Node* temp = first;
                while(temp->next != curr)
                    temp = temp->next;
                temp->next = curr->next;
                delete(curr);
                curr = temp->next;
            }
        }
        curr = curr->next;
    }
    cout << "Success\n" << endl;
}
typename SLL::Node* SLL::mergeList(Node* first1, Node* first2){
    Node* curr = first1;
    if(first1 != NULL && first2 != NULL){
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = first2;
        return first1;
    }else if(first1 == NULL)
        return first2;
    else
        return first1;
}
typename SLL::Node* SLL::splitList(int pos){
    Node* curr = first;
    if(curr != NULL){
        while(pos > 1 && curr->next != NULL){
            curr = curr->next;
            pos--;
        }
        if(pos == 1){
            Node* newList = curr->next;
            curr->next = NULL;
            return newList;
        }
    }
    return NULL;
}
int main()
{
    SLL* a = new SLL();
    a->insertAtBegin(1,"a");
    a->insertAtEnd(2,"b");
    a->insertAtEnd(3,"c");
    a->insertAtBegin(4,"d");
    a->insertAtMiddle(5,"e",2);
    SLL* newList = new SLL(a->splitList(3));
    a->mergeList(a->first,newList->first);
    a->print();
    return 0;
}
