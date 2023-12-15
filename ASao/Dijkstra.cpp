﻿// ASao.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

        /*int x;
        for (int i = 0; i < v; i++) {
            cin >> x;
            h[i] = x;
        }*/

        /*for (int i = 0; i < e; i++) {
            cin >> s >> t >> x;
            matrix[VertexNameToIndex[s]][VertexNameToIndex[t]] = x;
        }*/
        int x;
        for (int i = 0; i < v; i++) {
            for (int j = 0; j < v; j++) {
                cin >> x;
                matrix[i][j] = x;
            }
        }
    }
    void process(int v, int n) {
        string s, t;
        for (int i = 0; i < n; i++) {
            cin >> s >> t;
            AStar(VertexNameToIndex[s], VertexNameToIndex[t], v);
        }
    }

    void AStar(int s, int u, int v) {
        vector<bool> close(v, 0); // danh sÃ¡ch cÃ¡c Äá»nh ÄÃ£ visit
        vector<int> g(v, INT16_MAX); // danh sÃ¡ch khoáº£ng cÃ¡ch cá»§a cÃ¡c Äá»nh
        vector<int> f(v, INT16_MAX); // danh sÃ¡ch Äá» tá»t cá»§a cÃ¡c Äá»nh
        map<string, string> parent;
        vector<bool> isOpenVisited(v, false);
        auto cmp = [&](pair<int, int> a, pair<int, int> b)
            {
                if (a.first < b.first)
                {
                    return false;
                }
                if (a.first == b.first)
                {
                    return a.second < b.second;
                }
                return true;
            };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> open(cmp);
        f[s] = 0;
        g[s] = 0;

        open.push(make_pair(0, s)); // thÃªm Äiá»m xuáº¥t phÃ¡t vÃ o open
        bool FoundFlag = false;
        isOpenVisited[s] = true;
        while (!open.empty()) {
            int p = open.top().second;
            int curDis = open.top().first;
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
                    if (close[q] == 0) {
                        if (g[q] > g_new) {
                            g[q] = g_new;
                            parent[v_list[q]] = v_list[p];
                            f[q] = g[q] + h[q];
                            open.push(make_pair(f[q], q));
                            isOpenVisited[q] = true;

                        }
                    }
                    //else if (isOpenVisited[q] == true) {
                    //    if (g[q] >= g_new) {
                    //        g[q] = g_new;
                    //        f[q] = g[q] + h[q];
                    //        parent[v_list[q]] = v_list[p];
                    //        /*open.pop();*/
                    //        /*open.push(make_pair(f[q], q));*/
                    //    }
                    //}
                    //else if (close[q] == 1) {
                    //    if (g[q] >= g_new) {
                    //        close[q] = 0;
                    //        g[q] = g_new;
                    //        f[q] = g[q] + h[q];
                    //        parent[v_list[q]] = v_list[p];
                    //        /*open.pop();*/
                    //        /*open.push(make_pair(f[q], q));*/
                    //        // cap nhap su thay doi cac dinh chiu anh huong cua su thay doi tu q
                    //    }
                    //}
                }

            }
        }
        // tÃ­nh sá» Äá»nh ÄÃ£ má» rá»ng
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
    /*cin >> s >> u;*/
    Graph G;
    G.init(v);
    G.initGraph(v, e);
    /*G.AStar(G.VertexNameToIndex[s], G.VertexNameToIndex[u], v);*/
    G.process(v, e);
}

// CÃ³ tham kháº£o chat gpt pháº§n lÃ m láº¡i priority queue