#include<iostream>
using namespace std;

template <typename T>
struct Node{
	T data;
	Node* next;
	Node(): data(0), next(nullptr){}
	Node(T data): data(data), next(nullptr){}
	Node(T data, Node* next): data(data), next(next){}
};

template <typename T>
class Stack{
	private:
		Node<T>* head;
	public:
		Stack();
		
		~Stack();
		
		void push(const T& data);

		void disp();
		
		T top();
		
		bool pop();
		
		bool empty();
};
