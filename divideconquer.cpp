#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <ctime>

using namespace std;

struct Point {
    int x, y;
};

double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void merge(vector<Point>& points, int l, int m, int r, bool x) {
    vector<Point> temp(r - l);
    int i = l, j = m, k = 0;
    
    while (i < m && j < r) {
        if ((x && points[i].x <= points[j].x) || 
            (!x && points[i].y <= points[j].y)) {
            temp[k++] = points[i++];
        } else {
            temp[k++] = points[j++];
        }
    }
    
    while (i < m) temp[k++] = points[i++];
    while (j < r) temp[k++] = points[j++];
    
    for (i = 0; i < k; i++) {
        points[l + i] = temp[i];
    }
}

void mergeSort(vector<Point>& points, int l, int r, bool x) {
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    mergeSort(points, l, m, x);
    mergeSort(points, m, r, x);
    merge(points, l, m, r, x);
}

vector<Point> quickClosestPair(vector<Point>& points, int l, int r) {
    if (r - l <= 3) {
        double minDistance = DBL_MAX;
        vector<Point> closest(2);
        for (int i = l; i < r - 1; i++) {
            for (int j = i + 1; j < r; j++) {
                double dist = calculateDistance(points[i], points[j]);
                if (dist < minDistance) {
                    minDistance = dist;
                    closest[0] = points[i];
                    closest[1] = points[j];
                }
            }
        }
        return closest;
    }

    int m = (l + r) / 2;
    int c = points[m].x;

    auto lPair = quickClosestPair(points, l, m);
    auto rPair = quickClosestPair(points, m, r);

    double d1 = calculateDistance(lPair[0], lPair[1]);
    double d2 = calculateDistance(rPair[0], rPair[1]);
    double d = min(d1, d2);
    vector<Point> closest = (d1 < d2) ? lPair : rPair;

    vector<Point> C1, C2;
    for (int i = l; i < r; i++) {
        if (abs(points[i].x - c) < d) {
            if (points[i].x <= c) {
                C1.push_back(points[i]);
            } else {
                C2.push_back(points[i]);
            }
        }
    }

    mergeSort(C1, 0, C1.size(), false);
    mergeSort(C2, 0, C2.size(), false);

    for (size_t i = 0; i < C1.size(); i++) {
        for (size_t j = i + 1; j < C1.size() && (C1[j].y - C1[i].y) < d; j++) {
            double dist = calculateDistance(C1[i], C1[j]);
            if (dist < d) {
                d = dist;
                closest[0] = C1[i];
                closest[1] = C1[j];
            }
        }
    }

    for (size_t i = 0; i < C2.size(); i++) {
        for (size_t j = i + 1; j < C2.size() && (C2[j].y - C2[i].y) < d; j++) {
            double dist = calculateDistance(C2[i], C2[j]);
            if (dist < d) {
                d = dist;
                closest[0] = C2[i];
                closest[1] = C2[j];
            }
        }
    }

    for (const Point& p : C1) {
        for (const Point& q : C2) {
            if (abs(p.y - q.y) >= d) continue;
            double dist = calculateDistance(p, q);
            if (dist < d) {
                d = dist;
                closest[0] = p;
                closest[1] = q;
            }
        }
    }
    return closest;
}

vector<Point> findClosestPair(vector<Point>& points) {
    mergeSort(points, 0, points.size(), true);
    return quickClosestPair(points, 0, points.size());
}

int main() {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;

    ifstream file(filename);

    vector<Point> points;
    Point p;
    while (file >> p.x >> p.y) {
        points.push_back(p);
    }

    clock_t start = clock();
    vector<Point> closest = findClosestPair(points);
    clock_t end = clock();
        
    cout << "Closest pair: (" << closest[0].x << "," << closest[0].y << ") and ("
             << closest[1].x << "," << closest[1].y << ")\n";
    cout << "Time: " << double(end - start)/CLOCKS_PER_SEC << " seconds\n";

}