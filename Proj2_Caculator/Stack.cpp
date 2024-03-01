#include"Stack.h"
using namespace std;

template <typename T>
Stack<T>::Stack(){
	head = new Node<T>();
}

template <typename T>
Stack<T>::~Stack(){
	while(!empty() ){
		pop();
	}
}

template <typename T>
void Stack<T>::push(const T& data){
	Node<T>* tmp = head;
	head = new Node<T>(data, tmp);
}

template <typename T>
T Stack<T>::top(){
	return head->data;
}

template <typename T>
void Stack<T>::disp(){
	Node<T>* tmp = head;
	while(tmp->next != nullptr){
		cout << tmp->data << ' ';
		tmp = tmp->next;
	}
	cout << endl;
}

template <typename T>
bool Stack<T>::pop(){
	if(empty() )
		return false;
	Node<T> *tmp = head;
	head = head->next;
	delete tmp;
	return true;
}

template <typename T>
bool Stack<T>::empty(){
	if(head->next == nullptr)
		return true;
	return false;
}
