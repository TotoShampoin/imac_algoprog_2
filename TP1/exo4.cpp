#include "tp1.h"
#include <QApplication>
#include <time.h>

#define return_and_display(result) return _.store(result);

void allEvens(Array& evens, Array& array, int evenSize, int arraySize)
{
    Context _("allEvens", evenSize, arraySize); // do not care about this, it allow the display of call stack

    // your code
    if(arraySize == 0) return;
    if(array[0] % 2 == 0) {
        evens.insert(evenSize++, array[0]);
    }
    Array inter(arraySize-1);
    for(int i = 1; i < arraySize; i++) {
        inter.set(i-1, array[i]);
    }
    allEvens(evens, inter, evenSize, arraySize-1);
    return;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // create a window manager
    MainWindow::instruction_duration = 400;  // make a pause between instruction display
    MainWindow* w = new AllEvensWindow(allEvens); // create a window for this exercice
    w->show(); // show exercice

    return a.exec(); // main loop while window is opened
}




