#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Uzel{
private:
    int key;
    Uzel *left, *right;

    Uzel(int k = 0, Uzel *l = NULL, Uzel *r = NULL)
    {key = k; left = l; right = r;}

    friend void rec_del(Uzel*);
    friend class BinTree;
};

class BinTree
{
private:
    Uzel *root;
public:
    BinTree(){root = NULL;}//пустое дерево
    BinTree(int n);
    BinTree(const BinTree&);
    BinTree(const vector<int>&);
    BinTree(const int *arr, int N);
    ~BinTree();

    Uzel *BTree(int n);
    Uzel* get_root(){return root;}
    Uzel* find_k(int k);
    
    Uzel* CopyTree(Uzel*);

    BinTree operator =(const BinTree&);

    int find__k(int k);
    
    void add(int k);
    void del(int k);

    int min();
    int min_r(Uzel *q);

    int KRL(int *a);
    void inarray(Uzel* q, int* a,int& k);
    
    int max();
    void print_level(Uzel* t, int k);
    //del_elem, два обхода(по уровню и глубины)
    //два обхода(по уровню и глубины)

    void print_tree(Uzel*, int k);
    void print(ostream& os, int, Uzel*) const;
    friend ostream & operator << (ostream&, const BinTree&);
};

int BinTree::KRL(int *a){
    int k = 0;
    inarray(root, a, k);
    return k;
}

void BinTree::inarray(Uzel*q, int*a, int&k){
    if(q == NULL) return;
    a[k++] = q -> key;
    inarray(q -> right, a, k);
    inarray(q -> left, a, k);
}

void BinTree::del(int k){
    Uzel* p;
    Uzel* q = root;
    while(q != NULL && q -> key != k){
        p = q;
        if(k < q -> key) q = q -> left;
        if(k > q -> key) q = q -> right;
    }
    if(q == NULL) return;
    if(q -> left == NULL && q -> right == NULL){
        if(p != NULL){
            if(p -> left == q) p -> left = NULL;
            else p -> right = NULL;
        }   
        else root = NULL;
        delete q;
        return;
    }
    if(q -> left != NULL && q -> right != NULL){
        Uzel* change_p = q;
        Uzel *change = q -> left;
        while(change -> right){
            change_p = change;
            change = change -> right;
        }
        q -> key = change -> key;
        if(change_p == q) q -> left = change -> left;
        else change_p -> right= change -> left;
        delete change;
        return;
    }
    Uzel* change;
    if (q -> left != NULL) change = q -> left;
    else change = q -> right;
    if(k < p -> key) p -> left = change;
    else p -> right = change;
    delete q;
}
    
BinTree::BinTree(const vector<int> &arr){
    if(arr.size() > 0){
        Uzel *q = new Uzel(arr[0]);

        int _k = 0, size_arr = arr.size();

        vector<int>::iterator i;

        for (size_t i = 1; i < size_arr; i++){
            _k = arr[i];
            
            Uzel* p = q;
            Uzel* g = p;

            while (p != NULL) {
                if (_k < p->key) {
                    g = p;
                    p = p -> left;
                }
                else {
                    g = p;
                    p = p -> right;
                }
            }

            p = new Uzel(_k);
            if (_k < g -> key) {
                g -> left = p;
            }
            else {
                g -> right = p;
            }
        }
        root = q;
    }else{
        root = NULL;
    }
}

BinTree::BinTree(const int *arr, int N){
    if(N > 0){
        Uzel *q = new Uzel(arr[0]);

        int _k = 0, size_arr = N;

        for (size_t i = 1; i < size_arr; i++){
            _k = arr[i];
            
            Uzel* p = q;
            Uzel* g = p;

            while (p != NULL) {
                if (_k < p->key) {
                    g = p;
                    p = p -> left;
                }
                else {
                    g = p;
                    p = p -> right;
                }
            }

            p = new Uzel(_k);
            if (_k < g -> key) {
                g -> left = p;
            }
            else {
                g -> right = p;
            }
        }
        root = q;
    }else{
        root = NULL;
    }
}


BinTree::~BinTree()
{
    rec_del(root); root = NULL;
}

BinTree BinTree::operator=(const BinTree& BT){
    if(this == &BT) return *this;
    this -> ~BinTree();
    if(BT.root == NULL) root = NULL;
    else{
        root = new Uzel(BT.root -> key);
        root -> left = CopyTree(BT.root -> left);
        root -> right = CopyTree(BT.root -> right);
    }

    return *this;
}


BinTree::BinTree(const BinTree &BN){
    if(BN.root == NULL) root = NULL;
    else{
        root = new Uzel(BN.root -> key);
        root -> left = CopyTree(BN.root -> left);
		root -> right = CopyTree(BN.root -> right);
    }
}


Uzel* BinTree::CopyTree(Uzel *q){
    if(q == NULL) return NULL;
    Uzel *p = new Uzel(q -> key);
    p -> left = CopyTree(q -> left);
    p -> right = CopyTree(q -> right);
    return p;
}



void rec_del(Uzel* q){
    if(q == NULL) return;
    if(q -> left) rec_del(q -> left);
    if(q -> right) rec_del(q -> right);
    delete q;
}


BinTree::BinTree(int n){
    if(root == 0) root = NULL;

    Uzel* q = new Uzel(rand() % 100);
    int k;
    for (int i = 1; i < n; i++) {
        k = rand() % 100;
        Uzel* p = q;//
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
        }//
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

int BinTree::max(){
    if(root == NULL){
        cout << "tree is empty!" << endl;
        return - 1;
    }
    
    Uzel* max = root;
    while(max -> right != NULL) max = max -> right;

    return max -> key;
}

ostream& operator<<(ostream& out, const BinTree& BT) {
    BT.print(out, 0, BT.root);
    return out;
}

int main(int argc, char const *argv[])
{
    srand(time(0));

    // BinTree A(10), B;
    
    // //A.print_tree(A.get_root(), 0); cout << endl;
    // cout << A << endl;
    // // cout << "___________________________________________" << endl;
    // // cout << A.min(); cout << endl;
    // // cout << A.max(); cout << endl;
    // cout << "___________________________________________" << endl;
    // B = A;

    // cout << B; cout << endl;

    // vector<int> arr = {454, 21, 34, 1, 34, 43, 546, 1, 35, 4652};
    // BinTree A(arr);
    // cout << A; cout << endl;
    // A.del(454);
    // cout << "___________________________________________" << endl;
    // cout << A; cout << endl;
    
     int N = 10, _A[N]{8, 11, 15, 19, 7, 2, 13, 12, 10, 18};

    BinTree A(_A, N);
    A.add(15);
    cout << A.min() << endl;
    cout << A.max() << endl;
    if(A.find_k(5)) cout << "1" << endl;
    else cout << "0" << endl;
    cout << A; cout << endl;
    cout << "___________________________________________" << endl;


    return 0;
}
