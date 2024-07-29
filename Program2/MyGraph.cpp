//
// Created by Deuce Palmer on 3/7/23.
//
#include "MyGraph.h"

MyGraph::MyGraph(int n){
    nodes = n;
}
MyGraph::MyGraph(const MyGraph& g){
    //only copies graph defining information of node count and graph content
    nodes = g.nodes;
    for (int i =0; i<g.graph.size(); i++) {
        graph.push_back(g.graph[i]);
    }
}
bool MyGraph::addEdge(int a, int b, float w){
    //check if node exists on the graph
    if (a < nodes || b < nodes) {
        //checks to make sure edge has not already been added to either node
        auto it = find(graph.begin(), graph.end(), make_pair(w, edge(a,b)));
        auto it2 = find(graph.begin(), graph.end(), make_pair(w, edge(b,a)));
        if (it != graph.end() || it2 != graph.end()){//if it already exists, do not add edge and return false
            return false;
        }
        graph.push_back(make_pair(w, edge(a,b)));//add edge to graph list of edges
        return true;
    } else {//if either node does not exist on graph, do not add edge and return false
        return false;
    }
}
void MyGraph::output(ostream& os){
    os << nodes << endl;
    for (int i =0; i<graph.size(); i++){
        if (graph[i].second.first > graph[1].second.second) {//prints the smallest node first
            os << graph[i].second.second << " " << graph[i].second.first << " " << graph[i].first << endl;
        } else {//prints the smallest node first
            os << graph[i].second.first << " " << graph[i].second.second << " " << graph[i].first << endl;
        }
    }
}
int MyGraph::findSet(int a){
    //code from slide deck Version 3/4
    int root = a;
    while (root != parent[root]){//find root of a
        root = parent[root];
    }
    int j = parent[a];
    while (j != root){//set every other node along the path to have root as its parent
        parent[a] = root;
        a = j;
        j = parent[a];
    }
    return root;
}
void MyGraph::unionSet(int a, int b){
    //code from slide deck Version 3/4
    int aparent = findSet(a);
    int bparent = findSet(b);
    if (num[aparent] < num[bparent]){
        parent[aparent] = bparent;//set parent of smaller num node to bigger num node
        num[bparent] += num[aparent];//increase num of bigger num node
    } else if (num[aparent] > num[bparent]){
        parent[bparent] = aparent;//set parent of smaller num node to bigger num node
        num[aparent] += num[bparent];//increase num of bigger num node
    } else { //they have equal nums
        parent[aparent] = bparent;
        num[bparent] += num[aparent];
    }
}
void MyGraph::createMaxST() {
    maxxST = new vector<pair<int,float>>[nodes]; //initializes adjacency list that will store Maximum Spanning Tree
    parent = new int[nodes];//for disjoint sets implementation
    num = new int[nodes];//for disjoint sets implementation
    for (int i=0; i<nodes; i++){//make every node its own tree that points to itself
        parent[i] = i;
        num[i] = 0;
    }
    //using standard library sort since it is O(n log n), or in this case O(e log e)
    sort(graph.begin(), graph.end(), greater<>());//sorts in descending order
    int edges = 0;//stores number of edges added to maxST
    for (int i=0; i<graph.size(); i++) {
        int a = findSet(graph[i].second.first);
        int b = findSet(graph[i].second.second);
        if (a != b) {//if they do not belong to the same set
            unionSet(a, b);//combine the 2 sets
            maxST.push_back(graph[i]);//stored for easy output (no edge duplicates)
            //add each edge to both nodes to store Maximum Spanning Tree as an Adjacency List
            maxxST[graph[i].second.first].push_back(make_pair(graph[i].second.second, graph[i].first));
            maxxST[graph[i].second.second].push_back(make_pair(graph[i].second.first, graph[i].first));
            if (++edges >= (nodes-1)) {//an MST only has n-1 edges. Once maxST has n-1 edges, it can stop
                return;
            }
        }
    }
}
bool MyGraph::DFSVisit(int x, int dest, vector<int> &status, pair<vector<int>, float> &path, pair<vector<int>, float> &correctPath, bool &found) {
    if (found == false) {//will run only if dest is not yet found, will make program more efficient in order to eliminate unnecessary DFS steps
        path.first.push_back(x);//add node to stack
        status[x] = 1; //mark node as visited
        for (auto it = maxxST[x].begin(); it != maxxST[x].end(); it++) {//search all adjacent nodes
            if (it->first == dest) {//if destination is found
                path.first.push_back(it->first);
                correctPath.first = path.first;//create a copy of the current path on the stack
                found = true;
                return true;
            }
            if (status[it->first] == 0) {//if a node is unvisited, recursively continue the DFS
                DFSVisit(it->first, dest, status, path, correctPath, found);
            }
        }
        path.first.pop_back();//once node is finished, pop it out of stack
    }
}
pair<vector<int>, float> MyGraph::HW2Prog(int s, int t, bool printMST){
    if (maxST.size() == 0){//in order to increase efficiency, only perform MaxST once
        createMaxST();
    }
    vector<int> status(nodes);//0=unvisited, 1=visited
    for (int s=0; s<nodes; s++){//set all nodes to unvisited
        status[s] = 0;
    }
    pair<vector<int>, float> path;//the stack for DFS
    pair<vector<int>, float> correctPath;//a snapshot of the stack when start -> dest
    bool found = false;
    DFSVisit(s, t, status, path, correctPath, found);//make first DFS call, starting at s
    int start = correctPath.first[0];
    int next = correctPath.first[1];
    for (auto it = maxxST[start].begin(); it != maxxST[start].end(); it++) {//uses the 2 nodes to find the corresponding edge weight
        if (it->first == next){
            correctPath.second = it->second;//initializes capacity of path
        }
    }
    for (int i=1; i<correctPath.first.size()-1; i++){//for every edge after the first
        int start = correctPath.first[i];
        int next = correctPath.first[i+1];
        for (auto it = maxxST[start].begin(); it != maxxST[start].end(); it++) {//uses the 2 nodes to find the corresponding edge weight
            if (it->first == next){
                if (correctPath.second > it->second) {//if this edge capacity is less than the current capacity of path
                    correctPath.second = it->second;//change path capacity
                }
            }
        }
    }
    if (printMST == true){//if user elects to print (same format as output())
        cout << nodes << endl;
        for (int i =0; i<maxST.size(); i++){//use maxST for output instead of maxxST adjacency list since there is only 1 entry per edge, not 2
            if (maxST[i].second.first > maxST[1].second.second) {//prints the smallest node first
                cout << maxST[i].second.second << " " << maxST[i].second.first << " " << maxST[i].first << endl;
            } else {//prints the smallest node first
                cout << maxST[i].second.first << " " << maxST[i].second.second << " " << maxST[i].first << endl;
            }
        }
    }
    return correctPath;
}