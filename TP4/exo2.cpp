#include <time.h>
#include <stdio.h>

#include <QApplication>
#include <QDebug>

#include "tp3.h"
#include "tp4.h"
#include "tp4_exo2.h"
#include "HuffmanNode.h"

_TestMainWindow* w1 = nullptr;
using std::size_t;
using std::string;

void processCharFrequences(string data, Array& frequences);
void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize);
HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode);
HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize);

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree);
string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot);


void main_function(HuffmanNode*& huffmanTree)
{
    string data = "Ouesh, bien ou bien ? Ceci est une chaine de caracteres sans grand interet";

    // this array store each caracter frequences indexed by their ascii code
    Array characterFrequences(256);
    characterFrequences.fill(0);
    // this array store each caracter code indexed by their ascii code
    string characterCodes[256];
    HuffmanHeap priorityMinHeap;
    int heapSize = 0;

    processCharFrequences(data, characterFrequences);
    displayCharacterFrequences(characterFrequences);
    buildHuffmanHeap(characterFrequences, priorityMinHeap, heapSize);
    qDebug() << priorityMinHeap.toString().toStdString().c_str();

    huffmanTree = buildHuffmanTree(priorityMinHeap, heapSize);
    huffmanTree->processCodes("");
    string encoded = huffmanEncode(data, huffmanTree);
    string decoded = huffmanDecode(encoded, *huffmanTree);

    qDebug("Encoded: %s\n", encoded.c_str());
    qDebug("Decoded: %s\n", decoded.c_str());
}


void processCharFrequences(string data, Array& frequences)
{
    /**
      * Fill `frequences` array with each caracter frequence.
      * frequences is an array of 256 int. frequences[i]
      * is the frequence of the caracter with ASCII code i
     **/

    // Your code
    frequences.fill(0);
    for(auto c : data) {
        frequences[c]++;
    }
}

void HuffmanHeap::insertHeapNode(int heapSize, HuffmanNode* newNode)
{
    /**
      * Insert a HuffmanNode into the lower heap. A min-heap put the lowest value
      * as the first cell, so check the parent should be lower than children.
      * Instead of storing int, the cells of HuffmanHeap store HuffmanNode*.
      * To compare these nodes use their frequences.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/

    // TODO: fix this

    // Your code
    int i = heapSize;
    this->set(i, newNode);
    while(i > 0 && this->get(i)->frequences < this->get((i-1)/2)->frequences) {
        swap(i, (i-1)/2);
        i = (i-1)/2;
    }

}

void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize)
{
    /**
      * Do like Heap::buildHeap. Use only non-null frequences
      * Define heapSize as numbers of inserted nodes
      * allocate a HuffmanNode with `new`
     **/

    // Your code
    heapSize = 0;

    for(int i = 0; i < frequences.size(); i++) {
        auto frequence = frequences[i];
        if(frequence == 0) continue;
        HuffmanNode* node = new HuffmanNode { (unsigned char)i , frequence };
        priorityMinHeap.insertHeapNode(heapSize, node);
        heapSize++;
    }
}

int leftChildIndex(int nodeIndex)
{
    return nodeIndex * 2 + 1;
}

int rightChildIndex(int nodeIndex)
{
    return nodeIndex * 2 + 2;
}

void HuffmanHeap::heapify(int heapSize, int nodeIndex)
{
    /**
      * Repair the heap starting from nodeIndex. this is a min-heap,
      * so check the parent should be lower than children.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/
    
    // Your code
    int i_left = leftChildIndex(nodeIndex);
    int i_right = rightChildIndex(nodeIndex);
    if(i_left >= heapSize || i_right >= heapSize) return;
    int i_min = (this->get(i_left)->frequences > this->get(i_right)->frequences) ? i_right : i_left;
    if(this->get(nodeIndex)->frequences > this->get(i_min)->frequences) {
        swap(nodeIndex, i_min);
        heapify(heapSize, i_min);
    }
}


HuffmanNode* HuffmanHeap::extractMinNode(int heapSize)
{
    /**
      * Extract the first cell, replace the first cell with the last one and
      * heapify the heap to get a new well-formed heap without the returned cell
      * you can use `this->swap`
     **/

    // Your code
    HuffmanNode* node = get(0);
    swap(0, heapSize-1);
    heapify(heapSize-1, 0);
    return node;
}

HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode)
{
    /**
     * Make a subtree (parent + 2 children) with the given 2 nodes.
     * These 2 characters will be the children of a new parent node which character is '\0'
     * and frequence is the sum of the 2 children frequences
     * Return the new HuffmanNode* parent
     **/
    // Your code
    HuffmanNode* parent = new HuffmanNode('\0');
    parent->right = rightNode;
    parent->left = leftNode;
    parent->frequences = rightNode->frequences + leftNode->frequences;
    return parent;
}

HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize)
{
    /**
      * Build Huffman Tree from the priorityMinHeap, pick nodes from the heap until having
      * one node in the heap. For every 2 min nodes, create a subtree and put the new parent
      * into the heap. The last node of the heap is the HuffmanTree;
      * use extractMinNode()
     **/

    // Your code
    HuffmanNode* tmpParent = nullptr;
    HuffmanNode* tmpChild[2] = {nullptr, nullptr};
    while(heapSize > 1) {
        tmpChild[0] = priorityMinHeap.extractMinNode(heapSize--);
        tmpChild[1] = priorityMinHeap.extractMinNode(heapSize--);
        tmpParent = makeHuffmanSubTree(tmpChild[0], tmpChild[1]);
        priorityMinHeap.insertHeapNode(heapSize++, tmpParent);
    }
    return priorityMinHeap[0];
}

void HuffmanNode::processCodes(const std::string& baseCode)
{
    /**
      * Travel whole tree of HuffmanNode to determine the code of each
      * leaf/character.
      * Each time you call the left child, add '0' to the baseCode
      * and each time call the right child, add '1'.
      * If the node is a leaf, it takes the baseCode.
     **/

    // Your code
    if(isLeaf()) {
        code = baseCode;
        return;
    }
    left->processCodes(baseCode + "0");
    right->processCodes(baseCode + "1");
}

void HuffmanNode::fillCharactersArray(std::string charactersCodes[])
{
    /**
      * Fill the string array with all nodes codes of the tree
      * It store a node into the cell corresponding to its ascii code
      * For example: the node describing 'O' should be at index 79
     **/
    if (!this->left && !this->right)
        charactersCodes[this->character] = this->code;
    else {
        if (this->left)
            this->left->fillCharactersArray(charactersCodes);
        if (this->right)
            this->right->fillCharactersArray(charactersCodes);
    }
}

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree)
{
    /**
      * Encode a string by using the huffman compression.
      * With the huffmanTree, determine the code for each character
     **/

    // Your code
    std::string charactersCodes[256]; // array of 256 huffman codes for each character
    huffmanTree->fillCharactersArray(charactersCodes);
    string encoded = "";

    for(unsigned char c : toEncode) {
        encoded += charactersCodes[c];
    }

    return encoded;
}


string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot)
{
    /**
      * Use each caracters of toDecode, which is '0' either '1',
      * to travel the Huffman tree. Each time you get a leaf, get
      * the decoded character of this node.
     **/
    // Your code
    string decoded = "";
    const HuffmanNode* tmp = nullptr;

    tmp = &huffmanTreeRoot;
    for(auto c : toDecode) {
        switch (c) {
        case '0':
            tmp = tmp->left;
            break;
        case '1':
            tmp = tmp->right;
            break;
        }
        if(tmp->isLeaf()) {
            decoded += tmp->character;
            tmp = &huffmanTreeRoot;
        }
    }

    return decoded;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Array::wait_for_operations = false;
    w1 = new HuffmanMainWindow(main_function);
    w1->show();
    return a.exec();
}
