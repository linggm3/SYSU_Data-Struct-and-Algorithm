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
		flag = true;  //是否输出多项式结果 
		if(operation == "quit"){
			break;
		}
		else if(operation == "input1"){
			p1.input();  //输入多项式1 
			p1.display();
			flag = false;
		}
		else if(operation == "input2"){
			p2.input();  //输入多项式2
			p2.display();
			flag = false;
		}
		else if(operation == "add")
			res = add_sub(p1, p2, 1);  //加法 
		else if(operation == "sub")
			res = add_sub(p1, p2, -1);  //减法
		else if(operation == "mul")
			res = mul(p1, p2);  //乘法
		else if(operation == "der1")
			res = p1.der();  //求导 
		else if(operation == "der2")
			res = p2.der();  //求导
		else if(operation == "cal1"){
//			cout << "请输入x" << endl; 
			cin >> x;  //计算多项式在x的值 
			cout << p1.caculate(x) << endl; 
			flag = false;
		}
		else if(operation == "cal2"){
//			cout << "请输入x" << endl;
			cin >> x;  //计算多项式在x的值 
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
	cout << "请输入要执行的操作，输入quit退出" << endl;
	cout << "input1输入第一个多项式，input2输入第二个" << endl; 
	cout << "先输入系数再输入指数，系数部分输入0则结束输入" << endl; 
	cout << "disp1输出第一个多项式，disp2输出第二个" << endl; 
	cout << "add将两个多项式相加" << endl;
	cout << "sub将两个多项式相减" << endl;
	cout << "mul将两个多项式相乘" << endl;
	cout << "der1对第一个多项式求导，der2对第二个求导" << endl;
	cout << "cal1计算第一个多项式在x处的值，cal2算第二个" << endl;
	cout << "load1将结果保存到p1中，load2保存到第二个" << endl << endl;
	return true;
}

