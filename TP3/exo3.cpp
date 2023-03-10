#include "mainwindow.h"
#include "tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

struct SearchTreeNode : public Node
{    
    SearchTreeNode* left;
    SearchTreeNode* right;
    int value;

    void initNode(int value)
    {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

    void insertNumber(int value) {
        if(this->value == value) return;
        if(this->value > value) {
            if(this->left == nullptr)
                this->left = new SearchTreeNode(value);
            return this->left->insertNumber(value);
        }
        if(this->value < value) {
            if(this->right == nullptr)
                this->right = new SearchTreeNode(value);
            return this->right->insertNumber(value);
        }
    }

	uint height() const	{
        // should return the maximum height between left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        uint l = (this->left) ? this->left->height() : 0,
             r = (this->right) ? this->right->height() : 0;
        return (l > r ? l : r) + 1;
    }

	uint nodesCount() const {
        // should return the sum of nodes within left child and
        // right child +1 for itself. If there is no child, return
        // just 1
        uint l = (this->left) ? this->left->nodesCount() : 0,
             r = (this->right) ? this->right->nodesCount() : 0;
        return l + r + 1;
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        return !(this->left || this->right);
	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        // fill leaves array with all leaves of this tree
        if(isLeaf()) {
            leaves[leavesCount++] = this;
            return;
        }
        if(this->left) this->left->allLeaves(leaves, leavesCount);
        if(this->right) this->right->allLeaves(leaves, leavesCount);
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with inorder travel
        if(this->left) this->left->inorderTravel(nodes, nodesCount);
        nodes[nodesCount++] = this;
        if(this->right) this->right->inorderTravel(nodes, nodesCount);
	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with preorder travel
        nodes[nodesCount++] = this;
        if(this->left) this->left->preorderTravel(nodes, nodesCount);
        if(this->right) this->right->preorderTravel(nodes, nodesCount);
	}

	void postorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with postorder travel
        if(this->left) this->left->postorderTravel(nodes, nodesCount);
        if(this->right) this->right->postorderTravel(nodes, nodesCount);
        nodes[nodesCount++] = this;
	}

	Node* find(int value) {
        // find the node containing value
        if(this->value == value) return this;
        if(this->value > value && this->left) return this->left->find(value);
        if(this->value < value && this->right) return this->right->find(value);
		return nullptr;
	}

    void reset()
    {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
        left = right = NULL;
    }

    SearchTreeNode(int value) : Node(value) {initNode(value);}
    ~SearchTreeNode() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

Node* createNode(int value) {
    return new SearchTreeNode(value);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow<SearchTreeNode>();
	w->show();

	return a.exec();
}
