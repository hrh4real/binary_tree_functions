#include <iostream>
#include "classBinaryTree.h"
#include <queue>
#include <vector>
// #include "classNode.cpp"
using namespace std;

template <typename T>

class listNode{
    T data;
    listNode<T> next;
    public :
    listNode(T data){
        this->data = data;
    }
};

class node{
    public :
    int data;
    node * next;

    node(int data){
        this->data = data;
        next = NULL;
    }
};

binTree<int> *searchNode(binTree<int> *root, int num)
{
    if (root == NULL)
    {
        cout << "Element Isn't Found : " << endl;
        exit(1);
    }
    if (root->data == num)
    {
        return root;
    }
    else if (root->data > num)
    {
        searchNode(root->left, num);
    }
    else
    {
        searchNode(root->right, num);
    }

    return NULL;
}

void treeToListTraversal(binTree<int>* root, node*& prev, node*& head){
    if (root == NULL)
    {
        return;
    }
    
    treeToListTraversal(root->left, prev, head);

    node * newNode = new node(root->data);

    if (prev != NULL)
    {
        prev->next = newNode;
    } else {
        head = newNode;
    }
    prev = newNode;

    treeToListTraversal(root->right, prev, head);
}

node * treeToSortedList(binTree<int> * root){
    node * prev = NULL;
    node * head = NULL;
    treeToListTraversal(root, prev, head);
    return head;
}

int bstMin(binTree<int> *root)
{
    if (root == NULL)
    {
        cout << "Tree doesn't exist : " << endl;
        return -1;
    }

    if (root->left == NULL)
    {
        return root->data;
    }
    else
    {
        return bstMin(root->left);
    }
}

int mini_mum(binTree<int> *root)
{
    if (root == NULL)
    {
        return INT_MAX;
    }

    return min(root->data, min(mini_mum(root->left), mini_mum(root->right)));
}

int maxi_mum(binTree<int> *root)
{
    if (root == NULL)
    {
        return INT_MIN;
    }

    return max(root->data, max(maxi_mum(root->left), maxi_mum(root->right)));
}

int bstMax(binTree<int> *root)
{
    if (root == NULL)
    {
        cout << "Tree doesn't exist : " << endl;
        return -1;
    }
    if (root->right == NULL)
    {
        return root->data;
    }
    else
    {
        return bstMax(root->right);
    }
}

bool checkBst(binTree<int> *root)
{
    if (root == NULL)
    {
        return false;
    }
    return (root->data > maxi_mum(root->left)) && (root->data < mini_mum(root->right)) && checkBst(root->left) && checkBst(root->right);
}

vector<int> *getRootToNode(binTree<int> *root, int num)
{
    if (root == NULL)
    {
        // cout << "Tree doesn't exist" << endl;
        return NULL;
    }
    if (root->data == num)
    {
        vector<int> *output = new vector<int>();
        output->push_back(root->data);
        return output;
    }
    vector<int> *leftOutput = getRootToNode(root->left, num);
    if (leftOutput != NULL)
    {
        leftOutput->push_back(root->data);
        return leftOutput;
    }
    vector<int> *rightOutput = getRootToNode(root->right, num);
    if (rightOutput != NULL)
    {
        rightOutput->push_back(root->data);
        return rightOutput;
    }
    else
    {
        return NULL;
    }
}

binTree<int> *takeInput()
{
    int root_data;
    cout << "Enter Root Data " << endl;
    cin >> root_data;
    if (root_data == -1)
    {
        return NULL;
    }

    binTree<int> *root = new binTree<int>(root_data);
    binTree<int> *left = takeInput();
    binTree<int> *right = takeInput();

    root->left = left;
    root->right = right;

    return root;
}

int treeHeight(binTree<int> *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int lh = treeHeight(root->left);
    int rh = treeHeight(root->right);

    return 1 + max(lh, rh);
}

void printTree(binTree<int> *root)
{
    if (root == NULL)
    {
        // cout << "Tree Doesn't Exist : " << endl;
        return;
    }

    cout << root->data << " : ";
    if (root->left)
    {
        cout << "L : " << root->left->data << " ";
    }
    if (root->right)
    {
        cout << "R : " << root->right->data << " ";
    }

    cout << endl;

    printTree(root->left);
    printTree(root->right);
    return;
}

binTree<int> *takeInputLeveLWise()
{
    int root_data;
    cout << "Enter Root Data : " << endl;
    cin >> root_data;

    if (root_data == -1)
    {
        return NULL;
    }

    binTree<int> *node = new binTree<int>(root_data);
    queue<binTree<int> *> pending_nodes;
    pending_nodes.push(node);
    while (pending_nodes.size())
    {
        binTree<int> *front = pending_nodes.front();
        pending_nodes.pop();
        cout << "Enter Left Child of " << front->data << " : ";
        int leftChild_data;
        cin >> leftChild_data;
        if (leftChild_data != -1)
        {
            binTree<int> *child = new binTree<int>(leftChild_data);
            front->left = child;
            pending_nodes.push(child);
        }
        cout << "Enter right Child of " << front->data << " : ";
        int rightChild_data;
        cin >> rightChild_data;
        if (rightChild_data != -1)
        {
            binTree<int> *child = new binTree<int>(rightChild_data);
            front->right = child;
            pending_nodes.push(child);
        }
    }

    return node;
}

void printLeveLwise(binTree<int> *root)
{
    if (root == NULL)
    {
        // cout << "Tree Doesn't Exist : " << endl;
        return;
    }
    cout << endl;

    queue<binTree<int> *> q;
    q.push(root);
    while (q.empty() == false)
    {
        int nodeCount = q.size();

        while (nodeCount > 0)
        {
            binTree<int> *front = q.front();
            cout << front->data << " ";
            q.pop();
            if (front->left != NULL)
            {
                q.push(front->left);
            }
            if (front->right != NULL)
            {
                q.push(front->right);
            }

            nodeCount--;
        }

        cout << endl;
    }
}


binTree<int>* deleteLeaf(binTree<int>* root){
    if(root == NULL){
        return NULL;
    }

    if (root->left == NULL && root->right == NULL)
    {
        free(root);

        return NULL;
    }

    root->left = deleteLeaf(root->left);
    root->right = deleteLeaf(root->right);
    
    return root;
}

bool isBalanced(binTree<int>* root){
    if (root == NULL)
    {
        return true;
    }
    return treeHeight(root->left) == treeHeight(root->right);
}

binTree<int>* construct_tree(int arr[], int start, int end){
    if (start > end)
    {
        return NULL;
    }
    
    int mid = (end + start) / 2;
    binTree<int> * node = new binTree<int>(arr[mid]);
    
    node->left = construct_tree(arr, start, mid - 1);
    node->right = construct_tree(arr, mid + 1, end);

    return node;  
}
int total_nodes(binTree<int>* node){
    if (node == NULL)
    {
        return 0;
    }
    return 1 + total_nodes(node->left) + total_nodes(node->right);
}
void InOrderTraversal(binTree<int>* node, vector<int> &result){
    if (node)
    {
        InOrderTraversal(node->left, result);
        result.push_back(node->data);
        InOrderTraversal(node->right, result);
    }
    
}
vector<int> treeSortedArray(binTree<int>* root){
    vector<int> result;
    InOrderTraversal(root, result);
    return result;
}
void preOrder(binTree<int>* node)
{
    if (node == NULL)
        return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}



// 1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
// 1 2 3 -1 -1 -1 -1
int main()
{
     

    binTree<int> *root = takeInputLeveLWise();
    cout << endl;
    // printTree(root);
    printLeveLwise(root);

    // cout<< "Tree Height : " << treeHeight(root) << endl;

    if (isBalanced(root))
    {
        cout << "Tree is Balanced " << endl;
    } else {
        cout << "Tree is not Balanced " << endl;
    }
    
    root = deleteLeaf(root);

    printLeveLwise(root);

    preOrder(root);

    /*

    vector<int> *nodePath = getRootToNode(root, 9);

    for (int i = 0; i < nodePath->size(); i++)
    {
        cout << (*nodePath)[i] << " ";
    }

    cout << endl;

    if (checkBst(root))
    {
        cout << "Tree is Binary " << endl;
    }
    else{
        cout << "Tree isn't Binary" << endl;
    }

    cout << "Minimum Element : " << mini_mum(root) << endl ; 
    cout << "Maximum Element : " << maxi_mum(root) << endl ; 

    

    int arr[] = {1,2,3,4,5,6,7};
    int n = sizeof(arr) / sizeof(arr[0]);
    binTree<int> * sorted_tree = construct_tree(arr, 0, n - 1);

    cout << "Sorted Array to Tree : " << endl;
    preOrder(sorted_tree);
    cout << endl;
    vector<int> result = treeSortedArray(sorted_tree);
    cout << " Tree to Sorted Array : " << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    */


    delete root;


    // delete nodePath;
    // delete sorted_tree;
}
