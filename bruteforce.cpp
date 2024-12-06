#include <iostream>
#include <fstream>
#include <cmath>
#include <cfloat>
#include <vector>
#include <ctime>


using namespace std;

struct Point {
    int x, y;
};

double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

vector<Point> bruteForce(const vector<Point>& points) {
    double minDistance = DBL_MAX;
    int psize = points.size();
    Point p1, p2;
    
    for (int i = 0; i < psize - 1; i++) {
        for (int j = i + 1; j < psize; j++) {
            double dist = calculateDistance(points[i], points[j]);
            if (dist < minDistance) {
                minDistance = dist;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    
    vector<Point> minPoints;
    minPoints.push_back(p1);
    minPoints.push_back(p2);
    return minPoints;
}

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;


    ifstream file(filename);

    vector<Point> points;
    Point point;
    while (file >> point.x >> point.y) {
        points.push_back(point);
    }
    file.close();

    
    clock_t start = clock();
    vector<Point> closestPoints = bruteForce(points);
    clock_t end = clock();

    cout << "Closest pair: (" << closestPoints[0].x << ", " 
         << closestPoints[0].y << ") and (" 
         << closestPoints[1].x << ", " << closestPoints[1].y << ")" << endl;
    cout << "Time taken: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}