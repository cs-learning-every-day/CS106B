#include "Plotter.h"
#include <strlib.h>
using namespace std;

void runPlotterScript(istream& input) {
    PenStyle style = {1, "black"};

    bool isDraw = false;
    double x0 = 0, y0 = 0;

    for (string line; getline(input, line);) {
        line = toLowerCase(line);
        Vector<string> order = stringSplit(line, " ");
        double oldX = x0, oldY = y0;

        if (order[0] == "penup") {
            isDraw = false;
        } else if (order[0] == "pendown") {
            isDraw = true;
        } else if (order[0] == "moveabs") {
            x0 = stringToReal(order[1]);
            y0 = stringToReal(order[2]);
        } else if (order[0] == "moverel") {
            x0 += stringToReal(order[1]);
            y0 += stringToReal(order[2]);
        } else if (order[0] == "pencolor") {
            style.color = order[1];
        } else if (order[0] == "penwidth") {
            style.width = stringToDouble(order[1]);
        }
        if (isDraw) {
            drawLine(oldX, oldY, x0, y0, style);
        }
    }
}
