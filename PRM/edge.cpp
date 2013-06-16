#include "edge.h"

Edge::Edge(Node *nodeLeft, Node *nodeRight)
{
    mNodeL = nodeLeft;
    mNodeR = nodeRight;

    distance = sqrt(pow(mNodeR->mPose->getX() - mNodeL->mPose->getX(),2)+pow(mNodeR->mPose->getY() - mNodeL->mPose->getY(),2));
    //qDebug() << distance;
}
