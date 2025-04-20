#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
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
namespace std {
	template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };

	//定义节点结构体
struct Node {
        Point pos;
		double h;//启发函数
		double g;//实际代价
		double f;//总代价
		Node* parent;

		Node(Point pos, double g, double h, double f, Node* parent = nullptr) :pos(pos), g(g), h(h), f(f), parent(parent) {};
		bool operator<(const Node& other) const{
			return f > other.f;

	}

		//A*算法实现
		class Astar {
		private:
			//定义图
			vector<vector<int>> grid;
			int width, height;
		public:
			vector<int> closed;
			vector<int> open;
			Astar(int width, int height) : width(width), height(height) {
				grid.resize(height, vector<int>(width, 0));
			}
			//随机生成障碍物
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
			//随机生成起点终点
			void generateStartEnd(Point& start, Point& end) {
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> dis(0, width - 1);
				start = Point(dis(gen), dis(gen));
				end = Point(dis(gen), dis(gen));
			}
			//启发式函数
			double heuristic(Point a, Point b) {
				return abs(a.x - b.x) + abs(a.y - b.y);
			}
			//判断点是否在范围内
			bool inBounds(Point p) {
				return p.x >= 0 && p.x < width && p.y >= 0 && p.y < height;
			}
			//邻域点
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

				//A*算法主函数
				vector<Point> findPath(const Point & start, const Point & end) {
					//定义优先队列,open
					priority_queue<Node, vector<Node>, greater<Node>> openSet;
					//已访问集合closed
					unordered_set<Point> closed;
					//记录节点的g
					vector<vector<double>> gvalues(height, vector<double>(width, INT16_MAX));
					//起点初始化
					int h = heuristic(start, end);
					openSet.push(Node(start, 0, h));
					gValues[start.x][start.y];

					while (!openSet.empty()) {
						Node current = openSet.top();
						openSet.pop();//获取f值最小的节点
						//到达终点则回溯路径
						if (current.pos == end) {//如果到达终点回溯路径
							vector<point>path;
							Node* node = &current;
							while (node != nullptr) {
								path.push_back(node->pos);
								node = node->parent;

							}
							reverse(path.begn(), path.end());
							return path;

						}
						closedSet.insert(current.pop);//吧当前节点加入已探索
						//探索邻居节点
						for (auto& neighborPos : getNeighbors(current.pos)) {
							if (closedSet.count(neighborPos))
								continue;//已在已探索集合跳过
							//计算新g
							int tentativeG = current.g + 1//这里设每步代价是1

								if (testG < gValues[neighborsPos.x][neighborPos.y) {
									gValues[neighborPos.x][neighborPos.y] = testG;
									int h = heuristic(neighborPos, end);
									openSet.push(Node(neighborPos, testG, h, new Node(current)));
								}
						}
					}

			
					return {};//没有找到路径
				}
					void printMap(Point & start, Point & end, vector<Point>&path = {}){
						unordered_set<Point>



			}

        

		
