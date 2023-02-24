#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;


void bubbleSort(Array& toSort){
    bool is_sorted = true;
    do {
        is_sorted = true;
        for(size_t i = 0; i < toSort.size() - 1; i++) {
            if(toSort[i] > toSort[i+1]) {
                toSort.swap(i, i+1);
                is_sorted = false;
            }
        }
    } while(!is_sorted);
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 100;
	w = new TestMainWindow(bubbleSort);
	w->show();

	return a.exec();
}
