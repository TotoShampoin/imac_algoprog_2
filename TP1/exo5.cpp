#include "tp1.h"
#include <QApplication>
#include <time.h>

int isMandelbrot(Point z, int n, Point point){
    // recursiv Mandelbrot

    // check n
    if(n == 0) return 0;

    // check length of z
    // if Mandelbrot, return 1 or n (check the difference)
    // otherwise, process the square of z and recall
    // isMandebrot

    if( z.length() > 2 ) {
        return n;
    }
    Point zi = {
        z.x * z.x - z.y * z.y,
        2 * z.x * z.y
    };

    return isMandelbrot(zi, n-1, point);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}



