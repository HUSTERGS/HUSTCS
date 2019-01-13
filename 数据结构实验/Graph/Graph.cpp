//无向图
//C++
#include<queue>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define OK 1
#define ERROR -1

using namespace std;

typedef int status;
typedef int ElemType;


//创建的模板，用于查找vector中目标元素的位置
template <typename T>
int findElem(T target, string name) {
	for (int i = target.size() - 1; i >= 0; i--) {
		if (target[i].name == name) {
			return i;
		}
	}
	return -1;
}


class Vex {
public:
	ElemType data;
	string name;
	bool visited;
	Vex * nextVex;
	//构造函数
	Vex(string name, ElemType data) {
		this->data = data;
		this->name = name;
		this->visited = false;
		this->nextVex = nullptr;
	}

	void DestroyVex(Vex * v) {
		if (v != nullptr) {
			DestroyVex((*v).nextVex);
			delete v;
		}
	}
	void Destroy() {
		DestroyVex(nextVex);
	}
};

class Graph {
public:
	vector <Vex> List;
	string name;
	Graph(string graphname) {
		name = graphname;
	}
	/*New Destroy with built-in iterator for vector*/
	void Destroyself() {
		for (auto v : List) {
			v.Destroy();
		}
		List.clear();
	}

	void AddVex(string vexname, ElemType vexvalue) {
		Vex v(vexname, vexvalue);
		List.push_back(v);
	}
};

class Index {
public:
	int currentGraphIndex;
	vector <Graph> List;

	status CreateGraph(string graphname);
	status DestroyGraph(string graphname);
	Vex & LocateVex(string graphname, string vexname);
	ElemType GetVex(string graphname, string vexname);
	status PutVex(string graphname, string vexname, ElemType value);
	Vex * FirstAdjVex(string graphname, string vexname);
	Vex * NextAdjVex(string graphname, string vexname, string vexname2);
	status InsertVex(string graphname, string vexname, ElemType data);
	status DeleteVex(string graphname, string vexname);
	status InsertArc(string graphname, string vexname1, string vexname2);
	status DeleteArc(string graphname, string vexname1, string vexname2);
	status DFSTraverse(string graphname, void (*visit)(Vex));
	status BFSTraverse(string graphname, void (*visit)(Vex));

	void SaveData();
	void LoadData();
	void PrintTable();



	int GraphExist(string graphname) {
		int gposition = findElem(List, graphname);
		if (gposition >= 0) {
			return gposition;
		}
		else {
			return -1;
		}
	}

	bool VexExist(string graphname, string vexname) {
		int gposition = GraphExist(graphname);
		if (gposition >= 0) {
			int vposition = findElem(List[gposition].List, vexname);
			if (vposition >= 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	void Clearvisited(string graphname) {
		int gposition = findElem(List, graphname);
		/*new clear with built-in iterator with vector*/
		for (auto i : List[gposition].List) {
			i.visited = false;
		}
	}
private:
	void DFS(Graph & G, int position, void(*visit)(Vex), string graphname);
};






status Index::CreateGraph(string graphname) {
	Graph G(graphname);
	List.push_back(G);
	cout << "请输入将要输入的节点数目" << endl;

	//一些临时变量
	int vexnum;
	int arcnum;
	string vexname;
	string vexname2;
	int vexvalue;


	cin >> vexnum;
	cout << "请依次输入" << vexnum << "个节点的名字以及每个节点的值" << endl;
	for (int i = 0; i < vexnum; i++) {
		cin >> vexname;
		cin >> vexvalue;
		InsertVex(graphname, vexname, vexvalue);
	}
	cout << "请输入要输入边的数目" << endl;
	cin >> arcnum;
	cout << "请依次输入" << arcnum << "组边的两个节点名字" << endl;
	for (int i = 0; i < arcnum; i++) {
		cin >> vexname;
		cin >> vexname2;
		InsertArc(graphname, vexname, vexname2);
	}
	return OK;
}

status Index::DestroyGraph(string graphname) {
	int position = findElem(List, graphname);
	if (position >= 0) {
		List[position].Destroyself();
		vector<Graph>::iterator iter = List.begin() + position;
		List.erase(iter);
		return OK;
	}
	else {
		return ERROR;
	}
}

Vex & Index::LocateVex(string graphname, string vexname) {
	int gposition = findElem(List, graphname);
	int vposition = findElem(List[gposition].List, vexname);
	return List[gposition].List[vposition];
}

ElemType Index::GetVex(string graphname, string vexname) {
	return LocateVex(graphname, vexname).data;
}

status Index::PutVex(string graphname, string vexname, ElemType value) {
	Vex &target = LocateVex(graphname, vexname);
	Vex * temp = &target;
	target.data = value;
	while (temp->nextVex) {
		//找到邻接节点
		Vex tempV = LocateVex(graphname, temp->nextVex->name);
		while (tempV.nextVex->name != target.name)
			tempV = *tempV.nextVex;
		//找到后，更新值
		tempV.nextVex->data = value;
		temp = temp->nextVex;
	}
	return OK;
}

Vex * Index::FirstAdjVex(string graphname, string vexname) {
	int gposition = findElem(List, graphname);
	int vposition = findElem(List[gposition].List, vexname);
	Vex temp = List[gposition].List[vposition];
	if (temp.nextVex) {
		return temp.nextVex;
	}
	else {
		return nullptr;
	}
}

Vex * Index::NextAdjVex(string graphname, string vexname, string vexname2) {
	int gposition = findElem(List, graphname);
	int vposition = findElem(List[gposition].List, vexname);
	Vex temp = List[gposition].List[vposition];
	while (temp.nextVex) {
		if (temp.nextVex->name == vexname2 && temp.nextVex->nextVex) {
			return temp.nextVex->nextVex;
		}
		temp = *temp.nextVex;
	}
	return nullptr;
}

status Index::InsertVex(string graphname, string vexname, ElemType data) {
	int position = findElem(List, graphname);
	List[position].AddVex(vexname, data);
	return OK;
}

status Index::DeleteVex(string graphname, string vexname) {
	int gposition = findElem(List, graphname);
	int vposition = findElem(List[gposition].List, vexname);
	Vex & target = LocateVex(graphname, vexname);
	Vex * temp = &target;
	while (temp->nextVex) {
		//找到邻接节点
		Vex *tempV = &(LocateVex(graphname, temp->nextVex->name));
		while (tempV->nextVex->name != target.name)
			tempV = tempV->nextVex;
		//找到后，创建临时指针用于删除点
		Vex * deleteTemp = tempV->nextVex;
		//在邻接点的邻接链表中去掉目标节点
		tempV->nextVex = tempV->nextVex->nextVex;
		//删除点
		delete deleteTemp;
		temp = temp->nextVex;
	}
	target.Destroy();
	vector<Vex>::iterator iter = List[gposition].List.begin() + vposition;
	List[gposition].List.erase(iter);
	return OK;
}

status Index::InsertArc(string graphname, string vexname1, string vexname2) {
	Vex &v1 = LocateVex(graphname, vexname1);
	Vex &v2 = LocateVex(graphname, vexname2);
	Vex * tempV1 = &v1;
	Vex * tempV2 = &v2;
	while (tempV1->nextVex) {
		if (tempV1->nextVex->name == v2.name)
			return ERROR;
		tempV1 = tempV1->nextVex;
	}
	while (tempV2->nextVex) {
		if (tempV2->nextVex->name == v1.name)
			return ERROR;
		tempV2 = tempV2->nextVex;
	}
	tempV1->nextVex = new Vex(v2.name, v2.data);
	tempV2->nextVex = new Vex(v1.name, v1.data);
	return OK;
}

status Index::DeleteArc(string graphname, string vexname1, string vexname2) {
	Vex &v1 = LocateVex(graphname, vexname1);
	Vex &v2 = LocateVex(graphname, vexname2);
	Vex * tempV1 = &v1;
	Vex * tempV2 = &v2;
	while (tempV1) {
		if (tempV1->nextVex->name == v2.name)
			break;
		else
			tempV1 = tempV1->nextVex;
	}
	while (tempV2) {
		if (tempV2->nextVex->name == v1.name)
			break;
		else
			tempV2 = tempV2->nextVex;
	}
	if (!(tempV1 && tempV2)) {
		return ERROR;
	}
	else {
		Vex * deleteTemp1 = tempV1->nextVex;
		Vex * deleteTemp2 = tempV2->nextVex;
		tempV1->nextVex = tempV1->nextVex->nextVex;
		tempV2->nextVex = tempV2->nextVex->nextVex;
		delete deleteTemp1;
		delete deleteTemp2;
		return OK;
	}
}


void Index::DFS(Graph & G, int position, void (*visit)(Vex), string graphname) {
	G.List[position].visited = true;
	visit(G.List[position]);
	for (Vex * w = G.List[position].nextVex; w != nullptr; w = w->nextVex) {
		if (!LocateVex(graphname, w->name).visited) {
			DFS(G, findElem(G.List, w->name), visit, graphname);
		}
	}
}

status Index::DFSTraverse(string graphname, void (*visit)(Vex)) {
	int gposition = findElem(List, graphname);
	Graph & G = List[gposition];
	for (int i = 0; i < G.List.size(); i++) {
		if (!G.List[i].visited)
			DFS(G, i, visit, G.name);
	}
	return OK;
}

status Index::BFSTraverse(string graphname, void(*visit)(Vex)) {
	queue <string> Queue;
	int gposition = findElem(List, graphname);
	Graph & G = List[gposition];
	for (auto i : G.List) {
		if (!i.visited) {
			Queue.push(i.name);
			while (Queue.size() != 0) {
				string vname = Queue.front();
				if (!G.List[findElem(G.List, vname)].visited) {
					visit(LocateVex(graphname, vname));
					G.List[findElem(G.List, vname)].visited = true;
				}
				Queue.pop();
				for (Vex * w = LocateVex(graphname, vname).nextVex; w != nullptr; w = w->nextVex) {
					if (!LocateVex(graphname, w->name).visited)
						Queue.push(w->name);
				}
			}
		}
	}
	return OK;
}
//用于打印邻接表
void Index::PrintTable() {
	for (auto i : List) {
		cout << "图: " << i.name << endl;
		cout << endl;
		for (auto j : i.List) {
			for (Vex * temp = &j; temp != nullptr; temp = temp->nextVex) {
				cout << " -> " << "(" << temp->name << ", " << temp->data << ")";
			}
			cout << endl;
			cout << endl;
		}
	}
}


void Index::SaveData() {
	ofstream outfile;
	outfile.open("data.txt", ios::out);
	//图的数量
	outfile << List.size() << endl;
	int arcnum = 0;
	for (auto i : List) {
		//图的名字
		outfile << i.name << endl;
		//图中节点的个数
		outfile << " " << i.List.size() << endl;
		for (auto j : i.List) {
			//节点的名字以及节点的值
			outfile << j.name << " " << j.data << endl;
		}
		for (auto j : i.List) {
			//边的信息
			for (Vex * w = j.nextVex; w != nullptr; w = w->nextVex) {
				//outfile << j.name << " " << w->name << endl;
				arcnum++;
			}
		}
		outfile << arcnum << endl;
		for (auto j : i.List) {
			//边的信息
			for (Vex * w = j.nextVex; w != nullptr; w = w->nextVex) {
				outfile << j.name << " " << w->name << endl;
			}
		}
	}
	outfile.close();
}

void Index::LoadData() {
	ifstream  infile;
	infile.open("data.txt", ios::in);
	int graphnum;
	int vexnum;
	int arcnum;
	string graphname;
	string vexname1;
	string vexname2;
	ElemType vexvalue;
	infile >> graphnum;
	for (int i = 0; i < graphnum; i++) {
		infile >> graphname;
		Graph G(graphname);
		List.push_back(G);
		infile >> vexnum;
		for (int j = 0; j < vexnum; j++) {
			infile >> vexname1;
			infile >> vexvalue;
			InsertVex(graphname, vexname1, vexvalue);
		}
		infile >> arcnum;
		for (int m = 0; m < arcnum; m++) {
			infile >> vexname1;
			infile >> vexname2;
			InsertArc(graphname, vexname1, vexname2);
		}
	}
}

void PrintMenu() {
	cout << "|-------------------Graph Experiment Menu-----------------|" << endl;
	cout << "|             1. 创建图                2. 销毁图           |" << endl;
	cout << "|             3. 查找顶点              4. 获得顶点值        |" << endl;
	cout << "|             5. 顶点赋值              6. 获得第一邻节点    |" << endl;
	cout << "|             7. 获得下一邻节点         8. 插入节点         |" << endl;
	cout << "|             9. 删除节点              10. 插入弧           |" << endl;
	cout << "|             11. 删除弧               12. 深度优先         |" << endl;
	cout << "|             13. 广度优先             14. 保存数据         |" << endl;
	cout << "|             15. 导入数据             16. 打印邻接表       |" << endl;
}

void visit(Vex v) {
	cout << "(" << v.name << ", " <<v.data << ") ";
}

int main(void) {
	int op = 1;
	string graphname;
	string vexname;
	string vexname2;
	ElemType vexvalue;
	Index index;
	PrintMenu();
	while (op) {
		cin >> op;
		system("cls");
		PrintMenu();
		switch (op)
		{
		case 1:
			cout << "请输入要创建的图名" << endl;
			cin >> graphname;
			if (index.GraphExist(graphname) >= 0) {
				cout << "该图名已被使用" << endl;
			}
			else {
				index.CreateGraph(graphname);
				cout << "创建成功" << endl;
			}
			break;
		case 2:
			cout << "请输入要销毁的图名" << endl;
			cin >> graphname;
			if (index.GraphExist(graphname) >= 0) {
				index.DestroyGraph(graphname);
				cout << "销毁成功" << endl;
			}
			else {
				cout << "输入的图名不存在" << endl;
			}
			break;
		case 3:
			cout << "请输入要查找的节点所在图的名字以及节点本身的名字" << endl;
			cin >> graphname;
			cin >> vexname;
			if (index.VexExist(graphname, vexname)) {
				Vex v = index.LocateVex(graphname, vexname);
				cout << "位于图" << graphname << "的节点" << vexname << "的值为" << v.data;
			}
			else {
				cout << "输入的节点不存在" << endl;
			}
			break;
		case 4:
			cout << "请输入要获取的节点所在图的名字以及节点本身的名字" << endl;
			cin >> graphname;
			cin >> vexname;
			if (index.VexExist(graphname, vexname)) {
				int value = index.GetVex(graphname, vexname);
				cout << "位于图" << graphname << "的节点" << vexname << "的值为" << value;
			}
			else {
				cout << "输入的节点不存在" << endl;
			}
			break;
		case 5:
			cout << "请输入要赋值的节点所在图的名字以及节点本身的名字" << endl;
			cin >> graphname;
			cin >> vexname;
			if (index.VexExist(graphname, vexname)) {
				cout << "位于图" << graphname << "的节点" << vexname << "的值为" << index.GetVex(graphname, vexname) << endl;
				cout << "请输入新值" << endl;
				cin >> vexvalue;
				index.PutVex(graphname, vexname, vexvalue);
				cout << "位于图" << graphname << "的节点" << vexname << "的值已修改为" << vexvalue << endl;
			}
			else {
				cout << "输入的节点不存在" << endl;
			}
			break;
		case 6:
			cout << "请输入要查找的节点所在图的名字以及节点本身的名字" << endl;
			cin >> graphname;
			cin >> vexname;
			if (index.VexExist(graphname, vexname)) {
				Vex * v = index.FirstAdjVex(graphname, vexname);
				if (v) {
					cout << "位于图" << graphname << "的节点" << vexname << "的第一邻接点为";
					cout << "名为" << v->name << "且值为" << v->data << "的节点" << endl;
				}
				else {
					cout << "位于图" << graphname << "的节点" << vexname << "不存在第一邻接点";
				}
			}
			else {
				cout << "输入的节点不存在" << endl;
			}
			break;
		case 7:
			cout << "请输入两个节点所在图的名字以及两个节点的名字" << endl;
			cin >> graphname;
			cin >> vexname;
			cin >> vexname2;
			if (index.VexExist(graphname, vexname) && index.VexExist(graphname, vexname2)) {
				Vex * v = index.NextAdjVex(graphname, vexname, vexname2);
				if (v) {
					cout << "位于图" << graphname << "的" << vexname << "相对于" << vexname2 << "的下一邻接节点为";
					cout << "名为" << v->name << "且值为" << v->data << "的节点" << endl;
				}
				else {
					cout << "位于图" << graphname << "的" << vexname << "相对于" << vexname2 << "的下一邻接节点不存在";
				}
			}
			else {
				cout << "输入的节点或图不存在" << endl;
			}
			break;
		case 8:
			cout << "请输入目标图的名称和要插入的节点的名称以及值" << endl;
			cin >> graphname;
			cin >> vexname;
			cin >> vexvalue;
			if (index.GraphExist(graphname) >= 0) {
				if (index.VexExist(graphname, vexname)) {
					cout << "目标图" << graphname << "中已存在名为" << vexname << "的节点" << endl;
				}
				else {
					index.InsertVex(graphname, vexname, vexvalue);
					cout << "插入成功" << endl;
				}
			}
			else {
				cout << "目标图不存在" << endl;
			}
			break;
		case 9:
			cout << "请输入目标图的名称和要删除的节点的名称" << endl;
			cin >> graphname;
			cin >> vexname;
			if (index.GraphExist(graphname) >= 0) {
				if (index.VexExist(graphname, vexname)) {
					if (index.DeleteVex(graphname, vexname) == OK)
						cout << "删除成功" << endl;
					else
						cout << "删除失败" << endl;
				}
				else {
					cout << "目标图" << graphname << "中已不存在名为" << vexname << "的节点" << endl;
				}
			}
			else {
				cout << "目标图不存在" << endl;
			}
			break;
		case 10:
			cout << "请输入要插入的图的名称以及两个顶点的名称" << endl;
			cin >> graphname;
			cin >> vexname;
			cin >> vexname2;
			if (index.GraphExist(graphname) >= 0) {
				if (vexname == vexname2) {
					cout << "无法在一个节点上创建弧" << endl;
				}
				else if (index.VexExist(graphname, vexname) && index.VexExist(graphname, vexname2)) {
					if (index.InsertArc(graphname, vexname, vexname2) == OK) {
						cout << "成功插入" << endl;
					}
					else
						cout << "插入失败" << endl;
				}
				else
					cout << "目标图中不存在顶点" << vexname << "或" << vexname2 << endl;
			}
			else {
				cout << "目标图不存在" << endl;
			}
			break;
		case 11:
			cout << "请输入要删除的弧所在图的名称以及两个顶点的名称" << endl;
			cin >> graphname;
			cin >> vexname;
			cin >> vexname2;
			if (vexname != vexname2) {
				if (index.VexExist(graphname, vexname) && index.VexExist(graphname, vexname2)) {
					if (index.DeleteArc(graphname, vexname, vexname2) == OK) {
						cout << "成功删除" << endl;
					}
					else
						cout << "删除失败" << endl;
				}
				else
					cout << "目标图中不存在顶点" << vexname << "或" << vexname2 << endl;
			}
			else {
				cout << "节点相同 删除失败" << endl;
			}
			
			break;
		case 12:
			cout << "请输入要进行深度优先遍历的图的名称" << endl;
			cin >> graphname;
			cout << "遍历结果为：" << endl;
			if (index.GraphExist(graphname) >= 0) {
				index.Clearvisited(graphname);
				index.DFSTraverse(graphname, visit);
				cout << endl;
			}
			else
				cout << "目标图不存在" << endl;
			break;
		case 13:
			cout << "请输入要进行广度优先遍历的图的名称" << endl;
			cin >> graphname;
			cout << "遍历结果为：" << endl;
			if (index.GraphExist(graphname) >= 0) {
				index.Clearvisited(graphname);
				index.BFSTraverse(graphname, visit);
				cout << endl;
			}
			else
				cout << "目标图不存在" << endl;
			break;
		case 14:
			index.SaveData();
			cout << "保存成功" << endl;
			break;
		case 15:
			index.LoadData();
			cout << "导入成功" << endl;
		case 16:
			index.PrintTable();
			break;
		default:
			op = 0;
			break;
		}
	}
	
	return 0;
}