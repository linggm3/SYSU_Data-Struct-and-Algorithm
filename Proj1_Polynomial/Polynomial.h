#include<iostream>
#include<string>
#include<cmath>

struct Node{
	double coef; //ϵ�� 
	double expo; //ָ��
	Node* next; 
	//���캯�� 
	Node(): coef(0), expo(99999), next(NULL){}
	Node(double coef, double expo): coef(coef), expo(expo), next(NULL){}
	Node(double coef, double expo, Node* next): coef(coef), expo(expo), next(next){}
};

class Polynomial{
	private:
		Node* head;
	public:
		//���캯�� 
		Polynomial();
		Polynomial(const Polynomial& p);
		//��������
		~Polynomial();
		//�����ֵ
		Polynomial operator = (const Polynomial& p); 
		//�������ʽ
		void clear();
		//�������ʽ
		void input(); 
		//�������Ԫ��
		bool insert(double coef, double expo); 
		//�������ʽ
		void display(); 
		//����ʽ����
		int size() const; 
		
		//�ӻ������ 
		friend Polynomial add_sub(const Polynomial& a, const Polynomial& b, int mod);
		//�˲��� 
		friend Polynomial mul(const Polynomial& a, const Polynomial& b);
		//�������ʽ��x����ֵ 
		double caculate(const double x);
		//����ʽ��
		Polynomial der();	
};
