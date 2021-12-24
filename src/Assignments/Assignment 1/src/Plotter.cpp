#include "Plotter.h"
#include"vector.h"
#include"strlib.h"
using namespace std;

void runPlotterScript(istream& input) {
    PenStyle ps = {1, "black"};
    bool isDraw = false;
    double x0 = 0;
    double y0 = 0;

    for (string line; getline(input, line); ) {
        line = toLowerCase(line);
        Vector<string> tmps = stringSplit(line, " ");
        if (tmps[0] == "pendown") {
            isDraw = true;
        } else if (tmps[0] == "penup") {
            isDraw = false;
        } else if (tmps[0] == "pencolor") {
            ps.color = tmps[1];
        } else if (tmps[0] == "penwidth") {
            ps.width = stringToReal(tmps[1]);
        } else {
            if (isDraw) {
                double x1 = 0, y1 = 0;
                if (tmps[0] == "moveabs") {
                    x1 = stringToReal(tmps[1]);
                    y1 = stringToReal(tmps[2]);
                } else if (tmps[0] == "moverel") {
                    x1 = x0 + stringToReal(tmps[1]);
                    y1 = y0 + stringToReal(tmps[2]);
                }
                drawLine(x0, y0, x1, y1, ps);
            } else {
                if (tmps[0] == "moveabs") {
                    x0 = stringToReal(tmps[1]);
                    y0 = stringToReal(tmps[2]);
                } else if (tmps[0] == "moverel") {
                    x0 += stringToReal(tmps[1]);
                    y0 += stringToReal(tmps[2]);
                }
            }
        }
    }
}

