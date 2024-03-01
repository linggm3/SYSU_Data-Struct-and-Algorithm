#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#define INF 0x7FFFFFFF
#define MAX_SIZE 31
using namespace std;

struct Pair{
	// 姓名 
	string key;
	// 数据 
	int data;
	// 状态 0为空 1为满 -1为已删除 
	int status;
};

struct Hash_Table{
	vector<Pair> table;
	
	Hash_Table(){
		table.resize(MAX_SIZE);
		for(int i = 0; i < MAX_SIZE; i++){
			table[i].status = 0;
		}
	}
	
	int hash(string key){
		int addr = 0;
		int offset[] = {0,1,3,7}; 
		for(int i = 0; i < key.size(); i++){
    		addr = (long long)(addr * 11 + key[i]) % MAX_SIZE;
		}
		for (int i = 0; i < sizeof(offset)/sizeof(int); i++) {
			int addr2 = (addr + offset[i]) % MAX_SIZE;
			if(table[addr2].status == 0)
				return addr2;
			if(table[addr2].status == 1 && table[addr2].key == key)
				return addr2;
		}
		return -1;
	}
	
	int hash2(string key){
		int addr = 0;
		int offset[] = {0,1,3,7}; 
		for(int i = 0; i < key.size(); i++){
    		addr = (long long)(addr * 11 + key[i]) % MAX_SIZE;
		}
		for (int i = 0; i < sizeof(offset)/sizeof(int); i++) {
			int addr2 = (addr + offset[i]) % MAX_SIZE;
			if(table[addr2].status == 0 || table[addr2].status == -1)
				return addr2;
			if(table[addr2].status == 1 && table[addr2].key == key)
				return addr2;
		}
		return -1;
	}
	
	bool has(string key){
		int addr = hash(key);
		if(addr == -1) 
			return false;
		if(table[addr].status != 1) 
			return false;
		return table[addr].key == key;
	}
	
	bool insert(string key, int data){
		int addr = hash2(key);
		if(addr == -1)
			return false;
		table[addr].key = key;
		table[addr].data = data;
		table[addr].status = 1;
		return true;
	}
	
	bool deletee(string key){
		if(has(key)){
			int addr = hash(key);
			table[addr].status = -1;
			return true;
		}
		return false;
	}
	
	int find(string key){
		if(has(key))
			return table[hash(key)].data;
		return -1;
	}
	
	void disp(){
		settextcolor(BLACK);
		setfillcolor(WHITE);
		settextstyle(25, 12, "楷体");
		for(int i = 0; i < 15; i++){
			solidrectangle(10+70*i, 50, 50+70*i, 150);
			if(table[i].status == 0)
				outtextxy(15+70*i, 100, "空");
			else if(table[i].status == -1)
				outtextxy(15+70*i, 100, "删");
			else{
				settextstyle(15, 8, "楷体");
				outtextxy(10+70*i, 80, table[i].key.c_str());
				outtextxy(10+70*i, 120, to_string(table[i].data).c_str());
				settextstyle(25, 12, "楷体");
			} 
		}
		for(int i = 15; i < 31; i++){
			solidrectangle(10+70*(i-15), 200, 50+70*(i-15), 300);
			if(table[i].status == 0)
				outtextxy(15+70*(i-15), 250, "空");
			else if(table[i].status == -1)
				outtextxy(15+70*(i-15), 250, "删");
			else{
				settextstyle(15, 8, "楷体");
				outtextxy(10+70*(i-15), 230, table[i].key.c_str());
				outtextxy(10+70*(i-15), 270, to_string(table[i].data).c_str());
				settextstyle(25, 12, "楷体");
			} 
		}
	}
}; 

void show(){
	solidrectangle(400, 350, 800, 400);
	solidrectangle(200, 425, 400, 480);
	solidrectangle(500, 425, 700, 480);
	solidrectangle(800, 425, 1000, 480);
	outtextxy(280, 440, "插入");
	outtextxy(580, 440, "查找");
	outtextxy(880, 440, "删除");
}

string get_name(){
	char c;
	string s;
	while(true){
		outtextxy(450, 360, s.c_str());
		char c = _getch();
		if(c == 8 && s.size() > 0){
			s = s.substr(0, s.size()-1);
		}
		else if(c == 13)
			return s;
		else if(c != 8)
			s += c;
	}
}

int main(){
	initgraph(1120, 500);
	setbkmode(TRANSPARENT);
	// 设置背景颜色 
	COLORREF WH = RGB(235, 229, 209);
	setbkcolor(WH);
	cleardevice();
	int data;
	Hash_Table ht;
	
	while(true){
		ht.disp();
		show();
		setfillcolor(WHITE);
		while(!kbhit()){
			ExMessage msg = {0};
			if (peekmessage(&msg, EM_MOUSE))//检测鼠标信息
			{
				switch (msg.message)//筛选鼠标信息类型
				{
				case WM_LBUTTONDOWN://左键信息
					if(msg.y >= 425 && msg.y <= 480){
						if(msg.x >= 200 && msg.x <= 400){
							cleardevice();
							ht.disp();
							show();
							string key = get_name();
							cleardevice();
							ht.disp();
							show();
							data = stoi(get_name());
							ht.insert(key, data);
							cleardevice();
							ht.disp();
							show();
						}
						else if(msg.x >= 500 && msg.x <= 700){
							cleardevice();
							ht.disp();
							show();
							string key = get_name();
							cleardevice();
							ht.disp();
							show();
							data = ht.find(key);
							outtextxy(450, 360, to_string(data).c_str());
						}
						else if(msg.x >= 800 && msg.x <= 1000){
							cleardevice();
							ht.disp();
							show();
							string key = get_name();
							ht.deletee(key);
							cleardevice();
							ht.disp();
							show();
						}
					}
					 
				}
			}
		}
		char ch;
		ch = _getch();
	}
}
