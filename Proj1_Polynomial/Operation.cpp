#include"Polynomial.h"
using namespace std;

bool show_list();

int main()
{
	string operation;
	Polynomial p1, p2, res;
	double x;  bool flag = true;
	show_list();
	while(cin >> operation){
		flag = true;  //�Ƿ��������ʽ��� 
		if(operation == "quit"){
			break;
		}
		else if(operation == "input1"){
			p1.input();  //�������ʽ1 
			p1.display();
			flag = false;
		}
		else if(operation == "input2"){
			p2.input();  //�������ʽ2
			p2.display();
			flag = false;
		}
		else if(operation == "add")
			res = add_sub(p1, p2, 1);  //�ӷ� 
		else if(operation == "sub")
			res = add_sub(p1, p2, -1);  //����
		else if(operation == "mul")
			res = mul(p1, p2);  //�˷�
		else if(operation == "der1")
			res = p1.der();  //�� 
		else if(operation == "der2")
			res = p2.der();  //��
		else if(operation == "cal1"){
//			cout << "������x" << endl; 
			cin >> x;  //�������ʽ��x��ֵ 
			cout << p1.caculate(x) << endl; 
			flag = false;
		}
		else if(operation == "cal2"){
//			cout << "������x" << endl;
			cin >> x;  //�������ʽ��x��ֵ 
			cout << p2.caculate(x) << endl;
			flag = false; 
		}
		else if(operation == "disp1"){
			p1.display();
			flag = false;
		}
		else if(operation == "disp2"){
			p2.display();
			flag = false;
		}
		else if(operation == "load1"){
			p1 = res;
		}
		else if(operation == "load2"){
			p2 = res;
		}
		else
			cout << "Invaild Operation" << endl;
		if(flag){
			res.display();
		}
		cout << endl;
	}
	
	return 0; 
}

bool show_list(){
	cout << "������Ҫִ�еĲ���������quit�˳�" << endl;
	cout << "input1�����һ������ʽ��input2����ڶ���" << endl; 
	cout << "������ϵ��������ָ����ϵ����������0���������" << endl; 
	cout << "disp1�����һ������ʽ��disp2����ڶ���" << endl; 
	cout << "add����������ʽ���" << endl;
	cout << "sub����������ʽ���" << endl;
	cout << "mul����������ʽ���" << endl;
	cout << "der1�Ե�һ������ʽ�󵼣�der2�Եڶ�����" << endl;
	cout << "cal1�����һ������ʽ��x����ֵ��cal2��ڶ���" << endl;
	cout << "load1��������浽p1�У�load2���浽�ڶ���" << endl << endl;
	return true;
}

