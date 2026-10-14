#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

struct point{
    int x;
    int y;
};





struct shape{
    vector<point> points;
    string name;
};




vector<vector<float>> createRotationalMatrix(float angle, int direction)
{
    vector<vector<float>> rotationMatrix(2, vector<float>(2, 0.0f));

    if (direction == 1) {
        rotationMatrix[0][0] = cos(angle);
        rotationMatrix[0][1] = -sin(angle);
        rotationMatrix[1][0] = sin(angle);
        rotationMatrix[1][1] = cos(angle);
    }

    if (direction == -1) {
        rotationMatrix[0][0] = cos(angle);
        rotationMatrix[0][1] = sin(angle);
        rotationMatrix[1][0] = -sin(angle);
        rotationMatrix[1][1] = cos(angle);
    }


    return rotationMatrix;
}



shape rotation2d(const shape& s, float angle, int direction) {
    shape rotatedShape;

    rotatedShape.name = s.name;
    rotatedShape.points.reserve(s.points.size());

    const vector<vector<float>> rotationMatrix = createRotationalMatrix(angle, direction);


    for (const point& currentPoint : s.points) {
        rotatedShape.points.push_back({
            static_cast<int>(lround(rotationMatrix[0][0] * currentPoint.x + rotationMatrix[0][1] * currentPoint.y)),
            
            static_cast<int>(lround(rotationMatrix[1][0] * currentPoint.x + rotationMatrix[1][1] * currentPoint.y))
        });
    }

    return rotatedShape;
}




int main(){
    //shape square{{{0, 0}, {1, 0}, {1, 1}, {0, 1}}, "square"};
    //shape triangle{{{0,0},{0,1}, {1,0}}, "triangle"};

    //shape rectangle{{{0, 0}, {2, 0}, {2, 1}, {0, 1}}, "rectangle"};
    shape pentagon{{{0, 0}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}}, "pentagon"};



    shape rotated = rotation2d(pentagon, static_cast<float>(M_PI / 2), 1);
    for (const point& currentPoint : rotated.points) {
        cout << currentPoint.x << ' ' << currentPoint.y << '\n';
    }
    return 0;
}