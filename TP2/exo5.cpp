#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
	// stop statement = condition + return (return stop the function even if it does not return anything)
    if(origin.size() <= 1) {
        return;
    }

	// initialisation
	Array& first = w->newArray(origin.size()/2);
	Array& second = w->newArray(origin.size()-first.size());
	
    // split
    for(size_t i = 0; i < first.size(); i++) {
        first.insert(i, origin[i]);
    }
    for(size_t i = 0; i < second.size(); i++) {
        second.insert(i, origin[i + first.size()]);
    }

	// recursiv splitAndMerge of lowerArray and greaterArray
    splitAndMerge(first);
    splitAndMerge(second);

	// merge
    merge(first, second, origin);
}

void merge(Array& first, Array& second, Array& result)
{
    size_t first_i = 0;
    size_t second_i = 0;
    for(size_t i = 0; i < result.size(); i++) {
        if(first_i == first.size()) {
            auto min_second = second[second_i];
            result[i] = min_second;
            second_i++;
            continue;
        }
        if(second_i == second.size()) {
            auto min_first= first[first_i];
            result[i] = min_first;
            first_i++;
            continue;
        }
        auto min_first = first[first_i];
        auto min_second = second[second_i];
        if(min_first < min_second) {
            result[i] = min_first;
            first_i++;
        } else {
            result[i] = min_second;
            second_i++;
        }
    }
}

void mergeSort(Array& toSort)
{
//    Array& original = w->newArray(toSort.size());
//    original = toSort;
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
	w->show();

	return a.exec();
}
