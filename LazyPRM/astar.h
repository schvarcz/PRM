#ifndef ASTAR_H
#define ASTAR_H

#include <graph.h>

typedef struct __AStarInfo
{
    struct __AStarInfo *came_from;
    Node *node;
    double c_percurso, c_total;
} AStarInfo;

class AStar
{
public:
    AStar();
    vector<Edge*> shortestPath(Node *initNode,Node *goalNode);

protected:
    AStarInfo* getInfoClosedNode(Node *node);
    AStarInfo* getInfoOpenNode(Node *node);
    AStarInfo* getInfoNode(Node *node);
    AStarInfo* getInfoNode(vector<AStarInfo*> vector, Node *node);
    vector<AStarInfo*> closed;
    vector<AStarInfo*> open;
};

#endif // ASTAR_H
