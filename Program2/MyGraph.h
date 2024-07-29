//
// Created by Deuce Palmer on 3/7/23.
//
#ifndef CS3353_PROGRAM2_MYGRAPH_H
#define CS3353_PROGRAM2_MYGRAPH_H
#include <iostream>
#include <vector>

using namespace std;

//edge represents 2 connecting nodes, used for the graph and MaxST list of edges
#define edge pair<int, int>

class MyGraph {
private:
    /**
     * stores initial graph content as a list of edges
     */
    vector<pair<float, edge>> graph;
    /**
     * stores Maximum Spanning Tree as a list of edges
     */
    vector<pair<float, edge>> maxST;
    /**
     * stores Maximum Spanning Tree as an Adjacency List
     */
    vector<pair<int,float>> *maxxST;
    /**
     * number of nodes
     */
    int nodes;
    /**
     * pointers used for disjoint sets implementation in Kruskal's algorithm
     */
    int *parent;
    int *num;
public:
    /**
     * constructors
     */
    MyGraph(int n);
    MyGraph(const MyGraph&);
    /**
     * adds edge to current graph while checking for its pre-existence in the graph and nodes that are out of range
     */
    bool addEdge(int, int, float);
    /**
     * outputs content of graph to file
     * format 'node node capacity' smallest node will always be first
     */
    void output(ostream&);
    /**
     * returns the parent of a node
     */
    int findSet(int);
    /**
     * combines two sets into one
     */
    void unionSet(int, int);
    /**
     * Kruskal's algorithm while using findSet and unionSet to check for cycles with disjoint sets
     */
    void createMaxST();
    /**
     * DFS to find path between two nodes
     */
    bool DFSVisit(int, int, vector<int>&, pair<vector<int>, float>&, pair<vector<int>, float>&, bool&);
    /**
     * returns path and its corresponding capacity
     * bool can print contents of Maximum Spanning Tree
     */
    pair<vector<int>, float> HW2Prog(int, int, bool);
};
#endif //CS3353_PROGRAM2_MYGRAPH_H
