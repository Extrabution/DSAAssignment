#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

template<typename T> class ISortedList{
public:
    virtual T least() = 0;
    virtual T greatest() = 0;
    virtual T sort() = 0;
    virtual T get(int index) = 0;
    virtual int indexOf(T item) = 0;
    virtual void remove(int i) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;
    virtual ISortedList<T> searchRange(T from, T to) = 0;
};


template<typename T> class Node{
public:
    Node* next;
    Node* previous;
    T value;
};

Node<string>* pNameNode;
Node<string>* PNameLeast;
Node<string>* PNameGreatest;

template<typename T> class SortedList : ISortedList<T>{
private:
    Node<T>* pLeast = NULL;
    Node<T>* pGreatest = NULL;
    int sizeDLL = 0;
public:
    SortedList() = default;;

    void add(T tempValue){
        Node<T> *tempP = new Node<T>();
        tempP->value = tempValue;
        if(sizeDLL!=0){
            tempP->next = NULL;
            tempP->previous = pGreatest;
            pGreatest->next = tempP;
            pGreatest = tempP;
            sizeDLL++;
        }
        else{
            pGreatest = tempP;
            pLeast = tempP;
            tempP->next = NULL;
            tempP->previous =NULL;
            sizeDLL++;
        }
    }

    void remove(int i) override {
        Node<T>* tempP = pLeast;
        Node<string>* tempPString = pNameNode;
        for(int j = 0; j < i; j++) {
            tempP = tempP->next;
            tempPString = tempPString->next;
        }
        if(tempP->next == NULL){          // Придумать как получить доступ к плист и п греатест для класса содержащего стринг, чтобы сэкономиь время и срауз в двух листах удалять элементы
            if(tempP->previous == NULL){
                pLeast = NULL;
                pGreatest = NULL;
            }
            else{
                pGreatest = tempP->previous;
                tempP->previous->next = NULL;
            }
        }
        else if(tempP->previous == NULL){
            pLeast = tempP->next;
            tempP->next->previous = NULL;
        }
        else{
            tempP->next->previous = tempP->previous;
            tempP->previous->next = tempP->next;
        }
        delete tempP;
        delete tempPString;
    }
    void insert(T newValue, int index){
        Node<T>* tempPNew = new Node<T>();
        Node<T>* tempP = pLeast;
        tempPNew->value = newValue;
        for(int i = 0; i < index; i++){
            tempP = tempP->next;
        }
        tempP->next->previous = tempPNew;
        tempPNew->next = tempP->next;
        tempPNew->previous = tempP;
        tempP->next = tempPNew;
    }

    T least() override {return pLeast->value;}

    T greatest() override {return pGreatest->value;}

    T get(int index) override {   // можно сэкономить вемя проверяя в какой половине
        Node<T>* tempP = pLeast;  // находится индекс от размера и идти от конца
        for(int i = 0; i < index; i++){
            tempP = tempP->next;
        }
        return tempP->value;
    }

    T sort() override {}

    int indexOf(T item) override {
        Node<T>* tempP = pLeast;
        for(int i = 0; i < sizeDLL; i++){
            if(tempP->value == item){return i;}
            else{tempP = tempP->next;}
        }
    }

    int size() override {return sizeDLL;}

    bool isEmpty() override {
        if(sizeDLL == 0){return true;}
        else{return false;}
    }

    ISortedList<T> searchRange(T from, T to) override {}

    Node<string>* stringPLeast(){
        return pLeast;
    }
    Node<string>* stringPGreatest(){
        return pGreatest;
    }
};


int main() {
    SortedList<float> prices;
    SortedList<string> names;
    pNameNode = names.stringPLeast();
    return 0;
}
