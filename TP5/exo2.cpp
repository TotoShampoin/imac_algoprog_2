#include <QApplication>
#include <QString>
#include <time.h>
#include <stdio.h>
#include <string>

#include <tp5.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;


std::vector<string> TP5::names(
{
    "Yolo", "Anastasiya", "Clement", "Sirine", "Julien", "Sacha", "Leo", "Margot",
    "JoLeClodo", "Anais", "Jolan", "Marie", "Cindy", "Flavien", "Tanguy", "Audrey",
    "Mr.PeanutButter", "Bojack", "Mugiwara", "Sully", "Solem",
    "Leo", "Nils", "Vincent", "Paul", "Zoe", "Julien", "Matteo",
    "Fanny", "Jeanne", "Elo"
});

unsigned long int hash(string key)
{
    // return an unique hash id from key
    unsigned long h = 0;
    unsigned long p = 1;
    for(unsigned long i = 0; i < key.length(); i++) {
        p <<= 7; // *= 128
    }
    for(unsigned char c : key) {
        h += c * p;
        p >>= 7; // /= 128
    }
    return h;
}

struct MapNode : public BinaryTree
{

    string key;
    unsigned long int key_hash;

    int value;

    MapNode* left;
    MapNode* right;

    MapNode(string key, int value) : BinaryTree (value)
    {
        this->key = key;
        this->value = value;
        this->key_hash = hash(key);

        this->left = this->right = nullptr;
    }

    /**
     * @brief insertNode insert a new node according to the key hash
     * @param node
     */
    void insertNode(MapNode* node)
    {
        MapNode** next = nullptr;
        if(node->key_hash > this->key_hash) {
            next = &this->right;
        } else {
            next = &this->left;
        }
        if(!*next) {
            *next = node;
            return;
        }
        (*next)->insertNode(node);
    }

    void insertNode(string key, int value)
    {
        this->insertNode(new MapNode(key, value));
    }

    virtual ~MapNode() {}
    QString toString() const override {return QString("%1:\n%2").arg(QString::fromStdString(key)).arg(value);}
    Node* get_left_child() const override {return left;}
    Node* get_right_child() const override {return right;}
};

struct Map
{
    Map() {
        this->root = nullptr;
    }

    /**
     * @brief insert create a node and insert it to the map
     * @param key
     * @param value
     */
    void insert(string key, int value)
    {
        MapNode* node = new MapNode(key, value);
        if(!this->root) {
            this->root = node;
            return;
        }
        this->root->insertNode(node);
    }

    /**
     * @brief get return the value of the node corresponding to key
     * @param key
     * @return
     */
    int get(string key)
    {
        auto search = hash(key);
        auto node = this->root;
        if(!node) return -1;
        while(node && node->key_hash != search) {
            if(search < node->key_hash) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        if(!node) return -1;
        return node->value;
    }

    MapNode* root;
};


int main(int argc, char *argv[])
{
    srand(time(NULL));
	Map map;

    map.insert("Yolo", 20);
    for (std::string& name : TP5::names)
    {
        if (rand() % 3 == 0)
        {
            map.insert(name, rand() % 21);
            qDebug("map[\"%s\"]=%d\n", name.c_str(), map.get(name.c_str()));
        }
    }


    QApplication a(argc, argv);
    MainWindow::instruction_duration = 200;
    w = new MapWindow(*map.root);
    w->show();
    return a.exec();
}
