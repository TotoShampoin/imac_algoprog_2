#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;

void insertionSort(Array& toSort){
    Array& sorted = w->newArray(toSort.size());

    for(auto n : toSort) {
        size_t j;
        for(j = 0; j < sorted.effectiveSize(); j++) {
            auto m = sorted[j];
            if(m > n) break;
        }
        sorted.insert(j, n);
    }
    toSort = sorted; // update the original array
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(insertionSort); // window which display the behavior of the sort algorithm
	w->show();

	return a.exec();
}
