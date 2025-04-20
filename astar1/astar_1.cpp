#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <random>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;

// 定义二维坐标
struct Point {
    int x, y;
    //添加默认构造函数
    Point() :x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
	
};

// 给Point定义哈希
namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
}

// 定义节点结构体
struct Node {
    Point pos;
    double g;  // 实际代价
    double h;  // 启发函数
    double f;  // 总代价
    Node* parent;

    Node(Point pos, double g, double h, Node* parent = nullptr)
        : pos(pos), g(g), h(h), f(g + h), parent(parent) {
    };

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

// A*算法实现
class Astar {
private:
    // 定义图
    vector<vector<int>> grid;
    int width, height;
public:
			vector<int> closed;
			vector<int> open;
    Astar(int width, int height) : width(width), height(height) {
        grid.resize(height, vector<int>(width, 0));
    }

    // 随机生成障碍物
    void generateObstacles(double obstacleDensity) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0.0, 1.0);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (dis(gen) < obstacleDensity) {
                    grid[y][x] = 1;
                }
            }
        }
    }

    // 随机生成起点终点
    void generateStartEnd(Point& start, Point& end) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, width - 1);

        do {
            start = Point(dis(gen), dis(gen));
        } while (grid[start.y][start.x] == 1);

        do {
            end = Point(dis(gen), dis(gen));
        } while (grid[end.y][end.x] == 1 || end == start);
    }

    // 启发式函数
    double heuristic(const Point& a, const Point& b) const{
        return abs(a.x - b.x) + abs(a.y - b.y);  // 曼哈顿距离
    }

    // 判断点是否在范围内
    bool inBounds(const Point& p) const{
        return p.x >= 0 && p.x < width && p.y >= 0 && p.y < height;
    }

  /* // 获取邻居点
//<<<<<<< HEAD
    vector<Point> getNeighbors(const Point& p) const{
//=======
    //vector<Point> getNeighbors(Point p) {
//>>>>>>> 857fe1b1e7fca650de0a710ef35eabcd16423da7
        vector<Point> neighbors;
        const vector<Point> directions = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0) };
        for (const auto& dir : directions) {
            Point neighbor(p.x + dir.x, p.y + dir.y);
            if (inBounds(neighbor) && grid[neighbor.y][neighbor.x] == 0) {
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }*/
    vector<Point> getNeighbors(const Point& p) const {  // 添加const限定符
        vector<Point> neighbors;
        const vector<Point> directions = { {0,1}, {1,0}, {0,-1}, {-1,0} };
        for (const auto& dir : directions) {
            Point neighbor(p.x + dir.x, p.y + dir.y);
            if (inBounds(neighbor) && grid[neighbor.y][neighbor.x] == 0) {
                neighbors.push_back(neighbor);
            }
        }
        return neighbors;
    }

    // A*算法主函数
    vector<Point> findPath(const Point& start, const Point& end) {
        // 定义优先队列,open
        priority_queue<Node, vector<Node>, greater<Node>> openSet;
        // 已访问集合closed
        unordered_set<Point> closedSet;
        // 记录节点的g值
        vector<vector<double>> gValues(height, vector<double>(width, INT_MAX));

        // 起点初始化
        double h = heuristic(start, end);
        openSet.push(Node(start, 0, h));
        gValues[start.y][start.x] = 0;

        while (!openSet.empty()) {
            Node current = openSet.top();
            openSet.pop();  // 获取f值最小的节点

            // 到达终点则回溯路径
            if (current.pos == end) {
                vector<Point> path;
                Node* node = &current;
                while (node != nullptr) {
                    path.push_back(node->pos);
                    node = node->parent;

                }
                reverse(path.begin(), path.end());
                return path;
            }

            closedSet.insert(current.pos);  // 把当前节点加入已探索

            // 探索邻居节点
            for (auto& neighborPos : getNeighbors(current.pos)) {
                if (closedSet.count(neighborPos))
                    continue;  // 已在已探索集合跳过

                // 计算新g
                double tentativeG = current.g + 1;  // 这里设每步代价是1

                if (tentativeG < gValues[neighborPos.y][neighborPos.x]) {
                    gValues[neighborPos.y][neighborPos.x] = tentativeG;
                    double h = heuristic(neighborPos, end);
                    openSet.push(Node(neighborPos, tentativeG, h, new Node(current)));
                }
            }
        }

        return {};  // 没有找到路径
    }

    void printMap(const Point& start, const Point& end, const vector<Point>& path = {}) {
        unordered_set<Point> pathSet(path.begin(), path.end());
        cout << "Map (S=Start, E=End, #=Obstacle, .=Path, O=Open):\n";
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Point p(x, y);
                if (p == start)
                    cout << "S ";
                else if (p == end)
                    cout << "E ";
                else if (pathSet.count(p))
                    cout << ". ";
                else if (grid[y][x] == 1)
                    cout << "# ";
                else
                    cout << "O ";
            }
            cout << endl;
        }
    }
};

int main() {
    int width = 15;
    int height = 10;

    Astar astar(width, height);

    // 随机生成障碍物
    astar.generateObstacles(0.30);  // 设置30%障碍物密度

    Point start, end;
    astar.generateStartEnd(start, end);

    cout << "Start: (" << start.x << ", " << start.y << ")\n";
    cout << "End: (" << end.x << ", " << end.y << ")\n\n";

    // 打印初始地图
    astar.printMap(start, end);

    // 查找路径
    auto startTime = chrono::high_resolution_clock::now();
    vector<Point> path = astar.findPath(start, end);
    auto endTime = chrono::high_resolution_clock::now();

    // 输出结果
    if (!path.empty()) {
        cout << "\nPath found ("
            << chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count()
            << "ms):\n";
        astar.printMap(start, end, path);

        cout << "\nPath:\n";
        for (const auto& p : path) {
            cout << "(" << p.x << ", " << p.y << ") ";
        }
        cout << endl;
    }
    else {
        cout << "\nNo path found!" << endl;
    }

    return 0;
}