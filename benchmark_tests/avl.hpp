#include <iostream>
#include <stack>

bool compare (const std::pair<double, unsigned long> &a, const std::pair<double, unsigned long> &b) {
    return a.first < b.first;
}

class AVL{
    public:
        class node{
            public:
                std::pair<double, unsigned long> key;
                int height;
                node * left;
                node * right;
                node(std::pair<double, unsigned long> k){
                    height = 1;
                    key = k;
                    left = NULL;
                    right = NULL;
                }
        };

        class iterator {
        private: 
            std::stack<node*> q; 
        public: 
            // Constructor for the class 
            iterator(node* root) 
            { 
                // Initializing stack 
                node* curr = root; 
                while (curr != NULL) 
                    q.push(curr), curr = curr->left; 
            } 
        
            // Function to return 
            // current element iterator 
            // is pointing to 
            node* curr() 
            { 
                return q.top(); 
            } 
        
            // Function to iterate to next 
            // element of BST 
            void next() 
            { 
                node* curr = q.top()->right; 
                q.pop(); 
                while (curr != NULL) 
                    q.push(curr), curr = curr->left; 
            } 
        
            // Function to check if 
            // stack is empty 
            bool isEnd() 
            { 
                return !(q.size()); 
            } 
        }; 

        node * root = NULL;
        int n;
        void insert(std::pair<double, unsigned long> x){
            root=insertUtil(root, x);
        }
        void remove(double x){
            root=removeUtil(root, x);
        }
        node * search(std::pair<double, unsigned long> x){
            return searchUtil(root,x);
        }
        void inorder(){
            inorderUtil(root);
            std::cout << std::endl;
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
            head->height = 1 + std::max(height(head->left), height(head->right));
            newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        node * leftRotation(node * head){
            node * newhead = head->right;
            head->right = newhead->left;
            newhead->left = head;
            head->height = 1 + std::max(height(head->left), height(head->right));
            newhead->height = 1 + std::max(height(newhead->left), height(newhead->right));
            return newhead;
        }

        void inorderUtil(node * head){
            if(head==NULL) return ;
            inorderUtil(head->left);
            std::cout << head->key.first << " ";
            inorderUtil(head->right);
        }

        node * insertUtil(node * head, std::pair<double, unsigned long> x){
            if(head==NULL){
                n+=1;
                node * temp = new node(x);
                return temp;
            }
            if(compare(x, head->key)) head->left = insertUtil(head->left, x);
            else if(x > head->key) head->right = insertUtil(head->right, x);
            head->height = 1 + std::max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(compare(x, head->left->key)){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal<-1){
                if (!compare(x, head->right->key)) {
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }
        node * removeUtil(node * head, double x){
            if(head==NULL) return NULL;
            if (x < head->key.first) {
                head->left = removeUtil(head->left, x);
            } else if (x > head->key.first) {
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
                    head->right = removeUtil(head->right, r->key.first);
                }
            }
            if(head==NULL) return head;
            head->height = 1 + std::max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(x > head->left->key.first) {
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal < -1){
                if (x < head->right->key.first) {
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }
        node * searchUtil(node * head, std::pair<double, unsigned long> x){
            if(head == NULL) return NULL;
            std::pair<double, unsigned long> k = head->key;
            if(k == x) return head;
            if(!compare(k, x)) return searchUtil(head->left, x);
            if(compare(k, x)) return searchUtil(head->right, x);
        }
};