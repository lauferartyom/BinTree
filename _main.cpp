#include <iostream>
#include <ctime>

using namespace std;

class Uzel{
private:
    int key;
    Uzel *left, *right;

    Uzel(int k = 0, Uzel *l = NULL, Uzel *r = NULL)
    {key = k; left = l; right = r;}

    friend class BinTree;
};

class BinTree
{
private:
    Uzel *root;
public:
    BinTree(){root = NULL;}
    BinTree(int n);
    ~BinTree();

    Uzel *BTree(int n);
    Uzel* get_root(){return root;}
    Uzel* find_k(int k);

    int find__k(int k);
    void add(int k);

    int min();
    int min_r(Uzel *q);

    void print_tree(Uzel*, int k);
    void print(ostream& os, int, Uzel*) const;
    friend ostream & operator << (ostream&, const BinTree&);
};


BinTree::~BinTree()
{
}
BinTree::BinTree(int n){
    if(root == 0) root = NULL;

    Uzel* q = new Uzel(rand() % 100);
    int k;
    for (int i = 1; i < n; i++) {
        k = rand() % 100;
        Uzel* p = q;
        Uzel* g = p;
        while (p != NULL) {
            if (k < p -> key) {
                g = p;
                p = p -> left;
            }
            else {
                g = p;
                p = p -> right;
            }
        }
        p = new Uzel(k);
        if (k < g -> key) {
            g -> left = p;
        }
        else {
            g -> right = p;
        }
    }
    root = q;
}
Uzel* BinTree::find_k(int k){
    Uzel *tmp = root;
    
    while(tmp != NULL && tmp -> key != k){
        if(k < tmp -> key) tmp = tmp -> left;
        if(k > tmp -> key) tmp = tmp -> right;
    }

    return tmp;
}
void BinTree::add(int k){
    Uzel* tmp = new Uzel(k);

    if(root == NULL){
        root = tmp;
        return;
    }

    Uzel* q = root;

    while(true){
        if(tmp -> key < q -> key){
            if(q -> left == NULL) break;
            q = q -> left; 
        }else{
            if(q -> right == NULL) break;
            q = q -> right;
        }
    }

    if( tmp -> key < q -> key) q -> left = tmp;
    else q -> right = tmp;

    return;
}
void BinTree::print_tree(Uzel *q, int k){
    if(q == NULL) return;

    print_tree(q -> left, k + 3);

    for (size_t i = 0; i < k; i++) cout << " ";
        cout.width(2);

    cout << q -> key << endl;

    print_tree(q -> right, k + 3);
    
}
int BinTree::min(){
    if(root == NULL){
        cout << "Дерево пустое" << endl;
        return -1;
    }

    Uzel* min = root;

    while(min -> left != NULL) min = min -> left;

    return min -> key;
}
int BinTree::min_r(Uzel *q){
    int m = 0, m1 = 0;
    m = q -> key;

    if(q -> key){m1 = min_r(q -> left); if(m1 < m) m = m1;}
    if(q -> right){m1 = min_r(q -> right); if(m1 < m) m = m1;}

    return m;
}


void BinTree::print(ostream& out, int spaces, Uzel* node) const{
    if (node == NULL) {
        return;
    }
    print(out, spaces+4, node->right);

    for (int i = 0; i < spaces; i++) {
        out << " ";
    }
    out << node->key << endl;

    print(out, spaces+4, node->left);
}

ostream& operator<<(ostream& out, const BinTree& BT) {
    BT.print(out, 0, BT.root);
    return out;
}

int main(int argc, char const *argv[])
{
    srand(time(0));

    BinTree A(10);
    
    //A.print_tree(A.get_root(), 0); cout << endl;
    cout << A << endl;
    cout << "___________________________________________" << endl;
    cout << A.min();
    
    return 0;
}
