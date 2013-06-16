#ifndef PRM_H
#define PRM_H

#include <graph.h>
#include <QColor>
#include <QGLWidget>
#include <QtCore>
#include <astar.h>
#include <time.h>

class PRM
{
public:
    PRM(double **map,int mapSize);
    Graph* createGraph(int numberOfNodes, int numberClosestNeighbors);
    vector<Edge*> query(int numberClosestNeighbors);
    int delta(Node *n1, Node *n2);
    bool checkNodeAreaIsEmpty(Node *n1);
    bool checkNodeAreaIsEmpty(int x,int y);
    void render();
    void drawBox(double xi,double yi,double xf,double yf,QColor color);
    void setInitNode(double x, double y);
    void setGoalNode(double x, double y);
    Graph *mGraph;
    Node *mGoalNode, *mInitNode;
    double **mMap;
    int mMapSize, celRange;
    vector<Edge*> path;

};

#endif // PRM_H
