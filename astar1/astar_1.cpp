#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
/*思路：定义节点结构->A*算法主函数->point定义哈希->建图二维->随机起点终点障碍物*/
//定义重载==
//定义二维坐标
struct Point{
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}
	
	bool operator<(const Point& other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
	
};

//给Point定义哈希
struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}


struct Node {
	Point pos();
	double h;//启发函数
	double g;//实际代价
	double f;//总代价
	Node* parent;

	Node(Point p,double g,double h,double f,
};