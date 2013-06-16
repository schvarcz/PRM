#ifndef EDGE_H
#define EDGE_H

#include <QtCore>

class Node;

class Edge
{
public:
    Edge(Node *nodeLeft, Node *nodeRight);
    Node *mNodeL, *mNodeR;
    double distance;
};

#include <node.h>

#endif // EDGE_H
