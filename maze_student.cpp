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
int Find(const int x) {
    if (parentUF[x] != x) // If it's not pointing to itself, then it means that it's not the root
            parentUF[x] = Find(parentUF[x]); // Recursing up the tree, we'll eventually get to the root

    return parentUF[x];
}

// TODO: Implement Union(a, b)
void Union(int a, int b) {
    int findA = Find(a);
    int findB = Find(b);

    // If the rank of a node is smaller than another node's rank, then add smaller node under bigger ranked node
    if (rankUF[findA] < rankUF[findB])
        parentUF[findA] = findB;
    else if (rankUF[findA] > rankUF[findB])
        parentUF[findB] = findA;
    else {
        parentUF[findB] = findA;
        rankUF[findA]++;
    }
}

// TODO: Build the list of edges for an R x C grid
void buildEdges(int R, int C, vector<Edge>& edges) {
    /* Notes:
     * Each cell has up to 2 edges:
     * - Right neighbor (r, c+1)
     * - Down neighbor (r+1, c)
     */


    for (int row = 0; row < R; row++) { // Going to iterate through each row
        for (int column = 0; column < C; column++) { // Then iterating through each column per row
            int id = row * C + column; //

            // Keep adding neighbors until we reach the end/wall of the maze
            // This section adds the right neighbors
            if (column + 1 < C) { // If we aren't out of bounds, add a neighbor ; otherwise don't add edge
                Edge newEdge;
                newEdge.a = id;
                newEdge.b = id + 1; // The right neighbor is the next cell in the 2D grid
                newEdge.weight = rand();
                edges.push_back(newEdge);
            }

            // This section adds the bottom neighbors
            if (row + 1 < R) { // If we aren't out of bounds, add a neighbor ; otherwise don't add edge
                Edge newEdge;
                newEdge.a = id;
                // Was confused why 'id + C' would make it traverse down by one row, but I think if it like it wraps around to the next row
                newEdge.b = id + C; // The bottom neighbor is going DOWN the column
                newEdge.weight = rand();
                edges.push_back(newEdge);
            }
        }
    }
}

// TODO: Run Kruskal’s algorithm and fill 'used'
void runKruskal(int R, int C, vector<Edge>& edges, unordered_set<long long>& used) {
    // I tried using the built-in vector sort() function, however it didn't work. Using insertion sort
    // 1. Sort edges by weight
    for (int i = 1; i < edges.size(); i++) {
        Edge keyEdge = edges[i];
        int j = i - 1;

        while (j >= 0 && edges[j].weight > keyEdge.weight) {
            edges[j + 1] = edges[j];
            j--;
        }
        edges[j + 1] = keyEdge;
    }

    // 2. Iterate through each edge after it has been sorted
    for (auto edge : edges) {
        // 3.
        if (Find(edge.a) != Find(edge.b)) {
            used.insert(encodeEdge(edge.a, edge.b));
            Union(edge.a, edge.b);

            // 4. Stop when you have selected R*C - 1 edges
            if (used.size() == R * C - 1)
                break;
        }
    }
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
