#include<iostream>
#include<string>
#include<cmath>

struct Node{
	double coef; //系数 
	double expo; //指数
	Node* next; 
	//构造函数 
	Node(): coef(0), expo(99999), next(NULL){}
	Node(double coef, double expo): coef(coef), expo(expo), next(NULL){}
	Node(double coef, double expo, Node* next): coef(coef), expo(expo), next(next){}
};

class Polynomial{
	private:
		Node* head;
	public:
		//构造函数 
		Polynomial();
		Polynomial(const Polynomial& p);
		//析构函数
		~Polynomial();
		//深拷贝赋值
		Polynomial operator = (const Polynomial& p); 
		//清除多项式
		void clear();
		//输入多项式
		void input(); 
		//链表插入元素
		bool insert(double coef, double expo); 
		//输出多项式
		void display(); 
		//多项式项数
		int size() const; 
		
		//加或减操作 
		friend Polynomial add_sub(const Polynomial& a, const Polynomial& b, int mod);
		//乘操作 
		friend Polynomial mul(const Polynomial& a, const Polynomial& b);
		//计算多项式在x处的值 
		double caculate(const double x);
		//多项式求导
		Polynomial der();	
};
