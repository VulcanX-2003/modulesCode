#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct point{
    int x;
    int y;
    int z;
};


struct shape{
    vector<point> points;
    string name;
};


vector<vector<float>> createRotationalMatrix(float angle, int dir, char axis)
{
    vector<vector<float>> rotationalMatrix(3, vector<float>(3, 0.0f));
    const float signedAngle = dir >= 0 ? angle : -angle;
    const float c = cos(signedAngle);
    const float s = sin(signedAngle);

    if (axis == 'x' || axis == 'X') {
        rotationalMatrix = {
            {1.0f, 0.0f, 0.0f},
            {0.0f, c, -s},
            {0.0f, s, c}
        };
    } else if (axis == 'y' || axis == 'Y') {
        rotationalMatrix = {
            {c, 0.0f, s},
            {0.0f, 1.0f, 0.0f},
            {-s, 0.0f, c}
        };
    } else if (axis == 'z' || axis == 'Z') {
        rotationalMatrix = {
            {c, -s, 0.0f},
            {s, c, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
    }

    return rotationalMatrix;
}





vector<vector<float>> compositeRotation()
{   
    
    return rotationalMatrix;
}



shape rotation3d(const shape& s, float angle, int direction, char axis)
{
    shape rotatedShape;

    rotatedShape.name = s.name;
    rotatedShape.points.reserve(s.points.size());

    const vector<vector<float>> rotationalMatrix =
        createRotationalMatrix(angle, direction, axis);

    for (const point& currentPoint : s.points) {
        rotatedShape.points.push_back({
            static_cast<int>(lround(rotationalMatrix[0][0] * currentPoint.x + rotationalMatrix[0][1] * currentPoint.y + rotationalMatrix[0][2] * currentPoint.z)),
            static_cast<int>(lround(rotationalMatrix[1][0] * currentPoint.x + rotationalMatrix[1][1] * currentPoint.y + rotationalMatrix[1][2] * currentPoint.z)),
            static_cast<int>(lround(rotationalMatrix[2][0] * currentPoint.x + rotationalMatrix[2][1] * currentPoint.y + rotationalMatrix[2][2] * currentPoint.z))
        });
    }




    return rotatedShape;
}



int main()
{   
    //shape cube{{{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0}, {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}}, "cube"};
    
    shape pyramid{{{0, 0, 0}, {2, 0, 0}, {2, 2, 0}, {0, 2, 0}, {1, 1, 2}}, "pyramid"};
    

    shape rotated = rotation3d(pyramid, static_cast<float>(M_PI / 2), 1, 'z');
    for (const point& currentPoint : rotated.points) {
        cout << currentPoint.x << ' ' << currentPoint.y << ' ' << currentPoint.z << '\n';
    }
    return 0;
}