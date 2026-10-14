#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct point {
    int x;
    int y;
    int z;
};

struct shape {
    vector<point> points;
    string name;
};

using Matrix4x4 = vector<vector<float>>;

Matrix4x4 createCompositeMatrix(float angle, int direction, char axis, const point& translation)
{
    Matrix4x4 matrix(4, vector<float>(4, 0.0f));
    const float signedAngle = direction >= 0 ? angle : -angle;
    const float cosine = cos(signedAngle);
    const float sine = sin(signedAngle);

    if (axis == 'x' || axis == 'X') {
        matrix[0][0] = 1.0f;
        matrix[1][1] = cosine;
        matrix[1][2] = -sine;
        matrix[2][1] = sine;
        matrix[2][2] = cosine;
    } else if (axis == 'y' || axis == 'Y') {
        matrix[0][0] = cosine;
        matrix[0][2] = sine;
        matrix[1][1] = 1.0f;
        matrix[2][0] = -sine;
        matrix[2][2] = cosine;
    } else if (axis == 'z' || axis == 'Z') {
        matrix[0][0] = cosine;
        matrix[0][1] = -sine;
        matrix[1][0] = sine;
        matrix[1][1] = cosine;
        matrix[2][2] = 1.0f;
    } else {
        throw invalid_argument("axis must be x, y, or z");
    }

    matrix[0][3] = static_cast<float>(translation.x);
    matrix[1][3] = static_cast<float>(translation.y);
    matrix[2][3] = static_cast<float>(translation.z);
    matrix[3][3] = 1.0f;
    return matrix;
}

shape transformShape(const shape& originalShape, const Matrix4x4& matrix)
{
    shape transformedShape;
    transformedShape.name = originalShape.name;
    transformedShape.points.reserve(originalShape.points.size());

    for (const point& currentPoint : originalShape.points) {
        transformedShape.points.push_back({
            static_cast<int>(lround(matrix[0][0] * currentPoint.x + matrix[0][1] * currentPoint.y + matrix[0][2] * currentPoint.z + matrix[0][3])),
            static_cast<int>(lround(matrix[1][0] * currentPoint.x + matrix[1][1] * currentPoint.y + matrix[1][2] * currentPoint.z + matrix[1][3])),
            static_cast<int>(lround(matrix[2][0] * currentPoint.x + matrix[2][1] * currentPoint.y + matrix[2][2] * currentPoint.z + matrix[2][3]))
        });
    }

    return transformedShape;
}

void printMatrix(const Matrix4x4& matrix)
{
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            cout << value << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    shape pyramid{{{0, 0, 0}, {2, 0, 0}, {2, 2, 0}, {0, 2, 0}, {1, 1, 2}}, "pyramid"};
    const point translation{3, -2, 5};
    const Matrix4x4 matrix = createCompositeMatrix(1.57079632679f, 1, 'z', translation);
    const shape transformedPyramid = transformShape(pyramid, matrix);

    cout << transformedPyramid.name << " transformed points:\n";
    for (const point& currentPoint : transformedPyramid.points) {
        cout << currentPoint.x << ' ' << currentPoint.y << ' ' << currentPoint.z << '\n';
    }

    cout << "\nComposite transformation matrix:\n";
    printMatrix(matrix);

    return 0;
}




