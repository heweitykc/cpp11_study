#ifndef __ROAD_SERACH_H__
#define __ROAD_SERACH_H__

#include <list>


using namespace std;

/*
节点(node)：
	本质上就是方形网格里的某一个方格（yujjj 注：为什么不把他们描述为方格？
	因为在一些时候划分的节点不一定是方形的，矩形、六角形、或其它任意形状，本书中只讨论方格）。
	由此可以看出，路径将会由起点节点，终点节点，还有从起点到终点经过的节点组成。

代价(cost)：
	这是对节点优劣分级的值。代价小的节点肯定比代价大节点更好。代价由两部
	分组成：从起点到达当前点的代价和从这个点到终点的估计代价。代价一般由变量 f，g 和 h，具体如下。 
	f：特定节点的全部代价。由 g+h 决定。 
	g：从起点到当前点的代价。它是确定的，因为你肯定知道从起点到这一点的实际路径。 
	h：从当前点到终点的估计代价。是用估价函数（heuristic function）计算的。它只能一个估算，因为你不知道具体的路线—你将会找出的那一条

估价函数(heuristic)：
	计算从当前点到终点估计代价的公式。通常有很多这样的公式，但他们的运算结果，速度等都有差异
	（注：估价公式计算的估计值越接近实际值，需要计算的节点越少；估价公式越简单，每个节点的计算速度越快）。

待考察表(open list)：
	一组已经估价的节点。表里代价最小的节点将是下一次的计算的起点。

已考察表(closed list)：
	从待考察表中取代价最小的节点作为起点，对它周围 8 个方向的节点进行估价，然后把它放入“已考察表”。

父节点(parent node)：
	以一个点计算周围节点时，这个点就是其它节点的父节点。当我们到达终点节点，
	你可以一个一个找出父节点直到起点节点。因为父节点总是带考察表里的小代价节点，这样可以确保你找出最佳路线。

算法：
1. 添加起点节点到待考察表 
2. 主循环 
	a. 找到待考察表里的最小代价的节点，设为当前节点。 
	b. 如果当前点是终点节点，你已经找到路径了。跳到第四步。 
	c. 考察每一个邻节点（直角坐标网格里，有 8 个这样的节点 ）对于每一个邻节点： 
		(1).如果是不能通过的节点，或者已经在带考察表或已考察表中，跳过，继续下一节点，否则继续。 
		(2).计算它的代价 
		(3).把当前节点定义为这个点的父节点添加到待考察表 
		(4).添加当前节点到已考察表 
3. 更新待考察表，重复第二步。 
4. 你已经到达终点，创建路径列表并添加终点节点 
5. 添加终点节点的父节点到路径列表 
6. 重复添加父节点直到起点节点。路径列表就由一组节点构成了最佳路径

*/

struct Node
{
	int x,y;
	float f,g,h;
	int pid;	
	float costMultiplier;
	Node* parent;
};

inline
bool greater_f( const Node* a, const Node* b )
{ return a->f < b->f; }

class RoadSearch
{
public:	
	static const int WIDTH =  18;
	static const int HEIGHT = 18;

	void init();
	void update(int x,int y,int pid);	//pid=(0表示可行, 1-10表示战斗单位, 11表示障碍)
	bool findPath(int startx, int starty, int endx, int endy);
	bool search();
private:
	Node  _roads[WIDTH][HEIGHT];
	Node* _startNode;
	Node* _endNode;
	list<Node*> _open;
	list<Node*> _closed;
	list<Node*> _path;

	float _straightCost = 1.0f;
	float _diagCost = 1.4142135623730951f;
	
	float euclidian(Node* node);
	float diagonal(Node* node);
	bool isOpen(Node* node);
	bool isClosed(Node* node);
	void buildPath();
};

#endif