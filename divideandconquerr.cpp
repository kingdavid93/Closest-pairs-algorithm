#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <ctime>
#include <stdexcept>

using namespace std;

struct Point {
    int x, y;
};

double calculateDistance(const Point &p1, const Point &p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void merge(vector<Point>& points, int left, int mid, int right, bool byX) {
    int n1 = mid - left;
    int n2 = right - mid;
    
    vector<Point> L(points.begin() + left, points.begin() + mid);
    vector<Point> R(points.begin() + mid, points.begin() + right);
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (byX) {
            if (L[i].x <= R[j].x) {
                points[k] = L[i];
                i++;
            } else {
                points[k] = R[j];
                j++;
            }
        } else {
            if (L[i].y <= R[j].y) {
                points[k] = L[i];
                i++;
            } else {
                points[k] = R[j];
                j++;
            }
        }
        k++;
    }
    
    while (i < n1) {
        points[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        points[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Point>& points, int left, int right, bool byX) {
    if (right - left <= 1) return;
    
    int mid = left + (right - left) / 2;
    mergeSort(points, left, mid, byX);
    mergeSort(points, mid, right, byX);
    merge(points, left, mid, right, byX);
}

pair<Point, Point> stripClosest(vector<Point> &strip, double d, pair<Point, Point> closestPair) {
    double minDist = d;
    
    mergeSort(strip, 0, strip.size(), false);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < min(i + 8, strip.size()) && (strip[j].y - strip[i].y) < minDist; ++j) {
            double dist = calculateDistance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                closestPair = {strip[i], strip[j]};
            }
        }
    }
    return closestPair;
}

pair<Point, Point> closestUtil(vector<Point> &points, int left, int right) {
    if (right - left <= 3) {
        double minDist = DBL_MAX;
        pair<Point, Point> closestPair = {points[left], points[left + 1]};
        
        for (int i = left; i < right - 1; ++i) {
            for (int j = i + 1; j < right; ++j) {
                double dist = calculateDistance(points[i], points[j]);
                if (dist < minDist) {
                    minDist = dist;
                    closestPair = {points[i], points[j]};
                }
            }
        }
        return closestPair;
    }

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    auto leftPair = closestUtil(points, left, mid);
    auto rightPair = closestUtil(points, mid, right);

    double leftDist = calculateDistance(leftPair.first, leftPair.second);
    double rightDist = calculateDistance(rightPair.first, rightPair.second);

    double d = min(leftDist, rightDist);
    auto closestPair = (d == leftDist) ? leftPair : rightPair;

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    return stripClosest(strip, d, closestPair);
}

pair<Point, Point> closestPair(vector<Point> &points) {    
    mergeSort(points, 0, points.size(), true);
    return closestUtil(points, 0, points.size());
}

int main() {
    string filename;
    cout << "Enter the input file name: ";
    cin >> filename;

    ifstream file(filename);

    vector<Point> points;
    Point temp;
    while (file >> temp.x >> temp.y) {
        points.push_back(temp);
    }
    file.close();

    clock_t start = clock();
    auto [p1, p2] = closestPair(points);
    double minDistance = calculateDistance(p1, p2);
    clock_t end = clock();
    double timeTaken = double(end - start) / CLOCKS_PER_SEC;

    cout << "Closest pair: (" << p1.x << ", " << p1.y << ") and ("
              << p2.x << ", " << p2.y << ")" << endl;
    cout << "Time taken: " << timeTaken << " seconds" << endl;

    return 0;
}
