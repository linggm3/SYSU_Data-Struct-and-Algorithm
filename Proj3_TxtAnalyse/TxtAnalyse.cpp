#include<bits/stdc++.h>
#include<easyx.h>
#include<graphics.h>
#include <conio.h>
using namespace std;
#define ENDLINE 13
#define DELETe 8

int APPEAR_NUM = 0;

class KMP{
	private:
		string pat;
		int** dp;
	public:
		KMP(){
			;
		}
		
		void initialize(string pat, int mode = 0){
			this->pat = pat;
			int M = pat.size();
			if(mode == 0){
				// ��ʼ��dp 
				this->dp = new int*[M];
				for(int j = 0; j < M; j++){
					dp[j] = new int[256];
					for(int c = 0; c < 256; c++){
						dp[j][c] = 0;
					}
				}
				// Ӱ��״̬
				int X = 0; 
				// ����dp���� 
				dp[0][pat[0]] = 1;
				// jΪ��ǰ״̬��cΪ�ַ� 
				for(int j = 1; j < M; j++){
					for(int c = 0; c < 256; c++){
						if(c == pat[j]){
							dp[j][c] = j + 1;
						}
						else{
							dp[j][c] = dp[X][c];
						}
					}
					// ����Ӱ��״̬ 
					X = dp[X][pat[j] ];
				}
			}
			
			else{
				// ��ʼ��dp
				this->dp = new int*[M];
				for(int j = 0; j < M; j++){
					dp[j] = new int[256];
					for(int c = 0; c < 256; c++){
						dp[j][c] = 0;
					}
				}
				// Ӱ��״̬
				int X = 0; 
				// ����dp���� 
				dp[0][pat[0]] = 1;
				if(isupper(pat[0]) ){
					dp[0][pat[0] - 'A' + 'a'] = 1;
				} 
				else if(islower(pat[0]) ){
					dp[0][pat[0] - 'a' + 'A'] = 1;
				}
				// jΪ��ǰ״̬��cΪ�ַ�
				bool flag = false; // ��ƥ���Сд 
				int cc = -1;
				for(int j = 1; j < M; j++){
					flag = false;
					for(int c = 0; c < 256; c++){
						if(c == pat[j]){
							dp[j][c] = j + 1;
							if(isupper(c ) ){
								cc =  c - 'A' + 'a';
								dp[j][c - 'A' + 'a'] = j+1;
								flag = true;
							} 
							else if(islower(c ) ){
								cc = c - 'a' + 'A';
								dp[j][c - 'a' + 'A'] = j+1;
								flag = true;
							}
						}
						else if(flag && c == cc){
							continue; // ��Сд������ 
						}
						else{
							dp[j][c] = dp[X][c];
						}
					}
					// ����Ӱ��״̬ 
					X = dp[X][pat[j] ];
				}
			}
			
		}
		
		~KMP(){
			int M = pat.size();
			for(int i = 0; i < M; i++){
				delete[] dp[i];
			}
			delete[] dp;
		}
		
		vector<int> search(const string& txt){
			vector<int> ans;
			APPEAR_NUM = 0;
			int M = pat.size();
			int N = txt.size();
			
			int j = 0;
			for(int i = 0; i < N; i++){
				j = dp[j][txt[i] ];
				if(j == M){
					APPEAR_NUM++;
					ans.push_back(i - j + 1);
					j = 0;
				}
			}
			return ans;
		}
		
		int search_num(const string& txt){
			int ans = 0;
			int M = pat.size();
			int N = txt.size();
			int j = 0;
			cout << "ans = " << ans << endl;
			for(int i = 0; i < N; i++){
				j = dp[j][txt[i] ];
				if(j == M){
					ans++;
					j = 0;
				}
			}
			return ans;
		}
		
};

/* �Զ���ṹ�����sort���� */
typedef pair<string, int> PAIR;

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second < rhs.second;
	}
};


string output_message(string source, string str, vector<int> ans){
	source += string("  \"") + str + string("\"����") + to_string(ans.size()) + string("��, ");
	if(ans.size() == 0){
		source = source.erase(source.size()-2, 2);
		return source;
	}
	source +=  string("�ֱ���");
	for(int i = 0; i < ans.size(); i++){
		source += to_string(ans[i]) + ", ";
	} 
	source = source.erase(source.size()-2, 2);
	source +=  string("��\n\n");
	return source;
}

string output_message2(string source, string TXT, int k){
	map<string, int> MAP;
	string s = "";
	for(int i = 0; i < TXT.size(); i++){
		if(TXT[i] == '.' || TXT[i] == ',' || TXT[i] == ' ' || TXT[i] == ';'){
			if(s == "" || s == " ")
				continue;
			MAP[s]++;
			s = "";
		}
		else{
			s += TXT[i];
		}
	}
	// ��map��Ԫ��ת�浽vector�У� ����ʹ�������㷨
	vector<PAIR> countVec(MAP.begin(), MAP.end() );

	// ����
	sort(countVec.begin(), countVec.end(), CmpByValue());
	
	if(countVec.size() < k){
		source += string("�ı��г��ֵ��ʲ���") + to_string(k) + string("��"); 
		return source;
	}
	// ������
	for(int i = 1; i <= k; i++){
		source += countVec[countVec.size()-i].first + string("������") + to_string(countVec[countVec.size()-i].second) + string("��\n");
	}
	
	
	return source;
}

int main()
{
//	initgraph(1000, 600, EW_SHOWCONSOLE);
	initgraph(1000, 600);
	// ���ñ�����ɫ 
	COLORREF WH = RGB(235, 229, 209);
	setbkcolor(WH);
	// �ñ�����ɫ�����Ļ 
	cleardevice();
	// ����������ɫ
	settextcolor(BLACK);
	// ����������ʽ���߶ȣ���ȣ����壩
	settextstyle(25, 12, "����");
	// Բ�������ɫ����
	setfillcolor(WHITE); 
	// �߿�������ɫ����
	setlinecolor(WHITE);
	// �߿�������ʽ����
	setlinestyle(PS_SOLID, 10);
	setbkmode(TRANSPARENT);
	
	string TXT = "";
	string PAT[10] = {""};
	int appear_num[10] = {0};
	KMP kmp_pat[10];
	int Line_Counter = 0;
	string output_msg;
	int Pat_Counter = -1;
	vector<int> tmp;
	int flag = 1, i = 0, i2, dist, mode = 0;
	while(1){
		cleardevice();//�����һ�λ滭��ͼ�η�ֹ�����ص�
		Line_Counter = TXT.size() / 75;
		i = Line_Counter <= 15 ? 0 : Line_Counter - 15;
		for(i2 = 0; i <= Line_Counter; i++, i2++){
			outtextxy(48, 20+25*i2, TXT.substr(75*i, 75).c_str() ); 
		}
		dist = 960 / (Pat_Counter+2); 
		for(i = 0; i <= Pat_Counter; i++){
			outtextxy( 10+(i+1)*dist, 430, ('\"'+PAT[i]+'\"').c_str() ); 
		}
		if(flag == 1){
			for(i = 0; i <= Pat_Counter; i++){
				outtextxy( 15*PAT[i].size()/2 + 10 + (i+1)*dist, 455, to_string(appear_num[i] ).c_str() ); 
			}
		}
		solidrectangle(25, 525, 175, 575);
		solidrectangle(225, 525, 375, 575);
		solidrectangle(425, 525, 497, 575);
		solidrectangle(504, 525, 575, 575);
		solidrectangle(625, 525, 775, 575);
		solidrectangle(825, 525, 975, 575);
		outtextxy(53, 540, "�����ı�"); 
		outtextxy(253, 540, "����ģʽ"); 
		outtextxy(453, 540, "��ʼͳ��"); 
		outtextxy(653, 540, "�������"); 
		if(mode)
			outtextxy(830, 540, "��ƥ���Сд");
		else
			outtextxy(840, 540, "ƥ���Сд");
		while(!kbhit() ) //��û�м�����
		{
			ExMessage msg = {0};
			if (peekmessage(&msg, EM_MOUSE));//��������Ϣ
			{
				switch (msg.message)//ɸѡ�����Ϣ����
				{
				case WM_LBUTTONDOWN://�����Ϣ
					if(msg.y >= 525 && msg.y <= 575){
						if(msg.x >= 25 && msg.x <= 175){
							cout << 1 << endl;
							flag = 1;
						}
						else if(msg.x >= 225 && msg.x <= 375){
							cout << 2 << endl;
							flag = 2;
							Pat_Counter++;
						}
						else if(msg.x >= 425 && msg.x <= 500){
							cout << 3 << endl;
							flag = 3;
						}
						else if(msg.x >= 500 && msg.x <= 575){
							cout << 5 << endl;
							flag = 5;
						}
						else if(msg.x >= 625 && msg.x <= 775){
							cout << 4 << endl;
							flag = 4;
						}
						else if(msg.x >= 825 && msg.x <= 975){
							mode = (mode + 1) % 2;
						}
					}
					break;

				default:
					break;
				}
			}
		}
		char ch;
		ch = _getch();
		if(flag == 1){
			switch(ch){
				case DELETe:
					if(!TXT.empty() )
						TXT = TXT.erase(TXT.size()-1, 1);
					break;
				default:
					TXT += ch;
					break;
			}
		}
		else if(flag == 2){
			if(Pat_Counter < 0)
				Pat_Counter = 0;
			switch(ch){
				case DELETe:
					if(!PAT[Pat_Counter].empty() )
						PAT[Pat_Counter] = PAT[Pat_Counter].erase(PAT[Pat_Counter].size()-1, 1);
					else{
						if(Pat_Counter >= 0)
							Pat_Counter--;
					}
					break;
				default:
					PAT[Pat_Counter] += ch;
					break;
			}
		}
		else if(flag == 3){
			cout << TXT.size() << endl;
			output_msg = "";
			for(int i = 0; i <= Pat_Counter; i++){
				kmp_pat[i].initialize(PAT[i], mode);
				tmp = kmp_pat[i].search(TXT);
				output_msg = output_message(output_msg, PAT[i], tmp);
				appear_num[i] = APPEAR_NUM;
//				appear_num[i] = kmp_pat[i].search_num(TXT);
				cout << appear_num[i] << endl;
			}
			HWND hn = GetHWnd();//��ȡ���ھ��������
			SetWindowText(hn, "TxtAnalyse");//�޸Ĵ������ֺ���
			MessageBox(hn, output_msg.c_str(), "���ҽ��", MB_OKCANCEL);//��Ϣ�򵯳����ú���
			flag = 1;
		}
		else if(flag == 4){
			TXT = "";
			Pat_Counter = -1;
			flag = 1;
			for(int i = 0; i < 10; i++){
				PAT[i] = "";
			}
			continue;
		}
		else if(flag == 5){
			output_msg = "";
			output_msg = output_message2(output_msg, TXT, 5);
			HWND hn = GetHWnd();//��ȡ���ھ��������
			SetWindowText(hn, "TxtAnalyse");//�޸Ĵ������ֺ���
			MessageBox(hn, output_msg.c_str(), "�������ĵ���", MB_OKCANCEL);//��Ϣ�򵯳����ú���
			flag = 1;
		}
		cout << ch << endl;
	}
	system("pause");
}
