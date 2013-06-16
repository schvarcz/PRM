#include "graph.h"

Graph::Graph()
{
}

bool Graph::hasEdge(Node *n1, Node *n2)
{
    for(int i=0;i<E.size();i++)
    {
        Edge *e = E.at(i);

        //qDebug() << e->mNodeL << n1;
        //qDebug() << e->mNodeR << n2;
        if(e->mNodeL == n1 && e->mNodeR == n2)
        {
            return true;
        }
        /*
        if(e->mNodeL == n2 && e->mNodeR == n1)
        {
            return true;
        }
        */
    }
    return false;
}
