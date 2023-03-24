#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

/**
 * @brief define indexMin and indexMax as the first and the last index of toSearch
 * @param array array of int to process
 * @param toSearch value to find
 * @param indexMin first index of the value to find
 * @param indexMax last index of the value to find
 */
void binarySearchAll(Array& array, int toSearch, int& indexMin, int& indexMax)
{
    // do not use increments, use two different binary search loop
    indexMin = indexMax = -1;

    int min = 0;
    int max = array.size();
    while(min < max) {
        int mid = (max + min) / 2;
        auto pick = array[mid];
        if(mid + 1 == max) break;
        if(pick == toSearch) min = mid;
        if(pick < toSearch) min = mid + 1;
        if(pick > toSearch) max = mid;
    }
    if(array[min] != toSearch) return;
    indexMax = min;

    min = 0;
    max = indexMax;
    while(min < max) {
        int mid = (max + min) / 2;
        auto pick = array[mid];
        if(mid + 1 == max) break;
        if(pick == toSearch) max = mid;
        if(pick < toSearch) min = mid;
        if(pick > toSearch) max = mid;
    }
    indexMin = max;

}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchAllWindow(binarySearchAll);
	w->show();

	return a.exec();
}
