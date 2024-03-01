#include"Polynomial.h"
using namespace std;

Polynomial::Polynomial(){
	head = new Node();
}

Polynomial::Polynomial(const Polynomial& p){
	this->head = new Node(p.head->coef, p.head->expo);
	Node *tmp = p.head;
	Node *tmp2 = this->head;
	while(tmp->next != NULL){
		tmp = tmp->next;
		tmp2->next = new Node(tmp->coef, tmp->expo);
		tmp2 = tmp2->next;
	}
}

Polynomial::~Polynomial(){
	this->clear();
	delete head;
}

Polynomial Polynomial::operator = (const Polynomial& p){
	this->clear();
	Node *tmp = p.head;
	Node *tmp2 = this->head;
	while(tmp->next != NULL){
		tmp = tmp->next;
		tmp2->next = new Node(tmp->coef, tmp->expo);
		tmp2 = tmp2->next;
	}
	return *this;
}

void Polynomial::clear(){
	Node *tmp = head;
	while(head != NULL){
		head = head->next;
		delete tmp;
		tmp = head;
	}
	head = new Node();
}

void Polynomial::input(){
	clear();
	double coef, expo;
	while(cin >> coef){
		if(coef == 0)
			break;
		cin >> expo; 
		insert(coef, expo);
	}
	return;
}

bool Polynomial::insert(double coef, double expo){
	Node *p = head, *q = head->next;
	bool add_or_not = true;
	while(q != NULL){
		if(p->expo > expo && q->expo < expo){
			add_or_not = true;
			break;
		}
		if(q->expo == expo){
			add_or_not = false;
			break;
		}
		q = q->next;
		p = p->next;
	}
	if(add_or_not){
		Node *tmp = new Node(coef, expo, q);
		p->next = tmp;
	}
	else{
		q->coef += coef;
		if(q->coef == 0)
			p->next = q->next;
	}
	return true;
}
 
void Polynomial::display(){
	if(head->next == NULL){
		cout << 0 << endl;
	}
	Node *tmp = head->next;
	char add_sub;
	int time = 1;
	while(tmp != NULL){
		if(tmp->coef == 0)
			tmp = tmp->next;
		if(tmp->coef > 0)
			add_sub = '+';
		else
			add_sub = '-';
		if(time == 1){
			if(tmp->expo == 0)
				cout << tmp->coef << ' ';
			else if(tmp->expo == 1)
				cout << tmp->coef <<  "X ";
			else
				cout << tmp->coef << "X^" << tmp->expo << ' ';
			time++;
		}
		else{
			if(tmp->expo == 0)
				cout << add_sub << ' ' << fabs(tmp->coef) << ' ';
			else if(tmp->expo == 1)
				cout << add_sub << ' ' << fabs(tmp->coef) <<  "X ";
			else
				cout << add_sub << ' ' << fabs(tmp->coef) << "X^" << tmp->expo << ' ';
		}
		tmp = tmp->next;
	}
	cout << endl;
}

int Polynomial::size() const{
	int ans = 0;
	Node *tmp = head;
	while(tmp->next != NULL){
		tmp = tmp->next;
		ans++;
	}
	return ans;
}
 
Polynomial add_sub(const Polynomial& a, const Polynomial& b, int mod){
	Polynomial res;
	Node *tmp = res.head;
	Node *tmp1 = a.head->next;
	Node *tmp2 = b.head->next;	
	while(tmp1 != NULL && tmp2 != NULL){
		if(tmp1->expo == tmp2->expo){
			if(tmp1->coef + mod * tmp2->coef != 0){
			tmp->next = new Node(tmp1->coef + mod * tmp2->coef, tmp1->expo);
			tmp = tmp->next;
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
			}
			else{
				tmp1 = tmp1->next;
				tmp2 = tmp2->next;
			}
		}
		else if(tmp1->expo > tmp2->expo){
			tmp->next = new Node(tmp1->coef, tmp1->expo);
			tmp = tmp->next;
			tmp1 = tmp1->next;
		}
		else if(tmp1->expo < tmp2->expo){
			tmp->next = new Node(mod * tmp2->coef, tmp2->expo);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	while(tmp1 != NULL){
		tmp->next = new Node(tmp1->coef, tmp1->expo);
		tmp = tmp->next;
		tmp1 = tmp1->next;
	}
	while(tmp2 != NULL){
		tmp->next = new Node(mod * tmp2->coef, tmp2->expo);
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	return res;
}
 
Polynomial mul(const Polynomial& a, const Polynomial& b){
	Polynomial res;
	Polynomial *tmp_res = new Polynomial[a.size() ];
	Node *tmp1 = a.head, *tmp2 = b.head, *tmp; 
	for(int i = 0; i < a.size(); i++){
		tmp1 = tmp1->next;
		tmp2 = b.head;
		tmp = tmp_res[i].head;
		for(int j = 0; j < b.size(); j++){
			tmp2 = tmp2->next;		
			tmp->next = new Node(tmp1->coef * tmp2->coef, tmp1->expo + tmp2->expo);
			tmp = tmp->next;
		}
		res = add_sub(res, tmp_res[i], 1);
	}
	return res;
}

double Polynomial::caculate(const double x){
	double ans = 0;
	Node *tmp = head->next;
	while(tmp != NULL){
		ans += tmp->coef * pow(x, tmp->expo);
		tmp = tmp->next;
	}
	return ans;
}

Polynomial Polynomial::der(){
	Polynomial res;
	Node *tmp = head->next;
	Node *tmp2 = res.head;
	while(tmp != NULL){
		if(tmp->expo == 0){
			tmp = tmp->next;
		}
		else{
			tmp2->next = new Node(tmp->coef * tmp->expo, tmp->expo-1);
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	return res;
}
