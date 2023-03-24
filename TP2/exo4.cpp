#include <QApplication>
#include <time.h>

#include "tp2.h"


MainWindow* w=nullptr;

void recursivQuickSort(Array& toSort, int size)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    if(size <= 1) return;
	
	Array& lowerArray = w->newArray(size);
    Array& greaterArray = w->newArray(size);
	int lowerSize = 0, greaterSize = 0; // effectives sizes

	// split
    auto pivot = toSort[0];
    for(int i = 1; i < size; i++) {
        if(toSort[i] < pivot) {
            lowerArray.insert(lowerSize++, toSort[i]);
        } else {
            greaterArray.insert(greaterSize++, toSort[i]);
        }
    }
	
	// recursiv sort of lowerArray and greaterArray
    recursivQuickSort(lowerArray, lowerSize);
    recursivQuickSort(greaterArray, greaterSize);

	// merge
    Array merge(size);
    for(auto n : lowerArray) {
        merge.insert(merge.effectiveSize(), n);
    }
    merge.insert(merge.effectiveSize(), pivot);
    for(auto n : greaterArray) {
        merge.insert(merge.effectiveSize(), n);
    }
    toSort = merge;
}

void quickSort(Array& toSort){
	recursivQuickSort(toSort, toSort.size());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(quickSort);
	w->show();

	return a.exec();
}
