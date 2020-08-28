#include<iostream>
using namespace std;

#define COUNT 3

template <typename T, typename V>
class AVL{
    public:
        class node{
            public:
                T key;
                V value;
                int height;
                node * left;
                node * right;
                node(T k, V v){
                    height = 1;
                    key = k;
                    value = v;
                    left = NULL;
                    right = NULL;
                }
        };
        node * root = NULL;
        int n;
        void insert(T x, V v){
            root=insertUtil(root, x, v);
        }
        void remove(T x){
            root=removeUtil(root, x);
        }
        node * search(T x){
            return searchUtil(root,x);
        }
        void inorder(){
            inorderUtil(root);
            cout<<endl;
        }
        vector <double> toVector(){
            vector <double> v;
            tovUtil(root, v);
            return v;
        }
        void print() {
            printTree(root, 0);
        }
        node* min() {
            return minValue(root);
        }
        node* max() {
            return maxValue(root);
        }
    private:
        int height(node * head){
            if(head==NULL) return 0;
            return head->height;
        }
        node * rightRotation(node * head){
            node * newhead = head->left;
            head->left = newhead->right;
            newhead->right = head;
            head->height = 1+std::max(height(head->left), height(head->right));
            newhead->height = 1+std::max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        node * leftRotation(node * head){
            node * newhead = head->right;
            head->right = newhead->left;
            newhead->left = head;
            head->height = 1+std::max(height(head->left), height(head->right));
            newhead->height = 1+std::max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        void inorderUtil(node * head){
            if(head==NULL) return ;
            inorderUtil(head->left);
            cout<<head->key<<" ";
            inorderUtil(head->right);
        }

        node * insertUtil(node * head, T x, V v){
            if(head==NULL){
                n+=1;
                node * temp = new node(x, v);
                return temp;
            }
            if(x < head->key) head->left = insertUtil(head->left, x, v);
            else if(x > head->key) head->right = insertUtil(head->right, x, v);
            head->height = 1 + std::max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(x < head->left->key){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal<-1){
                if(x > head->right->key){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }
        node * removeUtil(node * head, T x){
            if(head==NULL) return NULL;
            if(x < head->key){
                head->left = removeUtil(head->left, x);
            }else if(x > head->key){
                head->right = removeUtil(head->right, x);
            }else{
                node * r = head->right;
                if(head->right==NULL){
                    node * l = head->left;
                    delete(head);
                    head = l;
                }else if(head->left==NULL){
                    delete(head);
                    head = r;
                }else{
                    while(r->left!=NULL) r = r->left;
                    head->key = r->key;
                    head->right = removeUtil(head->right, r->key);
                }
            }
            if(head==NULL) return head;
            head->height = 1 + std::max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(x > head->left->key){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal < -1){
                if(x < head->right->key){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }
        void tovUtil(node * head, vector<double> &v){
            if(head==NULL) return ;
            tovUtil(head->left, v);
            v.push_back(head->key);
            tovUtil(head->right, v);
        }
        node * searchUtil(node * head, T x){
            if(head == NULL) return NULL;
            T k = head->key;
            if(k == x) return head;
            if(k > x) return searchUtil(head->left, x);
            if(k < x) return searchUtil(head->right, x);
        }
        void printTree(node *root, int space) {
            if (root == NULL)
                return;
            space += COUNT;
            printTree(root->right, space);
            for (int i = COUNT; i < space; ++i)
                std::cout << "\t";
            std::cout << root->key << " " << root->value << std::endl;
            printTree(root->left, space);
        }

        node *minValue(node *nod)  
        {  
            node *current = nod;  
            
            /* loop down to find the leftmost leaf */
            while (current->left != NULL)  
            {  
                current = current->left;  
            }  
            return(current);  
        }  

        node *maxValue(node *nod)  
        {  
            node *current = nod;  
            
            /* loop down to find the rightmost leaf */
            while (current->right != NULL)  
            {  
                current = current->right;  
            }  
            return(current);  
        }  
};

/*
int main(){
    AVL<float, unsigned long> tmin;
    tmin.insert(1.3, 3);
    tmin.insert(2.4, 4);
    tmin.insert(3.5, 5);
    tmin.insert(4.6, 6);
    tmin.insert(5.7, 7);
    tmin.insert(6.8, 9);
    tmin.insert(7.9, 11);
    tmin.print();
    std::cout << std::endl << std::endl;
    tmin.remove(5.7);
    tmin.remove(6.8);
    tmin.remove(7.9);
    tmin.print();
    std::cout << std::endl << std::endl;
    std::cout << tmin.min()->key << std::endl;
}
*/