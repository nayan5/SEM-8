#include <iostream>
#include <omp.h>
#include <stack>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void pBFS(TreeNode* root) {
    std::queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int qs = q.size();
        
        #pragma omp parallel for
        for (int i = 0; i < qs; i++) {
            TreeNode* node;
            
            #pragma omp critical
            {
                node = q.front();
                q.pop();
                std::cout << node->val << " ";  // Process the node
            }
            
            if (node->left) {
                #pragma omp critical
                {
                    q.push(node->left);  // Add the left child to the queue
                }
            }
            
            if (node->right) {
                #pragma omp critical
                {
                    q.push(node->right);  // Add the right child to the queue
                }
            }
        }
    }
}

void pDFS(TreeNode* root) {
    std::stack<TreeNode*> s;
    s.push(root);
    
    while (!s.empty()) {
        int ss = s.size();
        
        #pragma omp parallel for
        for (int i = 0; i < ss; i++) {
            TreeNode* node;
            
            #pragma omp critical
            {
                node = s.top();
                s.pop();
                std::cout << node->val << " ";  // Process the node
            }
            
            if (node->right) {
                #pragma omp critical
                {
                    s.push(node->right);  // Add the right child to the stack
                }
            }
            
            if (node->left) {
                #pragma omp critical
                {
                    s.push(node->left);  // Add the left child to the stack
                }
            }
        }
    }
}

int main() {
    // Construct Tree
    TreeNode* tree = new TreeNode(1);
    tree->left = new TreeNode(2);
    tree->right = new TreeNode(3); 
    tree->left->left = new TreeNode(4);
    tree->left->right = new TreeNode(5);
    tree->right->left = new TreeNode(6);
    tree->right->right = new TreeNode(7);

    /*
    Our Tree Looks like this:
                1
            2       3
        4     5   6    7
        
    */

    std::cout << "Parallel BFS: ";
    pBFS(tree);  // Perform parallel BFS
    std::cout << "\n";
    std::cout << "Parallel DFS: ";
    pDFS(tree);  // Perform parallel DFS

    // Clean up memory (optional)
    delete tree->right->right;
    delete tree->right->left;
    delete tree->left->right;
    delete tree->left->left;
    delete tree->right;
    delete tree->left;
    delete tree;

    return 0;
}
