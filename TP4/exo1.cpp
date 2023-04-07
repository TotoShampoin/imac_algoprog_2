#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChildIndex(int nodeIndex)
{
    return nodeIndex * 2 + 1;
}

int Heap::rightChildIndex(int nodeIndex)
{
    return nodeIndex * 2 + 2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
    // use (*this)[i] or this->get(i) to get a value at index i
    int i = heapSize;
    this->set(i, value);
    while(i > 0 && this->get(i) > this->get((i-1)/2)) {
        this->swap(i, (i-1)/2);
        i = (i-1)/2;
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
	// use (*this)[i] or this->get(i) to get a value at index i
    int i_left = this->leftChildIndex(nodeIndex);
    int i_right = this->rightChildIndex(nodeIndex);
    if(i_left >= heapSize || i_right >= heapSize) return;
    int i_max = (this->get(i_left) < this->get(i_right)) ? i_right : i_left;
    if(this->get(nodeIndex) < this->get(i_max)) {
        swap(nodeIndex, i_max);
        heapify(heapSize, i_max);
    }
}

void Heap::buildHeap(Array& numbers)
{
    int size = 0;
    for(auto num : numbers) {
        insertHeapNode(size++, num);
    }
}

void Heap::heapSort()
{
    int n = this->size();
    for(int i = n - 1; i >= 0; i--) {
        swap(0, i);
        heapify(i, 0);
    }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
