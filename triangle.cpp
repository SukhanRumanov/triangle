#include <iostream>
#include <cmath>
#include <vector>

const int WIDTH = 50;
const int HEIGHT = 25;

class Tria {
    int x1, x2, x3;
    int y1, y2, y3;

    double LenV(int x1, int y1, int x2, int y2) {
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    int canFormTriangle1() {
        double area = 0.5 * std::abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        if (area > 0) {
            return 1;
        }
        return 0;
    }

    int canFormTriangle2() {
        double side1 = LenV(x1, y1, x2, y2);
        double side2 = LenV(x2, y2, x3, y3);
        double side3 = LenV(x3, y3, x1, y1);

        if ((side1 + side2 > side3) &&
            (side1 + side3 > side2) &&
            (side2 + side3 > side1)) {
            return 1;
        }
        return 0;
    }

    void Brezenhem(char** z, int x0, int y0, int x1, int y1) {
        int A = y1 - y0;
        int B = x0 - x1;
        int signa = (A < 0) ? -1 : 1;
        int signb = (B < 0) ? -1 : 1;
        int sign = (abs(A) > abs(B)) ? 1 : -1;

        int f = 0;
        z[y0][x0] = '*';
        int x = x0, y = y0;

        if (sign == -1) {
            while (x != x1 || y != y1) {
                f += A * signa;
                if (f > 0) {
                    f -= B * signb;
                    y += signa;
                }
                x -= signb;
                z[y][x] = '*';
            }
        }
        else {
            while (x != x1 || y != y1) {
                f += B * signb;
                if (f > 0) {
                    f -= A * signa;
                    x -= signb;
                }
                y += signa;
                z[y][x] = '*';
            }
        }
    }


public:
    Tria(int x1, int x2, int x3, int y1, int y2, int y3)
        : x1(x1), x2(x2), x3(x3), y1(y1), y2(y2), y3(y3) {}

    int Check() {
        return canFormTriangle1() && canFormTriangle2();
    }

    void DrawTriangle() {
        if (!Check()) {
            std::cout << "Error" << std::endl;
            return;
        }

        char** canvas = new char* [HEIGHT];
        for (int i = 0; i < HEIGHT; ++i) {
            canvas[i] = new char[WIDTH];
            std::fill(canvas[i], canvas[i] + WIDTH, ' ');
        }

        Brezenhem(canvas, x1, y1, x2, y2);
        Brezenhem(canvas, x2, y2, x3, y3);
        Brezenhem(canvas, x3, y3, x1, y1);

        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                std::cout << canvas[y][x];
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < HEIGHT; ++i) {
            delete[] canvas[i];
        }
        delete[] canvas;
    }
};

int main() {
    Tria triangle1(10, 40, 25, 5, 5, 20);
    triangle1.DrawTriangle();

    return 0;
}
