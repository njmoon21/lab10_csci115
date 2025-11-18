#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

using namespace std;

struct Edge {
    int a, b;      // cell ids
    int weight;    // random priority
};

long long encodeEdge(int a, int b) {
    if (a > b) swap(a, b);
    return ((long long)a << 32) | (long long)b;
}

vector<int> parentUF;
vector<int> rankUF;

// TODO: Implement Find(x)
int Find(int x) {
    // TODO
    return 0;
}

// TODO: Implement Union(a, b)
void Union(int a, int b) {
    // TODO
}

// TODO: Build the list of edges for an R x C grid
void buildEdges(int R, int C, vector<Edge>& edges) {
    // TODO
}

// TODO: Run Kruskal’s algorithm and fill 'used'
void runKruskal(int R, int C, vector<Edge>& edges,
                unordered_set<long long>& used) {
    // TODO
}

// Provided ASCII printing (students do NOT modify this)
void printMaze(const unordered_set<long long>& used, int R, int C) {
    for (int c = 0; c < C * 2 + 1; c++) cout << '#';
    cout << "\n";

    for (int r = 0; r < R; r++) {
        cout << "#";
        for (int c = 0; c < C; c++) {
            int id = r * C + c;
            cout << ".";

            if (c + 1 < C) {
                long long k = encodeEdge(id, id + 1);
                if (used.count(k)) cout << ".";
                else cout << "#";
            } else {
                cout << "#";
            }
        }
        cout << "\n";

        cout << "#";
        for (int c = 0; c < C; c++) {
            int id = r * C + c;
            if (r + 1 < R) {
                long long k = encodeEdge(id, id + C);
                if (used.count(k)) cout << ".#";
                else cout << "##";
            } else {
                cout << "##";
            }
        }
        cout << "\n";
    }
}

int main() {
    srand(time(NULL));

    int R = 10;
    int C = 20;
    int N = R * C;

    parentUF.resize(N);
    rankUF.resize(N, 0);

    for (int i = 0; i < N; i++) {
        parentUF[i] = i;
    }

    vector<Edge> edges;
    unordered_set<long long> used;

    buildEdges(R, C, edges);
    runKruskal(R, C, edges, used);

    printMaze(used, R, C);

    return 0;
}
