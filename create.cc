#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

void createPoints(string &filename, int n) {
    ofstream file;
    file.open(filename);
    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        file << rand() % 20001 - 10000 << " " << rand() % 20001 - 10000 << endl;
    }
    file.close();
}

int main() {
    int n;
    cout << "Enter number of points: ";
    cin >> n;
    string filename = "output" + to_string(n) + ".txt";
    createPoints(filename, n);
    return 0;
}
    
