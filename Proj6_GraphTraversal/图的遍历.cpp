#include<bits/stdc++.h>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#define INF 0x7FFFFFFF
using namespace std;

// 输入数据 
/*
25 30 
0 39 37
1 755 36
2 710 112
3 378 146
4 448 172
5 657 164
6 542 222
7 635 237
8 190 231
9 266 261
10 350 282
11 438 290
12 526 292
13 252 352
14 435 371
15 577 375
16 189 474
17 266 451
18 400 445
19 479 439
20 557 462
21 266 522
22 327 487
23 395 520
24 448 558
0 9 1892
1 2 242
2 5 305
5 7 397
5 6 704
3 4 668
3 9 1145
4 6 137
4 11 695
6 12 674
8 9 216
9 10 676
10 11 511
11 12 349
10 13 842
11 14 534
12 15 651
13 16 1100
13 17 967
14 18 409
15 19 825
16 17 639
17 18 902
18 19 367
19 20 622
17 22 607
18 22 672
22 21 255
18 23 675
23 24 140
*/

template <typename T>
struct EdgeNode{
	bool mark;
	T vtx1;
	T vtx2;
	EdgeNode<T> *path1;
	EdgeNode<T> *path2;
	int weight;
	EdgeNode(T v1, T v2): vtx1(v1), vtx2(v2), path1(nullptr), path2(nullptr), weight(0), mark(false){}
	EdgeNode(T v1, T v2, int w): vtx1(v1), vtx2(v2), path1(nullptr), path2(nullptr), weight(w), mark(false){}
};

template <typename T>
struct VertexNode{
	T data;
	int x, y;
	EdgeNode<T> *fout;
	VertexNode(): data(0), x(0), y(0), fout(nullptr){}
	VertexNode(T data): data(data), x(0), y(0), fout(nullptr){}
	VertexNode(T data, EdgeNode<T> *n): data(data), x(0), y(0), fout(n){}
};

template <typename T>
struct Graph{
	
	vector<vector<int>> adj;
	VertexNode<T> **node;
	int order;
	int size;
	
	Graph(int o, int s): order(o), size(s){
		node = new VertexNode<T>*[o];
		adj.resize(o);
		for(int i = 0; i < order; i++){
			node[i] = new VertexNode<T>();
			adj[i].resize(o, INF);
			adj[i][i] = 0;
		}
		
	}
	
	void insert_edge(T v1, T v2, int w){
		EdgeNode<T> *to_add = new EdgeNode<T>(v1, v2, w), *tmp;
		if(node[v1]->fout == nullptr){
			node[v1]->fout = to_add;
		}
		else{
			tmp = node[v1]->fout;
			node[v1]->fout = to_add;
			to_add->path1 = tmp;
		}
		if(node[v2]->fout == nullptr){
			node[v2]->fout = to_add;
		}
		else{
			tmp = node[v2]->fout;
			node[v2]->fout = to_add;
			to_add->path2 = tmp;
		}
	}
	
	void disp(){
		for(int i = 0; i < order; i++){
			cout << i << " --> ";
			EdgeNode<T> *tmp = node[i]->fout;
			while(tmp != nullptr){
				cout << tmp->vtx1 << ':' << tmp->vtx2 << " --> ";
				if(tmp->vtx1 == i)
					tmp = tmp->path1;
				else
					tmp = tmp->path2;
			}
			cout << "NULL" << endl;
		}
		cout << endl;
	}
	
	void set_false(){
		for(int i = 0; i < order; i++){
			EdgeNode<T> *tmp = node[i]->fout;
			while(tmp != nullptr){
				tmp->mark = false;
				if(tmp->vtx1 == i)
					tmp = tmp->path1;
				else
					tmp = tmp->path2;
			}
		}
	}
	
	void print(){
		// 设置文字颜色
		settextcolor(BLACK);
		// 设置字体形式（高度，宽度，字体）
		settextstyle(15, 7.2, "楷体");
		// 圆的填充颜色函数
		setfillcolor(YELLOW); 
		// 边框线条颜色函数
		setlinecolor(WHITE);
		// 边框线条形式函数
		setlinestyle(PS_SOLID, 5);
		for(int i = 0; i < order; i++){
			EdgeNode<T> *tmp = node[i]->fout;
			if(tmp == nullptr)
				continue;
			EdgeNode<T> *tmp2 = tmp->path2;
			while(tmp != nullptr){
				line(node[tmp->vtx1]->x, node[tmp->vtx1]->y, node[tmp->vtx2]->x, node[tmp->vtx2]->y);
				outtextxy((node[tmp->vtx1]->x+node[tmp->vtx2]->x)/2-10, (node[tmp->vtx1]->y+node[tmp->vtx2]->y)/2-10, to_string(tmp->weight).c_str());
				tmp = tmp->path1;
			}
			while(tmp2 != nullptr){
				line(node[tmp2->vtx1]->x, node[tmp2->vtx1]->y, node[tmp2->vtx2]->x, node[tmp2->vtx2]->y);
				outtextxy((node[tmp2->vtx1]->x+node[tmp2->vtx2]->x)/2-10, (node[tmp2->vtx1]->y+node[tmp2->vtx2]->y)/2-10, to_string(tmp2->weight).c_str());
				tmp2 = tmp2->path2;
			}
		}
		settextstyle(25, 12, "楷体");
		setfillcolor(YELLOW);
		for(int i = 0; i < order; i++){
			solidcircle(node[i]->x, node[i]->y, 20);
			if(i < 10)
				outtextxy(node[i]->x-5, node[i]->y-10, to_string(i).c_str() );
			else
				outtextxy(node[i]->x-10, node[i]->y-10, to_string(i).c_str() );
		}
	}
	
	void print2(){
		// 设置文字颜色
		settextcolor(BLACK);
		// 设置字体形式（高度，宽度，字体）
		settextstyle(15, 7.2, "楷体");
		// 圆的填充颜色函数
		setfillcolor(YELLOW); 
		// 边框线条颜色函数
		setlinecolor(GREEN);
		// 边框线条形式函数
		setlinestyle(PS_SOLID, 8);
		for(int i = 0; i < order; i++){
			EdgeNode<T> *tmp = node[i]->fout;
			if(tmp == nullptr)
				continue;
			EdgeNode<T> *tmp2 = tmp->path2;
			while(tmp != nullptr){
				if(tmp->mark){
					line(node[tmp->vtx1]->x, node[tmp->vtx1]->y, node[tmp->vtx2]->x, node[tmp->vtx2]->y);
					outtextxy((node[tmp->vtx1]->x+node[tmp->vtx2]->x)/2-10, (node[tmp->vtx1]->y+node[tmp->vtx2]->y)/2-10, to_string(tmp->weight).c_str());
				}
				tmp = tmp->path1;
			}
			while(tmp2 != nullptr){
				if(tmp2->mark){
					line(node[tmp2->vtx1]->x, node[tmp2->vtx1]->y, node[tmp2->vtx2]->x, node[tmp2->vtx2]->y);
					outtextxy((node[tmp2->vtx1]->x+node[tmp2->vtx2]->x)/2-10, (node[tmp2->vtx1]->y+node[tmp2->vtx2]->y)/2-10, to_string(tmp2->weight).c_str());
				}
				tmp2 = tmp2->path2;
			}
		}
		settextstyle(25, 12, "楷体");
		setfillcolor(YELLOW);
		for(int i = 0; i < order; i++){
			solidcircle(node[i]->x, node[i]->y, 20);
			if(i < 10)
				outtextxy(node[i]->x-5, node[i]->y-10, to_string(i).c_str() );
			else
				outtextxy(node[i]->x-10, node[i]->y-10, to_string(i).c_str() );
		}
	}
	
	void bfs(T start){
		// 边框线条颜色函数
		setlinecolor(GREEN);
		// 边框线条形式函数
		setlinestyle(PS_SOLID, 8);
		if(start < 0 || start >= order)
			return;
		queue<T> que;
		vector<bool> visit(order, false);
		que.push(start);
		visit[start] = true;
		int counter = 0;
		settextstyle(18, 8, "楷体");
		while(!que.empty()){
			T t = que.front();
			cout << t << " ";
			outtextxy(90+25*counter++, 50, to_string(t).c_str() );
			que.pop();
			EdgeNode<T> *tmp = node[t]->fout;
			while(tmp != nullptr){
					
				if(tmp->vtx1 == t){
					if(!visit[tmp->vtx2]){
						visit[tmp->vtx2] = true;
						tmp->mark = true;
						line(node[tmp->vtx1]->x, node[tmp->vtx1]->y, node[tmp->vtx2]->x, node[tmp->vtx2]->y);
						Sleep(200);
						que.push(tmp->vtx2);
					}
					tmp = tmp->path1;
				}
				else{
					if(!visit[tmp->vtx1]){
						visit[tmp->vtx1] = true;
						tmp->mark = true;
						line(node[tmp->vtx1]->x, node[tmp->vtx1]->y, node[tmp->vtx2]->x, node[tmp->vtx2]->y);
						Sleep(200);
						que.push(tmp->vtx1);
					}
					tmp = tmp->path2;
				}
			}
		}
		cout << endl;
	}
	
	void dfs(T start){
		// 边框线条颜色函数
		setlinecolor(GREEN);
		// 边框线条形式函数
		setlinestyle(PS_SOLID, 8);
		if(start < 0 || start >= order)
			return;
		stack<T> sta;
		vector<bool> visit(order, false);
		vector<EdgeNode<T>*> rec(order);
		for(int i = 0; i < order; i++){
			rec[i] = node[i]->fout;
		}
		sta.push(start);
		cout << start << ' ';
		visit[start] = true;
		int counter = 0;
		settextstyle(18, 8, "楷体");
		outtextxy(90+25*counter++, 50, to_string(start).c_str() );
		while(!sta.empty() ){
			T t = sta.top();
			EdgeNode<T> *tmp = rec[t];
			if(tmp == nullptr){
				sta.pop();
			}
			else{
				if(tmp->vtx1 == t){
					if(!visit[tmp->vtx2]){
						visit[tmp->vtx2] = true;
						tmp->mark = true;
						sta.push(tmp->vtx2);
						cout << tmp->vtx2 << ' ';
						line(node[tmp->vtx1]->x, node[tmp->vtx1]->y, node[tmp->vtx2]->x, node[tmp->vtx2]->y);
						Sleep(200);
						outtextxy(90+25*counter++, 50, to_string(tmp->vtx2).c_str() );
					}
					rec[t] = tmp->path1;
 				}
				else if(tmp->vtx2 == t){
					if(!visit[tmp->vtx1]){
						visit[tmp->vtx1] = true;
						tmp->mark = true;
						sta.push(tmp->vtx1);
						cout << tmp->vtx1 << ' ';
						line(node[tmp->vtx1]->x, node[tmp->vtx1]->y, node[tmp->vtx2]->x, node[tmp->vtx2]->y);
						Sleep(200);
						outtextxy(90+25*counter++, 50, to_string(tmp->vtx1).c_str() );
					}
					rec[t] = tmp->path2;
				}
			}
		}
		cout << endl;
	}
	
	void dijkstra(int start){
		if(start < 0 || start >= order)
			return;
		vector<int> dist(order, INF);
		vector<int> pre(order, -1);
		vector<bool> visit(order, false);
		visit[start] = true;
		for(int i = 0; i < order; i++){
			dist[i] = adj[start][i];
			if(dist[i] < INF && dist[i] != 0)
				pre[i] = start;
		}
		for(int e = 1; e < order; e++){
			int minn = INF, min_pos = -1;
			for(int i = 0; i < order; i++){
				if(!visit[i] && dist[i] < minn){
					minn = dist[i];
					min_pos = i;
				}
			}
			if(min_pos == -1)
				break;
			visit[min_pos] = true;
			for(int i = 0; i < order; i++){
				if((long long)dist[min_pos] + adj[min_pos][i] < dist[i]){
					dist[i] = dist[min_pos] + adj[min_pos][i];
					pre[i] = min_pos;
				}
			}
		}
		for(int i = 0; i < order; i++){
			int tmp = pre[i];
			cout << i;
			if(tmp == -1){
				cout << " <- " << start;
			}
			while(tmp != -1){
				cout << " <- " << tmp;
				tmp = pre[tmp];
			}
			if(dist[i] == INF)
				cout << " : " << "INF" << endl;
			else
				cout << " : " << dist[i] << endl;
		}
	}
	
	void floyd(){
		int **dist = new int*[order];
		for(int i = 0; i < order; i++){
			dist[i] = new int[order];
			for(int j = 0; j < order; j++){
				dist[i][j] = adj[i][j];
			}
		}
		for(int e = 0; e < order; e++){
			for(int i = 0; i < order; i++){
				for(int j = 0; j < order; j++){
					if((long long)dist[i][e] + dist[e][j] < dist[i][j]){
						dist[i][j] = dist[i][e] + dist[e][j];
					}
				}
			}
		}
		for(int i = 0; i < order; i++){
			for(int j = 0; j < order; j++){
				cout << dist[i][j] << " ";
			}
			cout << endl;
		}
		for(int i = 0; i < order; i++){
			delete[] dist[i];
		}
		delete[] dist;
	}
	
	int find(int x, int *fa){
		if(fa[x] == x){
			return x;
		}
		else{
			fa[x] = find(fa[x], fa);
			return fa[x];
		}
	}
	
	void merge(int x, int y, int *fa, int *depth){
		int a = find(x, fa), b = find(y, fa);
		if(depth[a] >= depth[b]){
			fa[b] = a;
		}
		else{
			fa[a] = b;
		}
		if(depth[a] == depth[b]){
			depth[a]++;
		}
	}
	
	int kruskal(){
		int ans = 0;
		// 边框线条颜色函数
		setlinecolor(GREEN);
		// 边框线条形式函数
		setlinestyle(PS_SOLID, 8);
		int *fa = new int[order];
		int *depth = new int[order];
		bool **visit = new bool*[order];
		for(int i = 0; i < order; i++){
			fa[i] = i;
			depth[i] = 1;
			visit[i] = new bool[order];
			for(int j = 0; j < order; j++){
				visit[i][j] = false;
			}
		}
		for(int e = 1; e < order; e++){
			int minn = INF, si = -1, sj = 1;
			for(int i = 0; i < order; i++){
				for(int j = i+1; j < order; j++){
					if(!visit[i][j] && adj[i][j] < minn){
						minn = adj[i][j];
						si = i;
						sj = j;
					}
				}
			}
			if(find(si, fa) != find(sj, fa) ){
				Sleep(200);
				merge(si, sj, fa, depth);
				line(node[si]->x, node[si]->y, node[sj]->x, node[sj]->y);
				ans += adj[si][sj];
			}
			else{
				e--;
			}
			visit[si][sj] = true;
		}
		delete[] fa;
		delete[] depth;
		for(int i = 0; i < order; i++){
			delete[] visit[i];
		}
		delete[] visit;
		return ans;
	} 
};


Graph<int> mkGraph()
{
	int n, m, tmp1, tmp2, tmp3;
	FILE *fp(fopen("Graph.txt","r"));
	fscanf(fp, "%d,%d\n", &n, &m);
	cout << n << ' ' << m << endl;
	Graph<int> g(n, m);
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%d,%d,%d\n", &tmp1, &tmp2, &tmp3);
		cout << tmp1 << ' ' << tmp2 << ' ' << tmp3 << endl;
		g.node[tmp1]->x = tmp2;
		g.node[tmp1]->y = tmp3;
	}
	for (int k = 0; k < m; k++)
	{
		fscanf(fp, "%d,%d,%d\n", &tmp1, &tmp2, &tmp3);
		g.adj[tmp1][tmp2] = tmp3;
		g.adj[tmp2][tmp1] = tmp3;
		cout << tmp1 << ' ' << tmp2 << ' ' << tmp3 << endl;
		g.insert_edge(tmp1, tmp2, tmp3);
	}
	fclose(fp);
	g.disp();
	return g;
}

//Graph<int> mkGraph(){
//	int n, m, tmp1, tmp2, tmp3;
//	cin >> n >> m;
//	Graph<int> g(n, m);
//	for(int i = 0; i < n; i++){
//		cin >> tmp1 >> tmp2 >> tmp3;
//		g.node[i]->x = tmp2;
//		g.node[i]->y = tmp3;
//	}
//	for(int i = 0; i < m; i++){
//		cin >> tmp1 >> tmp2 >> tmp3;
//		g.insert_edge(tmp1, tmp2, tmp3);
//		g.adj[tmp1][tmp2] = tmp3;
//		g.adj[tmp2][tmp1] = tmp3;
////		g.insert_edge(tmp2, tmp1, tmp3);
//	}
//	g.disp();
//
//	return g;
//}

void llist(){
	setfillcolor(WHITE);
	settextstyle(25, 12, "楷体");
	solidrectangle(11, 600, 109, 650);
	solidrectangle(118, 600, 208, 650);
	solidrectangle(217, 600, 307, 650);
	solidrectangle(316, 600, 406, 650);
	solidrectangle(415, 600, 505, 650);
	solidrectangle(514, 600, 604, 650);
	solidrectangle(613, 600, 703, 650);
	solidrectangle(712, 600, 792, 650);
	outtextxy(36, 615, "原图"); 
	outtextxy(143, 615, "广搜"); 
	outtextxy(242, 615, "深搜"); 
	outtextxy(341, 615, "广树");
	outtextxy(440, 615, "深树");
	outtextxy(535, 615, "dijks");
	outtextxy(634, 615, "floyd");
	outtextxy(732, 615, "小树");
}

int main(){
	Graph<int> g = mkGraph();
	initgraph(800, 675, EW_SHOWCONSOLE);
	setbkmode(TRANSPARENT);
	// 设置背景颜色 
	COLORREF WH = RGB(235, 229, 209);
	setbkcolor(WH);
	cleardevice();
	g.print();
	int start;
	
	while(true){
		setfillcolor(WHITE);
		llist();
		while(!kbhit()){
			ExMessage msg = {0};
			if (peekmessage(&msg, EM_MOUSE))//检测鼠标信息
			{
				switch (msg.message)//筛选鼠标信息类型
				{
				case WM_LBUTTONDOWN://左键信息
					if(msg.y >= 600 && msg.y <= 650){
						if(msg.x >= 11 && msg.x <= 109){
							cleardevice();
							g.print();
							llist();
						}
						else if(msg.x >= 118 && msg.x <= 208){
							cleardevice();
							g.print();
							outtextxy(220, 50, "请输入起点编号，按ENTER结束输入");
							cin >> start;
							while(start < 0 || start >= g.order){
								outtextxy(270, 90, "输入编号无效，请重新输入");
								cin >> start;
							}
							cleardevice();
							llist();
							g.set_false();
							g.print();
							g.bfs(start);
							g.print2();
						}
						else if(msg.x >= 217 && msg.x <= 307){
							cleardevice();
							g.print();
							outtextxy(220, 50, "请输入起点编号，按ENTER结束输入");
							cin >> start;
							while(start < 0 || start >= g.order){
								outtextxy(270, 90, "输入编号无效，请重新输入");
								cin >> start;
							}	
							cleardevice();
							llist();
							g.set_false();
							g.print();
							g.dfs(start);
							g.print2();
						}
						else if(msg.x >= 316 && msg.x <= 406){
							cleardevice();
							g.print();
							outtextxy(220, 50, "请输入起点编号，按ENTER结束输入");
							cin >> start;
							while(start < 0 || start >= g.order){
								outtextxy(270, 90, "输入编号无效，请重新输入");
								cin >> start;
							}
							cleardevice();
							g.print();
							llist();
							g.set_false();
							g.bfs(start);
							cleardevice();
							llist();
							g.print2();
						}
						else if(msg.x >= 415 && msg.x <= 505){
							cleardevice();
							g.print();
							outtextxy(220, 50, "请输入起点编号，按ENTER结束输入");
							cin >> start;
							while(start < 0 || start >= g.order){
								outtextxy(270, 90, "输入编号无效，请重新输入");
								cin >> start;
							}
							cleardevice();
							g.print();
							llist();
							g.set_false();
							g.dfs(start);
							cleardevice();
							llist();
							g.print2();
						}
						else if(msg.x >= 514 && msg.x <= 604){
							cleardevice();
							g.print();
							outtextxy(220, 50, "请输入起点编号，按ENTER结束输入");
							cin >> start;
							while(start < 0 || start >= g.order){
								outtextxy(270, 90, "输入编号无效，请重新输入");
								cin >> start;
							}
							cleardevice();
							llist();
							g.print();
							g.dijkstra(start);
							outtextxy(260, 50, "请到另一窗口查看结果");
						}
						else if(msg.x >= 613 && msg.x <= 703){
							cleardevice();
							llist();
							g.print();
							g.floyd();
							outtextxy(260, 50, "请到另一窗口查看结果");
						}
						else if(msg.x >= 712 && msg.x <= 792){
							cleardevice();
							llist();
							g.print();
							g.set_false();
							int ans = g.kruskal();
							g.print2();
							outtextxy(275, 50, "最小生成树长度为");
							outtextxy(475, 50, to_string(ans).c_str());
						}
						cout << endl << endl;
					}
				}
			}
		}
		char ch;
		ch = _getch();
	}
}

// 输入数据 
/*
25 30 
0 39 37
1 755 36
2 710 112
3 378 146
4 448 172
5 657 164
6 542 222
7 635 237
8 190 231
9 266 261
10 350 282
11 438 290
12 526 292
13 252 352
14 435 371
15 577 375
16 189 474
17 266 451
18 400 445
19 479 439
20 557 462
21 266 522
22 327 487
23 395 520
24 448 558
0 9 1892
1 2 242
2 5 305
5 7 397
5 6 704
3 4 668
3 9 1145
4 6 137
4 11 695
6 12 674
8 9 216
9 10 676
10 11 511
11 12 349
10 13 842
11 14 534
12 15 651
13 16 1100
13 17 967
14 18 409
15 19 825
16 17 639
17 18 902
18 19 367
19 20 622
17 22 607
18 22 672
22 21 255
18 23 675
23 24 140
*/
