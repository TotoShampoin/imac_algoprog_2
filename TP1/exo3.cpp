#include "tp1.h"
#include <QApplication>
#include <time.h>

#define return_and_display(result) return _.store(result);


int search(int value, Array& toSort, int size)
{
    Context _("search", value, size); // do not care about this, it allow the display of call stack

    // your code
    // check the last cell and if it does not correspond
    // then consider a smaller array when recalling search

    if(size == 1 && toSort[0] != value) {
        return_and_display(-1);
    }
    if(toSort[0] == value) {
        return_and_display(0);
    }
    Array inter(size-1);
    for(int i = 1; i < size; i++) {
        inter.set(i-1, toSort[i]);
    }
    int res = search(value, inter, size-1);
    if(res == -1) {
        return_and_display(-1);
    }
    return_and_display(res + 1);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // create a window manager
    MainWindow::instruction_duration = 400;  // make a pause between instruction display
    MainWindow* w = new SearchWindow(search); // create a window for this exercice
    w->show(); // show exercice

    return a.exec(); // main loop while window is opened
}




