#include<bits/stdc++.h>
#include<easyx.h>
#include<graphics.h>
#include<conio.h>
using namespace std;


template<typename T>
void swapp(T &a, T &b){
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
struct Node{
	T data;
	Node<T> *next;
	Node(): data(0), next(nullptr){}
	Node(T data): data(data), next(nullptr){}
	Node(T data, Node<T> *next): data(data), next(next){}
};

template<typename T>
struct Node2{
	T data;
	Node2<T> *left;
	Node2<T> *right;
	Node2(): data(0), left(nullptr), right(nullptr){}
	Node2(T data): data(data), left(nullptr), right(nullptr){}
	Node2(T data, Node2<T> *left, Node2<T> *right): data(data), left(left), right(right){}
};

template<typename T>
class BinaryTree{
public:
	Node2<T> *root;
//	BinaryTree(){
//		root = new Node2<T>();
//	}
	BinaryTree(Node2<T> *root){
		this->root = root;
	}
//	BinaryTree(T data){
//		root = new Node2<T>(data);
//	}
//	BinaryTree(T data, Node2<T> *left, Node2<T> *right){
//		root = new Node2<T>(data, left, right);
//	}
	int SumWeight(){
		queue<Node2<T>*> que;
		Node2<T> *tmp;
		int child = 0, ans = 0, mem1 = 1, mem2 = 0, ceng = 0;
		que.push(root);
		while(!que.empty()){
			child = 0;
			tmp = que.front();
			if(tmp->left != nullptr){
				que.push(tmp->left);
				child++;
				mem2++;
			}
			if(tmp->right != nullptr){
				que.push(tmp->right);
				child++;
				mem2++;
			}
//			cout << tmp->data << ' ';
			if(child == 0){
				ans += tmp->data * ceng;
			}
			if(--mem1 == 0){
				mem1 = mem2;
				mem2 = 0;
				ceng++;
			}
			que.pop();
		}
		return ans;
	}
	
	void sortt(vector<vector<bool>> &ans, vector<int> &which){
		for(int i = 0; i < which.size()-1; i++){
			for(int j = 0; j < which.size()-1; j++){
				if(which[j] > which[j+1]){
					swapp(which[j], which[j+1]);
					swapp(ans[j], ans[j+1]);
				}
			}
		}
	}
	
	vector<vector<bool>> code(vector<int> weight){
		queue<Node2<T>*> que;
		vector<vector<bool>> ans;
		vector<int> which;
		queue<vector<bool>> code_que;
		Node2<T> *tmp;
		int child = 0, mem1 = 1, mem2 = 0, ceng = 0;
		que.push(root);
		code_que.push(vector<bool>() );
		while(!que.empty()){
			vector<bool> tmp_code = code_que.front();
			child = 0;
			tmp = que.front();
			if(tmp->left != nullptr){
				que.push(tmp->left);
				tmp_code.push_back(false);
				code_que.push(tmp_code);
				tmp_code = code_que.front();
				child++;
				mem2++;
			}
			if(tmp->right != nullptr){
				que.push(tmp->right);
				tmp_code.push_back(true);
				code_que.push(tmp_code);
				child++;
				mem2++;
			}
//			cout << tmp->data << ' ';
			if(child == 0){
				ans.push_back(tmp_code);
				for(int i = 0; i < weight.size(); i++){
					if(weight[i] == tmp->data){
						for(int j = 0; j < which.size(); j++){
							if(which[j] == i)
								break;
							else if(j == which.size()-1){
								which.push_back(i);
							} 
						}
						if(which.size() == 0){
							which.push_back(i);
						}
					}
				}
			}
			if(--mem1 == 0){
				mem1 = mem2;
				mem2 = 0;
				ceng++;
			}
			que.pop();
			code_que.pop();
		}
		sortt(ans, which);
		return ans;
	}
}; 


template<typename T>
class List{
public:
	Node<T> *head;
	int num;
	List(){
		head = new Node<T>(nullptr);
		num = 0;
	}
	void insert(T data){
		Node<T> *tmp = head;
		while(tmp->next != nullptr && data->data > tmp->next->data->data){
			tmp = tmp->next;
		}
		Node<T> *tmp2 = new Node<T>(data);
		tmp2->next = tmp->next;
		tmp->next = tmp2;
		num++;
//		disp();
		return;
	}
	bool pop(){
		if(num == 0)
			return false;
		head = head->next;
		num--;
		return true;
	}
	void disp()const{
		Node<T> *tmp = head->next;
		while(tmp != nullptr){
			cout << tmp->data->data << ' ';
			tmp = tmp->next;
		}
		cout << endl;
	}
	void merge(){
		
		while(num >= 2){
			Node2<int> *tmp1 = head->next->data;
			Node2<int> *tmp2 = head->next->next->data;
			int res = tmp1->data + tmp2->data;
			pop();
			pop();
			Node2<int> *node2 = new Node2<int>(res, tmp1, tmp2);
			insert(node2);
		}
	}
	
	vector<vector<bool>> init(int n, vector<int> weight){
		for(int i = 0; i < n; i++){
			Node2<int> *node2 = new Node2<int>(weight[i]);
			this->insert(node2);
		}
		this->merge();
		BinaryTree<int> bt((this->head)->next->data);
		vector<vector<bool>> ans = bt.code(weight);
		for(int i = 0; i < ans.size(); i++){
			for(int j = 0; j < ans[i].size(); j++){
				cout << ans[i][j];
			}
			cout << "   ";
		}
		cout << endl << bt.SumWeight();
		cout << endl;
		return ans;
	}
};


class Image{
public:
	IMAGE img;
	int height;
	int width;
	int CONSOLE_height;
	int CONSOLE_width;
	int **Gray;
	int **Red;
	int **Green;
	int **Blue;
public:
	Image(string address){
		loadimage(&img, _T(address.c_str() ) );
		height = img.getheight();
		width = img.getwidth();
		CONSOLE_height = height;
		CONSOLE_width = width;
		Red = new int*[height];
		Green = new int*[height];
		Blue = new int*[height];
		for(int i = 0; i < height; i++){
			Red[i] = new int[width];
			Green[i] = new int[width];
			Blue[i] = new int[width];
		}
		Gray = new int*[height];
		for(int i = 0; i < height; i++){
			Gray[i] = new int[width];
		}
	}
	
	void update(){
		getimage(&img, 0, 0, CONSOLE_width, CONSOLE_height);
		height = img.getheight();
		width = img.getwidth();
		CONSOLE_height = height;
		CONSOLE_width = width;
		Red = new int*[height];
		Green = new int*[height];
		Blue = new int*[height];
		for(int i = 0; i < height; i++){
			Red[i] = new int[width];
			Green[i] = new int[width];
			Blue[i] = new int[width];
		}
		Gray = new int*[height];
		for(int i = 0; i < height; i++){
			Gray[i] = new int[width];
		}
		DWORD *pMem = GetImageBuffer();
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				*pMem = BGR(*pMem);
				// 获取RGB的三个分量值
				Red[i][j] = GetRValue(*pMem);
				Green[i][j] = GetGValue(*pMem);
				Blue[i][j] = GetBValue(*pMem);
				Gray[i][j] = 0.3*Red[i][j] + 0.59*Green[i][j] + 0.11*Blue[i][j];
				pMem++;
			}
		}
	}
	
	void show(){
		//设置绘图窗口和图片一样大 并且显示控制台窗口
		initgraph(width, height, SHOWCONSOLE);
    	putimage(0, 0, &img); //显示图片
    	update();
	}
	
	void restore(){
		DWORD *pMem = GetImageBuffer();
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				*pMem =  RGB(Red[i][j], Green[i][j], Blue[i][j]);
				pMem++;
			}
		}
	}
	
	void up_scale(int h, int w){
		initgraph(2*width, 2*height, SHOWCONSOLE);
		IMAGE img2(2*width, 2*height);
		CONSOLE_height = 2*height;
		CONSOLE_width = 2*width;
		putimage(0, 0, &img2); //显示图片
		DWORD *pMem = GetImageBuffer();
		for(int i = 0; i < 2*height; i++){
			for(int j = 0; j < 2*width; j++){
				*pMem = BGR(*pMem);
				// 获取RGB的三个分量值
				int tmp1 = Red[(int)floor(i/2)][(int)floor(j/2)];
				int tmp2 = Green[(int)floor(i/2)][(int)floor(j/2)];
				int tmp3 = Blue[(int)floor(i/2)][(int)floor(j/2)];
//				Gray[i][j] = 0.3*R + 0.59*G + 0.11*B;
				*pMem =  RGB(tmp1, tmp2, tmp3);
				pMem++;
			}
		}
	}
	
	void down_scale(int h, int w){
		initgraph(width/2, height/2, SHOWCONSOLE);
		IMAGE img2(width/2, height/2);
		CONSOLE_height = height/2;
		CONSOLE_width = width/2;
		putimage(0, 0, &img2); //显示图片
		DWORD *pMem = GetImageBuffer();
		for(int i = 0; i < height/2; i++){
			for(int j = 0; j < width/2; j++){
				*pMem = BGR(*pMem);
				// 获取RGB的三个分量值
				int tmp1 = (Red[2*i][2*j] + Red[2*i+1][2*j] + Red[2*i][2*j+1] + Red[2*i+1][2*j+1]) / 4;
				int tmp2 = (Green[2*i][2*j] + Green[2*i+1][2*j] + Green[2*i][2*j+1] + Green[2*i+1][2*j+1]) / 4;
				int tmp3 = (Blue[2*i][2*j] + Blue[2*i+1][2*j] + Blue[2*i][2*j+1] + Blue[2*i+1][2*j+1]) / 4;
//				Gray[i][j] = 0.3*R + 0.59*G + 0.11*B;
				*pMem =  RGB(tmp1, tmp2, tmp3);
				pMem++;
			}
		}
	}
	
	void to_Gray(){
		DWORD *pMem = GetImageBuffer();
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				*pMem = BGR(*pMem);
				// 获取RGB的三个分量值
				BYTE R = Red[i][j];
				BYTE G = Green[i][j];
				BYTE B = Blue[i][j];
				Gray[i][j] = 0.3*R + 0.59*G + 0.11*B;
				*pMem =  RGB(Gray[i][j], Gray[i][j], Gray[i][j]);
				pMem++;
			}
		}
	}
	
	vector<int> count(){
		vector<int> weight(256);
		DWORD *pMem = GetImageBuffer();
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				*pMem = BGR(*pMem);
				// 获取RGB的三个分量值
				int Red = GetRValue(*pMem);
				int Green = GetGValue(*pMem);
				int Blue = GetBValue(*pMem);
				pMem++;
				weight[Red]++;
				weight[Green]++;
				weight[Blue]++;
			}
		}
		int sum = 0;
		for(int i = 0; i < 256; i++){
			cout << weight[i] << ' ';
			sum += weight[i];
		}
		cout << endl;
		cout << 8*sum << endl << endl;
		List<Node2<int>*> list;
		vector<vector<bool>> coder = list.init(256, weight);
		return weight;
	}
	
	vector<vector<vector<vector<bool>>>> code_pic(){
		vector<int> a = count();
		List<Node2<int>*> list;
		vector<vector<bool>> coder = list.init(256, a);
		vector<vector<vector<vector<bool>>>> code;
		for(int i = 0; i < 3; i++){
			code.push_back(vector<vector<vector<bool>>>() );
		}
		DWORD *pMem = GetImageBuffer();
		for(int i = 0; i < height; i++){
			code[0].push_back(vector<vector<bool>>() );
			code[1].push_back(vector<vector<bool>>() );
			code[2].push_back(vector<vector<bool>>() );
			for(int j = 0; j < width; j++){
				code[0][i].push_back(vector<bool>() );
				code[1][i].push_back(vector<bool>() );
				code[2][i].push_back(vector<bool>() );
				*pMem = BGR(*pMem);
				// 获取RGB的三个分量值
				int Red = GetRValue(*pMem);
				int Green = GetGValue(*pMem);
				int Blue = GetBValue(*pMem);
				pMem++;
				code[0][i][j] = coder[Red];
				code[1][i][j] = coder[Green];
				code[2][i][j] = coder[Blue];
			}
		}
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < code[i].size(); j++){
				for(int k = 0; k < code[i][j].size(); k++){
					for(int g = 0; g < code[i][j][k].size(); g++){
//						cout << code[i][j][k][g];
					}
					cout << "    ";
				}
				cout << endl;
			}
			cout << endl << endl;
		}
		return code;
	}
	
	void sobel(bool flag){
		// sobel算子边缘化 
		// flag为true时在rgb上进行边缘化 
		// false时在gray上进行边缘化 
		if(!flag){
			int **res = new int*[height];
			for(int i = 0; i < height; i++){
				res[i] = new int[width];
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					int gx = -1*Gray[i-1][j-1] -2*Gray[i][j-1] -Gray[i+1][j-1] \
						+Gray[i-1][j+1] +2*Gray[i][j+2] + Gray[i+1][j+1];
					int gy = -1*Gray[i-1][j-1] -2*Gray[i-1][j] -Gray[i-1][j+1] \
						+Gray[i+1][j-1] +2*Gray[i+1][j] + Gray[i+1][j+1];
					int tmp = abs(gx) + abs(gy);
					res[i][j] = tmp;
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[i][j], res[i][j], res[i][j]);
					pMem++;
				}
			}
		} 
		else{
			int *** res = new int**[3];
			for(int i = 0; i < 3; i++){
				res[i] = new int*[height];
				for(int j = 0; j < height; j++){
					res[i][j] = new int[width];
				}
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					int gx = -1*Red[i-1][j-1] -2*Red[i][j-1] -Red[i+1][j-1] \
						+Red[i-1][j+1] +2*Red[i][j+2] + Red[i+1][j+1];
					int gy = -1*Red[i-1][j-1] -2*Red[i-1][j] -Red[i-1][j+1] \
						+Red[i+1][j-1] +2*Red[i+1][j] + Red[i+1][j+1];
					int tmp = abs(gx) + abs(gy);
					res[0][i][j] = tmp;
					
					gx = -1*Green[i-1][j-1] -2*Green[i][j-1] -Green[i+1][j-1] \
						+Green[i-1][j+1] +2*Green[i][j+2] + Green[i+1][j+1];
					gy = -1*Green[i-1][j-1] -2*Green[i-1][j] -Green[i-1][j+1] \
						+Green[i+1][j-1] +2*Green[i+1][j] + Green[i+1][j+1];
					tmp = abs(gx) + abs(gy);
					res[1][i][j] = tmp;
					
					gx = -1*Blue[i-1][j-1] -2*Blue[i][j-1] -Blue[i+1][j-1] \
						+Blue[i-1][j+1] +2*Blue[i][j+2] + Blue[i+1][j+1];
					gy = -1*Blue[i-1][j-1] -2*Blue[i-1][j] -Blue[i-1][j+1] \
						+Blue[i+1][j-1] +2*Blue[i+1][j] + Blue[i+1][j+1];
					tmp = abs(gx) + abs(gy);
					res[2][i][j] = tmp;
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[0][i][j], res[1][i][j], res[2][i][j]);
					pMem++;
				}
			}
		}
	}
	
	void prewitt(bool flag){
		// prewitt算子边缘化 
		// flag为true时在rgb上进行边缘化 
		// false时在gray上进行边缘化 
		if(!flag){
			int **res = new int*[height];
			for(int i = 0; i < height; i++){
				res[i] = new int[width];
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					int gx = -1*Gray[i-1][j-1] -Gray[i][j-1] -Gray[i+1][j-1] \
						-Gray[i-1][j+1] -Gray[i][j+2] - Gray[i+1][j+1];
					int gy = -1*Gray[i-1][j-1] -Gray[i-1][j] -Gray[i-1][j+1] \
						+Gray[i+1][j-1] +Gray[i+1][j] + Gray[i+1][j+1];
					int tmp = abs(gx) + abs(gy);
					res[i][j] = tmp;
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[i][j], res[i][j], res[i][j]);
					pMem++;
				}
				delete[] res[i];
			}
			delete[] res;
		}
		else{
			int *** res = new int**[3];
			for(int i = 0; i < 3; i++){
				res[i] = new int*[height];
				for(int j = 0; j < height; j++){
					res[i][j] = new int[width];
				}
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					int gx = -1*Red[i-1][j-1] -Red[i][j-1] -Red[i+1][j-1] \
						+Red[i-1][j+1] +Red[i][j+2] + Red[i+1][j+1];
					int gy = -1*Red[i-1][j-1] -Red[i-1][j] -Red[i-1][j+1] \
						+Red[i+1][j-1] +Red[i+1][j] + Red[i+1][j+1];
					int tmp = abs(gx) + abs(gy);
					res[0][i][j] = tmp;
					
					gx = -1*Green[i-1][j-1] -Green[i][j-1] -Green[i+1][j-1] \
						+Green[i-1][j+1] +Green[i][j+2] + Green[i+1][j+1];
					gy = -1*Green[i-1][j-1] -Green[i-1][j] -Green[i-1][j+1] \
						+Green[i+1][j-1] +Green[i+1][j] + Green[i+1][j+1];
					tmp = abs(gx) + abs(gy);
					res[1][i][j] = tmp;
					
					gx = -1*Blue[i-1][j-1] -Blue[i][j-1] -Blue[i+1][j-1] \
						+Blue[i-1][j+1] +Blue[i][j+2] + Blue[i+1][j+1];
					gy = -1*Blue[i-1][j-1] -Blue[i-1][j] -Blue[i-1][j+1] \
						+Blue[i+1][j-1] +Blue[i+1][j] + Blue[i+1][j+1];
					tmp = abs(gx) + abs(gy);
					res[2][i][j] = tmp;
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[0][i][j], res[1][i][j], res[2][i][j]);
					pMem++;
				}
			}
		}
	}
	
	void laplacian4(bool flag){
		// laplacian4算子边缘化 
		// flag为true时在rgb上进行边缘化 
		// false时在gray上进行边缘化 
		if(!flag){
			int **res = new int*[height];
			for(int i = 0; i < height; i++){
				res[i] = new int[width];
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					res[i][j] = -Gray[i-1][j] -Gray[i+1][j] -Gray[i][j-1] \
						-Gray[i][j+1] + 4*Gray[i][j];
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[i][j], res[i][j], res[i][j]);
					pMem++;
				}
				delete[] res[i];
			}
			delete[] res;
		}
		else{
			int *** res = new int**[3];
			for(int i = 0; i < 3; i++){
				res[i] = new int*[height];
				for(int j = 0; j < height; j++){
					res[i][j] = new int[width];
				}
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					res[0][i][j] = -Red[i-1][j] -Red[i+1][j] -Red[i][j-1] \
						-Red[i][j+1] + 4*Red[i][j];
					res[1][i][j] = -Green[i-1][j] -Green[i+1][j] -Green[i][j-1] \
						-Green[i][j+1] + 4*Green[i][j];
					res[2][i][j] = -Blue[i-1][j] -Blue[i+1][j] -Blue[i][j-1] \
						-Blue[i][j+1] + 4*Blue[i][j];
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[0][i][j], res[1][i][j], res[2][i][j]);
					pMem++;
				}
			}
		}
	}
	
	void laplacian8(bool flag){
		// laplacian8算子边缘化 
		// flag为true时在rgb上进行边缘化 
		// false时在gray上进行边缘化 
		if(!flag){
			int **res = new int*[height];
			for(int i = 0; i < height; i++){
				res[i] = new int[width];
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					res[i][j] = -Gray[i-1][j-1] -Gray[i-1][j] -Gray[i-1][j+1] \
						-Gray[i][j-1] + 8*Gray[i][j] - Gray[i][j+1] \
						-Gray[i+1][j-1] -Gray[i+1][j] -Gray[i+1][j+1];
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[i][j], res[i][j], res[i][j]);
					pMem++;
				}
				delete[] res[i];
			}
			delete[] res;
		}
		else{
			int *** res = new int**[3];
			for(int i = 0; i < 3; i++){
				res[i] = new int*[height];
				for(int j = 0; j < height; j++){
					res[i][j] = new int[width];
				}
			}
			for(int i = 1; i < height-1; i++){
				for(int j = 1; j < width-1; j++){
					res[0][i][j] = -Red[i-1][j-1] -Red[i-1][j] -Red[i-1][j+1] \
						-Red[i][j-1] + 8*Red[i][j] - Red[i][j+1] \
						-Red[i+1][j-1] -Red[i+1][j] -Red[i+1][j+1];
					res[1][i][j] = -Green[i-1][j-1] -Green[i-1][j] -Green[i-1][j+1] \
						-Green[i][j-1] + 8*Green[i][j] - Green[i][j+1] \
						-Green[i+1][j-1] -Green[i+1][j] -Green[i+1][j+1];
					res[2][i][j] = -Blue[i-1][j-1] -Blue[i-1][j] -Blue[i-1][j+1] \
						-Blue[i][j-1] + 8*Blue[i][j] - Blue[i][j+1] \
						-Blue[i+1][j-1] -Blue[i+1][j] -Blue[i+1][j+1];
				}
			}
			DWORD *pMem = GetImageBuffer();
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					*pMem = RGB(res[0][i][j], res[1][i][j], res[2][i][j]);
					pMem++;
				}
			}
		}	
	}
	
};
 
int main()
{
//	Image image("D:\\1.jfif");
	Image image("D:\\color-block.png");
	image.show();
	MOUSEMSG m;
	char c;
	bool flag = true;
	cout << endl << endl; 
	cout << "按下 1 显示 RGB 原图" << endl;
	cout << "按下 2 显示 GARY 图像" << endl;
	cout << "按下 3 显示 prewitt 算子处理后的图像" << endl;
	cout << "按下 4 显示 sobel 算子处理后的图像" << endl;
	cout << "按下 5 显示 laplacian4 算子处理后的图像" << endl;
	cout << "按下 6 显示 laplacian8 算子处理后的图像" << endl;
	cout << "按下 7 将当前图像上采样至两倍大小" << endl;
	cout << "按下 8 将当前图像下采样至1/2大小" << endl;
	cout << "按下 9 将当前图像进行压缩存储" << endl;
	cout << "按下 0 将当前图像进行保存" << endl << endl;
	while(1)
	{
		c = _getch();
		cout << c << endl;
		switch(c){
			case '1':
				image.restore();
				flag = true;
				break;
			case '2':
				image.to_Gray();
				flag = false;
				break;
			case '3':
				image.prewitt(flag);
				break;
			case '4':
				image.sobel(flag);
				break;
			case '5':
				image.laplacian4(flag);
				break;
			case '6':
				image.laplacian8(flag);
				break;
			case '7':
				image.up_scale(1, 1);
				break;
			case '8':
				image.down_scale(1, 1);
				break;
			case '9':
				image.count();
				cleardevice();
				break;
			case '0':
				image.update();
				break;
		}
		cout << endl << endl; 
		cout << "按下 1 显示 RGB 原图" << endl;
		cout << "按下 2 显示 GARY 图像" << endl;
		cout << "按下 3 显示 prewitt 算子处理后的图像" << endl;
		cout << "按下 4 显示 sobel 算子处理后的图像" << endl;
		cout << "按下 5 显示 laplacian4 算子处理后的图像" << endl;
		cout << "按下 6 显示 laplacian8 算子处理后的图像" << endl;
		cout << "按下 7 将当前图像上采样至两倍大小" << endl;
		cout << "按下 8 将当前图像下采样至1/2大小" << endl;
		cout << "按下 9 将当前图像进行压缩存储" << endl;
		cout << "按下 0 将当前图像进行保存" << endl << endl;
	}	
	
	system("pause");
	closegraph();
}

