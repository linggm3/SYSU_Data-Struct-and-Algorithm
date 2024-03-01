#include<iostream>
#include<graphics.h>
#include<easyx.h>
#include<conio.h>
#include<string>
#include<stack>
#include<vector>
#include<cmath>
#include<map>
using namespace std;
#define ENTER 0x0D
#define DELETe 8

vector<char> v1;
vector<double> v2;

class Expression{
	private:
		string expr;
		map<char, double> val;
	public:
		Expression(){
			expr = "";
		}
		
		Expression(string expr){
			this->expr = expr;
		}
		
		void ReadExpr(string s){
			expr = s;
		}
		
		string WriteExpr(){
			string MidOrder = expr;
			string str1, str2;
			double tmp;
			stack<double> num_sta;
			stack<string> str_sta;
			bool digit_flag = false;
			int weishu = 1;
			for(int i = expr.size()-1; i >= 0; i--){
				if(isalpha(expr[i]) ){
					if(digit_flag){
						tmp = num_sta.top();
						num_sta.pop();
						str_sta.push(to_string(tmp) );
					}
					digit_flag = false;
					str_sta.push(string(1, expr[i]) );
				}
				else if(expr[i] == ' '){
					if(digit_flag){
						tmp = num_sta.top();
						num_sta.pop();
						str_sta.push(to_string(tmp) );
					}
					digit_flag = false;
					weishu = 1;
				}
				else if(expr[i] == '.'){
					digit_flag = true;
					tmp = num_sta.top();
					num_sta.pop();
					tmp *= pow(10, -weishu);
					num_sta.push(tmp);
					weishu = 0;
				}
				else if(isdigit(expr[i]) ){
					if(!digit_flag)
						num_sta.push(expr[i] - '0');
					else{
						tmp = num_sta.top();
						num_sta.pop();
						tmp += (int)pow(10, weishu++) * (expr[i] - '0');
						num_sta.push(tmp);
					}
					cout << num_sta.top() << endl;
					digit_flag = true;
				}
				else{
					if(digit_flag){
						tmp = num_sta.top();
						num_sta.pop();
						str_sta.push(to_string(tmp) );
					}
					digit_flag = false;
					weishu = 1;
					if(str_sta.empty() )
						return "";
					str1 = str_sta.top();
					str_sta.pop();
					if(str_sta.empty() )
						return "";
					str2 = str_sta.top();
					str_sta.pop();
					if(expr[i] == '+'){
						str_sta.push(string("(") + str1 + string("+") + str2 + (")") );
					}
					else if(expr[i] == '-'){
						str_sta.push(string("(") + str1 + string("-") + str2 + (")") );
					}
					else if(expr[i] == '*'){
						str_sta.push(string("(") + str1 + string("*") + str2 + (")") );
					}
					else if(expr[i] == '/'){
						str_sta.push(string("(") + str1 + string("/") + str2 + (")") );
					}
					else if(expr[i] == '^'){
						str_sta.push(string("(") + str1 + string("^") + str2 + (")") );
					}
				}
			}
			return str_sta.top();
		}
		
		void Assign(char c, double value){
			val[c] = value;
			map<char, double>::iterator iter = val.begin();
			while(iter != val.end() ){
				v1.push_back(iter->first);
				v2.push_back(iter->second);
				cout << iter->first << ' ' << iter->second << endl;
				iter++;
			}
			cout << endl;
		}
		
		double value(){
			double num1, num2, tmp;
			stack<double> num_sta;
			bool digit_flag = false;
			int weishu = 1;
			for(int i = expr.size()-1; i >= 0; i--){
				if(isalpha(expr[i]) ){
					num_sta.push(val[expr[i]] );
				}
				else if(expr[i] == ' '){
					digit_flag = false;
					weishu = 1;
				}
				else if(expr[i] == '.'){
					digit_flag = true;
					tmp = num_sta.top();
					num_sta.pop();
					tmp *= pow(10, -weishu);
					num_sta.push(tmp);
					weishu = 0;
				}
				else if(isdigit(expr[i]) ){
					if(!digit_flag)
						num_sta.push(expr[i] - '0');
					else{
						tmp = num_sta.top();
						num_sta.pop();
						tmp += (int)pow(10, weishu++) * (expr[i] - '0');
						num_sta.push(tmp);
					}
					cout << num_sta.top() << endl;
					digit_flag = true;
				}
				else{
					digit_flag = false;
					weishu = 1;
					if(num_sta.empty() )
						return -99999;
					num1 = num_sta.top();
					num_sta.pop();
					if(num_sta.empty() )
						return -99999;
					num2 = num_sta.top();
					num_sta.pop();
					if(expr[i] == '+'){
						num_sta.push(num1 + num2);
					}
					else if(expr[i] == '-'){
						num_sta.push(num1 - num2);
					}
					else if(expr[i] == '*'){
						num_sta.push(num1 * num2);
					}
					else if(expr[i] == '/'){
						num_sta.push(num1 / num2);
					}
					else if(expr[i] == '^'){
						num_sta.push(pow(num1, num2) );
					}
				}
			}
			return num_sta.top();
		}
		
		void CompoundExpr(Expression E, char op){
			this->expr = op + this->expr + ' ' + E.expr;
		}
		
		Expression Diff(char c){
			return *this;
		}
};

int main(){
	initgraph(1015, 600);
	// 设置背景颜色 
	COLORREF WH = RGB(235, 229, 209);
	setbkcolor(WH);
	// 用背景颜色清空屏幕 
	cleardevice();
	// 设置文字颜色
	settextcolor(BLACK);
	// 设置字体形式（高度，宽度，字体）
	settextstyle(32, 16, "楷体");
	// 圆的填充颜色函数
	setfillcolor(WHITE); 
	// 边框线条颜色函数
	setlinecolor(WHITE);
	// 边框线条形式函数
	setlinestyle(PS_SOLID, 10);
	setbkmode(TRANSPARENT);
	
	Expression E1, E2;
	int function_select = 1, expr_select = 1; 
	string s1 = "", s2 = "", ans = "";
	while (1)
	{
		cleardevice();//清除上一次绘画的图形防止发生重叠
		for(int i = 0; i < v1.size(); i++){
			outtextxy(50, 65+45*i, v1[i]);
			outtextxy(80, 65+45*i, to_string(v2[i]).c_str() );
		}
		solidrectangle(300, 100, 700, 150);
		outtextxy(430, 65, "表达式一");
		solidrectangle(300, 230, 700, 280);
		outtextxy(430, 195, "表达式二");
		solidrectangle(300, 360, 700, 410);
		outtextxy(430, 325, "运算结果");
		solidrectangle(25, 525, 165, 575);
		outtextxy(65, 535, "输入"); 
		solidrectangle(190, 525, 330, 575);
		outtextxy(230, 535, "输出");
		solidrectangle(355, 525, 495, 575);
		outtextxy(395, 535, "赋值");
		solidrectangle(520, 525, 660, 575);
		outtextxy(560, 535, "求值");
		solidrectangle(685, 525, 825, 575);
		outtextxy(725, 535, "合并");
		solidrectangle(850, 525, 990, 575);
		outtextxy(890, 535, "偏导");
		outtextxy(300, 110, s1.c_str()); 
		outtextxy(300, 240, s2.c_str());
		outtextxy(300, 370, ans.c_str());
		
		
		while(!kbhit() ) //当没有键按下
		{
			ExMessage msg = {0};
			if (peekmessage(&msg, EM_MOUSE));//检测鼠标信息
			{
				switch (msg.message)//筛选鼠标信息类型
				{
				case WM_LBUTTONDOWN://左键信息
					if(msg.y >= 525 && msg.y <= 575){
						if(msg.x >= 25 && msg.x <= 95){
							function_select = 1;
							expr_select = 1;
							cout << function_select << ' ' << expr_select << endl;
						}
						else if(msg.x >= 95 && msg.x <= 165){
							function_select = 1;
							expr_select = 2;
							cout << function_select << ' ' << expr_select << endl;
						}
						else if(msg.x >= 190 && msg.x <= 330){
							function_select = 2;
							cout << function_select << ' ' << expr_select << endl;
						}
						else if(msg.x >= 355 && msg.x <= 495){
							function_select = 3;
							cout << function_select << ' ' << expr_select << endl;
						}
						else if(msg.x >= 520 && msg.x <= 660){
							function_select = 4;
							cout << function_select << ' ' << expr_select << endl;
						}
						else if(msg.x >= 685 && msg.x <= 825){
							function_select = 5;
							cout << function_select << ' ' << expr_select << endl;
						}
						else if(msg.x >= 850 && msg.x <= 990){
							function_select = 6;
							cout << function_select << ' ' << expr_select << endl;
						}
					}
					break;

				default:
					break;
				}
			}
		}
		 
		char input;
		input = _getch();
		if(function_select == 1){
			switch (input)
			{
				case DELETe:
					if(expr_select == 1 && !s1.empty() ){
						s1 = s1.erase(s1.size()-1, 1);
					}
					else if(!s2.empty() ){
						s2 = s2.erase(s2.size()-1, 1);
					}
						
					break;
				default:
					if(expr_select == 1)
						s1 += input;
					else
						s2 += input;
			}
		}
		
		else if(function_select == 2){
			E1.ReadExpr(s1);
			ans = E1.WriteExpr();
		}
		
		else if(function_select == 3){
			v1.clear();
			v2.clear();
			char val1;
			double tmp_val = 0;
			do{
				val1 = _getch();
				if(isalpha(val1) ){
					input = val1;
				}
				else if(isdigit(val1) ){
					tmp_val *= 10;
					tmp_val += val1 - '0';
				}
			} while(val1 != ENTER);
			E1.Assign(input, tmp_val);
//			cout << input << ' ' << tmp_val << endl;
		}
		
		else if(function_select == 4){
			E1.ReadExpr(s1);
			ans = to_string(E1.value() );
		}
		
		else if(function_select == 5){
			E1.ReadExpr(s1);
			E2.ReadExpr(s2);
			E1.CompoundExpr(E2, input);
			ans = E1.WriteExpr();
			function_select = 1;
		}
		
		else if(function_select == 6){
			
		}
	}
	
}
