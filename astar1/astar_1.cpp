#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
/*˼·������ڵ�ṹ->A*�㷨������->point�����ϣ->��ͼ��ά->�������յ��ϰ���*/
//��������==
//�����ά����
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

//��Point�����ϣ
struct Point {
	int x, y;
	Point(int x, int y) : x(x), y(y) {}
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}


struct Node {
	Point pos();
	double h;//��������
	double g;//ʵ�ʴ���
	double f;//�ܴ���
	Node* parent;

	Node(Point p,double g,double h,double f,
};