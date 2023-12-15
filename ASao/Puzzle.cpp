// ASao.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>
using namespace std;
class Graph {
public:
    vector<vector<int>> matrix;
    vector<string> v_list;
    map<string, int> VertexNameToIndex;
    vector<int> h;

public:
    void init(int v) {
        matrix = vector<vector<int>>(v, vector<int>(v));
        v_list = vector<string>(v, "");
        h = vector<int>(v, 0);
    }

    void initGraph(int v, int e) {
        string s, t;

        for (int i = 0; i < v; i++) {
            cin >> s;
            v_list[i] = s;
            VertexNameToIndex[s] = i;

        }

        int x;
        for (int i = 0; i < v; i++) {
            cin >> x;
            h[i] = x;
        }

        for (int i = 0; i < e; i++) {
            cin >> s >> t >> x;
            matrix[VertexNameToIndex[s]][VertexNameToIndex[t]] = x;
        }
       
    }
    void process(int v, int n) {
        string s, t;
        for (int i = 0; i < n; i++) {
            cin >> s >> t;
            AStar(VertexNameToIndex[s], VertexNameToIndex[t], v);
        }
    }
    int countH(int row, int col) {

    }
    void AStar(int s, int u, int v) {
        vector<bool> close(v, 0); // danh sach cac dinh da visit
        vector<int> g(v, INT16_MAX); // danh ssach khoang cach cac dinh
        vector<int> f(v, -1); // danh sach cac do tot
        map<string, string> parent;
        vector<bool> isOpenVisited(v, false);
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> open;
        f[s] = h[s];
        g[s] = 0;

        open.push(make_pair(h[s], s)); // them dinh xuat phat vao open
        bool FoundFlag = false;
        isOpenVisited[s] = true;
        while (!open.empty()) {
            int p = open.top().second;
            int curDis = g[p];
            open.pop();
            close[p] = 1;
            if (p == u) {
                // ket thuc thuat toan
                FoundFlag = true;
                break;
            }

            for (int q = v - 1; q >= 0; q--) {
                int weight = matrix[p][q];


                if (weight > 0) {
                    int g_new = curDis + weight;
                    if (close[q] == 0 && isOpenVisited[q] == false) {
                        if (g[q] > g_new) {
                            g[q] = g_new;
                            parent[v_list[q]] = v_list[p];
                            f[q] = g[q] + h[q];
                            open.push(make_pair(f[q], q));
                            isOpenVisited[q] = true;

                        }
                    }
                    else if (isOpenVisited[q] == true) {
                        if (g[q] > g_new) {
                            g[q] = g_new;
                            f[q] = g[q] + h[q];
                            parent[v_list[q]] = v_list[p];
                            /*open.pop();*/
                            open.push(make_pair(f[q], q));
                        }
                    }
                    
                }

            }
        }
        // tinh so dinh da mo rong
        int countClose = 0;
        for (int i = 0; i < close.size(); i++) {
            if (close[i] == 1) {
                countClose++;
            }
        }
        if (FoundFlag) {
            vector<string> path;
            path.push_back(v_list[u]);
            string cur = v_list[u];
            while (cur != v_list[s]) {
                cur = parent[cur];
                path.push_back(cur);
            }
            for (int i = path.size() - 1; i >= 0; i--)
            {
                cout << path[i] << " ";
            }
            cout << "\n";
            cout << countClose << " " << g[u] << "\n";
        }
        else {
            cout << "-unreachable-" << "\n";
            cout << countClose << " " << 0 << "\n";

        }
    }
};
int main()
{
    int v, e;
    cin >> v >> e;
    string s, u;
    cin >> s >> u;
    Graph G;
    G.init(v);
    G.initGraph(v, e);
    G.AStar(G.VertexNameToIndex[s], G.VertexNameToIndex[u], v);
    /*G.process(v, e);*/
}

// Co tham khao chatgpt phan priority queue