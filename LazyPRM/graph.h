#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <node.h>
#include <edge.h>

using namespace std;

class Graph
{
public:
    Graph();
    bool hasEdge(Node *n1, Node *n2);

    vector<Node*> V;
    vector<Edge*> E;
};

#endif // GRAPH_H
