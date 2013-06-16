#ifndef NODE_H
#define NODE_H

#include <Aria.h>
#include <vector>
#include <QtCore>

using namespace std;

class Graph;
class Edge;

class Node
{
public:
    Node();
    Node(int id);
    vector<Node*> sortedClosest(Graph *graph, int numberClosestNeighbors);
    double distance(Node *node);
    ArPose *mPose;
    vector<Edge*> neighbors;
    int mId;
private:
    Edge** merge(int start,int finish);
    Edge **edges;

};

#include <graph.h>

#endif // NODE_H
