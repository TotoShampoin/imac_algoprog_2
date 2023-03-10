#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

int binarySearch(Array& array, int toSearch)
{
    int min = 0;
    int max = array.size();
    while(min < max) {
        int mid = (max + min) / 2;
        auto pick = array[mid];
        if(pick == toSearch) return mid;
        if(pick < toSearch) min = mid + 1;
        if(pick > toSearch) max = mid;
    }
    return -1;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchWindow(binarySearch);
	w->show();

	return a.exec();
}
