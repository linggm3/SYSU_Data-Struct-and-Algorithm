#include<bits/stdc++.h>
#include"Stack.h"
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
using namespace std;

void sett(int compare[][8]);

int main()
{
	int compare[8][8] = {0};
	sett(compare);
	string s;
	string ope = "+-*/()#^";
	stack<double> num_stack;
	stack<char> op_stack;
	bool digit_flag = false, point_flag = false;
	int flag, flag_1; 
	double tmp;
	
	while(cin >> s){
		op_stack.push('#');
		for(int i = 0; i < s.size(); i++){
			if(isdigit(s[i])){
				if(digit_flag && !point_flag){
					tmp = num_stack.top();
					num_stack.pop();
					tmp *= 10;
					tmp += s[i] - '0';
					num_stack.push(tmp);
				}
				else if(digit_flag && point_flag){
					tmp = num_stack.top();
					num_stack.pop();
					tmp += (s[i]-'0') * pow(10, -flag);
					flag++;
					num_stack.push(tmp);
				}
				else{
					num_stack.push(s[i] - '0');
				}
				digit_flag = true;
			}
			else if(s[i] == '.'){
				point_flag = true;
				digit_flag = true;
				flag = 1;
			}
			else{
				digit_flag = false;
				point_flag = false;
				flag = ope.find(s[i]);
				if(flag >= 0 && flag < 8){
					label: flag_1 = ope.find(op_stack.top() );
//					cout << flag_1 << ' ' << flag << ' ' << compare[flag_1][flag] << endl;
					if(compare[flag_1][flag] == 0){
						cout << "operater_stack pop " << op_stack.top() << endl;
						op_stack.pop();
					}
					else if(compare[flag_1][flag] == -1){
						op_stack.push(s[i]);
						cout << "operater_stack push " << op_stack.top() << endl;
					}
					else if(compare[flag_1][flag] == 1){
						tmp = num_stack.top();
						num_stack.pop();
						cout << "number_stack pop " << tmp << endl;
						cout << "number_stack pop " << num_stack.top() << endl;
						cout << "operater_stack pop " << op_stack.top() << endl;
						if(op_stack.top() == '+'){
							tmp += num_stack.top();
							num_stack.pop();
							num_stack.push(tmp);
						}
						else if(op_stack.top() == '-'){
							tmp = num_stack.top() - tmp;
							num_stack.pop();
							num_stack.push(tmp);
						}
						else if(op_stack.top() == '*'){
							tmp *= num_stack.top();
							num_stack.pop();
							num_stack.push(tmp);
						}
						else if(op_stack.top() == '/'){
							if(tmp == 0){
								cout << "Invaild devision" << endl;
								break;
							}
							tmp = num_stack.top() / tmp;
							num_stack.pop();
							num_stack.push(tmp);
						}
						else if(op_stack.top() == '^'){
							tmp = pow(num_stack.top(), tmp);
							num_stack.pop();
							num_stack.push(tmp);
						}
						cout << "number_stack push " << num_stack.top() << endl;
						op_stack.pop();
						goto label;
					}
//					else{
//						cout << "Invaild Input" << endl;
//					}
				}
//				else{
//					cout << "Invaild Input" << endl;
//				}
			}
		}
		if(!num_stack.empty() && op_stack.empty()){
			cout << num_stack.top() << endl;
		}
		else{
			cout << "Invaild Input" << endl;
		}
		while(!num_stack.empty()){
			num_stack.pop();
		}
		while(!op_stack.empty()){
			op_stack.pop();
		}
		cout << endl;
	}
}

void sett(int compare[][8]){
	compare[0][0] = 1;
	compare[0][1] = 1;
	compare[0][2] = -1;
	compare[0][3] = -1;
	compare[0][4] = -1;
	compare[0][5] = 1;
	compare[0][6] = 1;
	compare[0][7] = -1;
	
	compare[1][0] = 1;
	compare[1][1] = 1;
	compare[1][2] = -1;
	compare[1][3] = -1;
	compare[1][4] = -1;
	compare[1][5] = 1;
	compare[1][6] = 1;
	compare[1][7] = -1;
	
	compare[2][0] = 1;
	compare[2][1] = 1;
	compare[2][2] = 1;
	compare[2][3] = 1;
	compare[2][4] = -1;
	compare[2][5] = 1;
	compare[2][6] = 1;
	compare[2][7] = -1;
	
	compare[3][0] = 1;
	compare[3][1] = 1;
	compare[3][2] = 1;
	compare[3][3] = 1;
	compare[3][4] = -1;
	compare[3][5] = 1;
	compare[3][6] = 1;
	compare[3][7] = -1;
	
	compare[4][0] = -1;
	compare[4][1] = -1;
	compare[4][2] = -1;
	compare[4][3] = -1;
	compare[4][4] = -1;
	compare[4][5] = 0;
	compare[4][6] = -999;
	compare[4][7] = -1;
	
	compare[5][0] = 1;
	compare[5][1] = 1;
	compare[5][2] = 1;
	compare[5][3] = 1;
	compare[5][4] = -999;
	compare[5][5] = 1;
	compare[5][6] = 1;
	compare[5][7] = 1;
	
	compare[6][0] = -1;
	compare[6][1] = -1;
	compare[6][2] = -1;
	compare[6][3] = -1;
	compare[6][4] = -1;
	compare[6][5] = -999;
	compare[6][6] = 0;
	compare[6][7] = -1;
	
	compare[7][0] = 1;
	compare[7][1] = 1;
	compare[7][2] = 1;
	compare[7][3] = 1;
	compare[7][4] = -1;
	compare[7][5] = 1;
	compare[7][6] = 1;
	compare[7][7] = 1;
}
