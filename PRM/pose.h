#ifndef POSE_H
#define POSE_H

class Pose
{
public:
    Pose();
    void setPose(double x, double y);
    double getX();
    double getY();
    double mX, mY;
};

#endif // POSE_H
