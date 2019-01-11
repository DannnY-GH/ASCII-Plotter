#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <ctime>
#include <cmath>
#include <afxres.h>

#define M_PI  3.14159265358979323846
#define FILE "out"
using namespace std;

struct pt {
    double x, y;
};

struct TOCanvas {
    vector<vector<char> > cnv;
    int w, h;
    double gridStep = 1.0;
    char brushColor;

    TOCanvas(int _w, int _h, int gridStep) {
        this->w = _w;
        this->h = _h;
        this->gridStep = gridStep;
        cnv.resize(_w, vector<char>(_h, ' '));
    }

    void setBrushColor(char color) {
        brushColor = color;
    }

    void draw() {
        for (int i = h - 1; i >= 0; i--) {
            for (int j = 0; j < w; j++)
                cout << cnv[j][i];
            cout << endl;
        }
    }

    bool checkBounds(int x, int y) {
        return x >= 0 && y >= 0 && x < w && y < h;
    }

    void plotPolar(pt (*f)(double), int mx, int my, double from, double to, double delta) {
        for (double arg = from; arg < to; arg += delta) {
            pt out = f(arg);
            int x = (int) ((out.x + mx) / gridStep);
            int y = (int) ((out.y + my) / gridStep);
            if (checkBounds(x, y)) {
                cnv[x][y] = brushColor;
            }
        }
    }

    void plotXY(double(*f)(double), int mx, int my, double from, double to, double delta) {
        for (double arg = from; arg < to; arg += delta) {
            int x = (int) ceil(arg + mx / gridStep);
            int y = (int) ceil(f(arg) + my / gridStep);
            if (checkBounds(x, y)) {
                cnv[x][y] = brushColor;
            }
        }
    }
};

double parabolic(double x) {
    return x * x / 2500;
}

pt circle(double arg) {
    double r = 90;
    return {r * cos(arg), r * sin(arg)};
}

pt gold(double arg) {
    double r = 4 * arg;
    return {r * cos(2 * arg), r * sin(2 * arg)};
}

pt heart(double arg) {
    double r = (2 - 2 * sin(arg) + sin(arg) * sqrt(abs(cos(arg))) / (sin(arg) + 1.4)) * 40;
    return {r * cos(arg), r * sin(arg)};
}

pt flower(double arg) {
    double r = 150 * sin(7 * arg / 4);
    return {r * cos(arg), r * sin(arg)};
}

int main() {
#ifdef FILE
    freopen(FILE".txt", "w", stdout);
#else
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
#endif
    TOCanvas canvas(300, 230, 2);
    canvas.setBrushColor('0');
    canvas.plotXY(parabolic, 0, 5, 0, canvas.h * canvas.gridStep * 20., 0.1);
    canvas.plotPolar(circle, 200, 200, 0, 2 * M_PI, 0.01);
    canvas.plotPolar(flower, 200, 200, 0, 8 * M_PI, 0.001);
    canvas.plotPolar(gold, 420, 300, 0, 15 * M_PI, 0.0001);
    canvas.plotPolar(heart, 450, 230, 0, 2 * M_PI, 0.0001);
    canvas.draw();
#ifdef FILE
    fclose(stdout);
#else
    system("pause");
#endif
    return 0;
}
