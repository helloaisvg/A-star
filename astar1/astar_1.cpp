#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
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
namespace std {
	template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };

	//����ڵ�ṹ��
struct Node {
        Point pos;
		double h;//��������
		double g;//ʵ�ʴ���
		double f;//�ܴ���
		Node* parent;

		Node(Point pos, double g, double h, double f, Node* parent = nullptr) :pos(pos), g(g), h(h), f(f), parent(parent) {};
		bool operator<(const Node& other) const{
			return f > other.f;

	}

		//A*�㷨ʵ��
		class Astar {
		private:
			//����ͼ
			vector<vector<int>> grid;
			int width, height;
		public:
			vector<int> closed;
			vector<int> open;
			Astar(int width, int height) : width(width), height(height) {
				grid.resize(height, vector<int>(width, 0));
			}
			//��������ϰ���
			void generateObstacles(int numObstacles) {
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dis(0, width - 1);
				for (int i = 0; i < numObstacles; ++i) {
					int x = dis(gen);
					int y = dis(gen);
					grid[y][x] = 1;
				}
			}
			//
			//�����������յ�
			void generateStartEnd(Point& start, Point& end) {
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dis(0, width - 1);
				start = Point(dis(gen), dis(gen));
				end = Point(dis(gen), dis(gen));
			}
			//����ʽ����
			double heuristic(Point a, Point b) {
				return abs(a.x - b.x) + abs(a.y - b.y);
			}
			//�жϵ��Ƿ��ڷ�Χ��
			bool inBounds(Point p) {
				return p.x >= 0 && p.x < width && p.y >= 0 && p.y < height;
			}
			//�����
			vector<Point> getnighbors(Point p) {
				vector<Point> neighbors;
				vector<Point> directions = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };
				for (const auto& dir : directions) {
					Point neighbor(p.x + dir.x, p.y + dir.y);
					if (inBounds(neighbor) && grid[neighbor.y][neighbor.x] == 0) {
						neighbors.push_back(neighbor);
					}
				}
				return neighbors;

				//A*�㷨������
				vector<Point> findPath(const Point & start, const Point & end) {
					//�������ȶ���,open
					priority_queue<Node, vector<Node>, greater<Node>> openSet;
					//�ѷ��ʼ���closed
					unordered_set<Point> closed;
					//��¼�ڵ��g
					vector<vector<double>> gvalues(height, vector<double>(width, INT16_MAX));
					//����ʼ��
					int h = heuristic(start, end);
					openSet.push(Node(start, 0, h));
					gValues[start.x][start.y];

					while (!openSet.empty()) {
						Node current = openSet.top();
						openSet.pop();//��ȡfֵ��С�Ľڵ�
						//�����յ������·��
						if (current.pos == end) {//��������յ����·��
							vector<point>path;
							Node* node = &current;
							while (node != nullptr) {
								path.push_back(node->pos);
								node = node->parent;

							}
							reverse(path.begn(), path.end());
							return path;

						}
						closedSet.insert(current.pop);//�ɵ�ǰ�ڵ������̽��
						//̽���ھӽڵ�
						for (auto& neighborPos : getNeighbors(current.pos)) {
							if (closedSet.count(neighborPos))
								continue;//������̽����������
							//������g
							int tentativeG = current.g + 1//������ÿ��������1

								if (testG < gValues[neighborsPos.x][neighborPos.y) {
									gValues[neighborPos.x][neighborPos.y] = testG;
									int h = heuristic(neighborPos, end);
									openSet.push(Node(neighborPos, testG, h, new Node(current)));
								}
						}
					}

			
					return {};//û���ҵ�·��
				}
					void printMap(Point & start, Point & end, vector<Point>&path = {}){
						unordered_set<Point>



			}

        

		
