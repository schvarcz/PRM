#include "pose.h"

Pose::Pose()
{
    mX = mY = 0.0;
}
void Pose::setPose(double x, double y)
{
    mX = x;
    mY = y;
}

double Pose::getX()
{
    return mX;
}
double Pose::getY()
{
    return mY;
}
