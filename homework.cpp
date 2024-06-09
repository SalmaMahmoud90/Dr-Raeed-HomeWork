#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
using namespace std;

//Graph : Adjacency array  this graph is written by ((((((((((( Fatena Ahmad && Salma Mahmoud )))))))))))
class Graph {
private:
    vector<set<int>> adjlist; // list for representing graph ****** this line is written by (((( Nour Soliman ))))
    vector<pair<int, int>> edgelist; // list for storing edges
public:
    // constructor to initialize the size of adjlist  this constructor is written by ((((((((( Qousai Salton ))))))))
    Graph(int n = 0) {
        adjlist.resize(n);
    }
    // method to add edges to graph
    void add_edge(int s, int w) {
        adjlist[s].insert(w);
        edgelist.push_back({s, w});
    }
    // method to resize the adjlist  this method is written by ((((((((( Nagham Noufal  ))))))))))
    void resizeAdjList(int newSize) {
        adjlist.resize(newSize);
    }
    // method to get adjlist
    set<int>& getadjlist(int u) {
        return adjlist[u];
    }
    // method to get number of nodes/size of adjlist    
    int getNodeCount() {
        return adjlist.size();
    }
    // method to display the graph
    void printGraph() {
        for (size_t i = 0; i < adjlist.size(); ++i) {
            cout << i << " ";
            for (int neigh : adjlist[i]) {
                cout << neigh << " ";
            }
            cout << "\n";
        }
    }
    // method to get the list of edges  this method is written by ((((((((( zeinab Ghanem  ))))))))))
    vector<pair<int, int>>& getEdges() {
        return edgelist;
    }
    // method to convert the directed graph to undirected graph 
    Graph toUndirected() {
        int n = adjlist.size();
        Graph undirectedGraph(n);
        for (int u = 0; u < n; u++) {
            for (auto v : adjlist[u]) {
                undirectedGraph.add_edge(u, v);
                undirectedGraph.add_edge(v, u);
            }
        }
        return undirectedGraph;
    }
};
// init method    this method is written by (((((((( Salma Mahmoud ))))))) 
void init(Graph& g, vector<int>& state, vector<int>& dfs_num) {
    int size = g.getNodeCount();
    state.assign(size, -1);
    dfs_num.assign(size, -1);
}


// dfs method  this method is written by ((((((( Salma Mahmoud && Fatena Ahmad )))))))) 
void dfs(Graph& g, int v, vector<bool>& in_stack, int& dfs_counter, vector<int>& state, vector<int>& dfs_num, stack<int>& Ostack, stack<int>& Rstack, stack<int>& Rep, vector<pair<int, int>>& tree) {
    state[v] = 0;
    dfs_num[v] = dfs_counter++;
    Ostack.push(v);
    in_stack[v] = true;
    Rstack.push(v); // this line is written by (((( Reem Ghannam ))))
    for (set<int>::const_iterator it = (g.getadjlist(v)).begin(); it != (g.getadjlist(v)).end(); ++it) {
        if (state[*it] == -1) {
            dfs(g, *it, in_stack, dfs_counter, state, dfs_num, Ostack, Rstack, Rep, tree);
            tree.push_back(make_pair(v, *it));
        }
        else if (in_stack[*it]) {
            while (dfs_num[*it] < dfs_num[Rstack.top()]) {
                Rstack.pop();
            }
        }
    }
    state[v] = 1;
    if (v == Rstack.top()) {
        Rep.push(v);
        Rstack.pop();
        int w = -1;
        while (v != w) {
            w = Ostack.top();
            Ostack.pop();
            in_stack[w] = false;
        }
    }
}
// Gabow Algorithm  this method is written by ((((((((( Salma Mahmoud  ))))))))))
bool Cheriyan_Mehlhorn_Gabow(Graph& g) {
    int dfs_counter = 1; // this line is written by ((((((( leen kanaan )))))
    vector<int> comp(g.getNodeCount()), state(g.getNodeCount()), dfs_num(g.getNodeCount());
    stack<int> Ostack, Rstack, Rep; // this line is written by (((((( Rita mestel ))))))
    vector<pair<int, int>> tree;
    vector<bool> in_stack(g.getNodeCount(), false);
    init(g, state, dfs_num); // this line is written by (((((( Zeina Ahmad )))))
    for (int i = 0; i < g.getNodeCount(); i++) {
        if (state[i] == -1)
            dfs(g, i, in_stack, dfs_counter, state, dfs_num, Ostack, Rstack, Rep, tree);
    }
    if (!Rep.empty()) {
        int c = Rep.top();
        Rep.pop();
    }
    return Rep.empty();
}

// method to find element in edges vector  this method is written by ((((((((( Fatena Ahmad  ))))))))))
bool find_edge(vector<pair<int, int>> v, pair<int, int> p) {
    auto i = find(v.begin(), v.end(), p);
    return i != v.end();
}

// DFS algorithm method  this method is written by ((((((((( Fatena Ahmad  ))))))))))
void DFS(Graph& g, vector<pair<int, int>>& tree, vector<pair<int, int>>& back, vector<int>& state, vector<int>& dfs_num) {
    stack<int> ostack, rstack, rep;
    vector<bool> in_stack(g.getNodeCount(), false);
    int dfs_count = 1;
    init(g, state, dfs_num);
    int l = g.getNodeCount();
    for (int i = 0; i < l; ++i) {
        if (state[i] == -1)
            dfs(g, i, in_stack, dfs_count, state, dfs_num, ostack, rstack, rep, tree);
    }
    // find the back edges:
    vector<pair<int, int>> c = g.getEdges();
    int n = c.size();
    for (int i = 0; i < n; i++) {
        if (!find_edge(tree, c[i])) {
            back.push_back(c[i]);
        }
    }
}

// jens_schmidt algorithm  this method is written by ((((((((( Salma Mahmoud && Fatena Ahmad  ))))))))))
bool jens_schmidt(Graph& g) {
    vector<int> dfs_num, state;
    g = g.toUndirected();
    vector<pair<int, int>> tree, back;
    DFS(g, tree, back, state, dfs_num); // this line is written by ((((( Zeina Ahmad )))))
    int n = g.getNodeCount();
    for (int i = 0; i < n; ++i)
        state[i] = -1;
    // find chains :
    vector<int> chain;
    for (int i = 0; i < n; ++i) {
        if (state[i] == -1) {
            stack<int> S;
            S.push(i);
            while (!S.empty()) {
                int v = S.top();
                S.pop();
                if (state[v] == -1) {
                    state[v] = 1;
                    chain.push_back(v);
                    for (auto w : g.getadjlist(v)) {
                        if (state[w] == -1) {
                            S.push(w);
                        }
                    }
                }
            }
        }
    }
    for (auto edge : back) {
        if (find(chain.begin(), chain.end(), edge.first) == chain.end() || find(chain.begin(), chain.end(), edge.second) == chain.end())
            return false;
    }
    return true;
}

int main() {
    Graph c;  // this line is written by (((( Nawar Ibrahim ))))
    // all of these lines is written by Salma Mahmoud
    string const inputfile ;
    ifstream file(inputfile);
    if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    string line; int u, v;
    while (getline(file, line)) {
        istringstream iss(line);
        if (!(iss >> u >> v)) { break; }
        int maxNode = max(u, v);
        c.resizeAdjList(maxNode + 1);
        c.add_edge(u, v);
    }
    file.close();
     if(Cheriyan_Mehlhorn_Gabow(c) && jens_schmidt(c)) cout << "yes" ; else cout << "no" ;
     cout << '\n';
    
    return 0;
}