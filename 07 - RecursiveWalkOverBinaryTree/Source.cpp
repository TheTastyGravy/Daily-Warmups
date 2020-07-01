#include <iostream>
#include <functional>


struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int data, Node* left = nullptr, Node* right = nullptr) :
        data(data), left(left), right(right) {}
};


template<typename R>
void WalkThroughTreePre(Node* root, std::function<R(Node* node)> f)
{
    // At the end of a tree, this function will be passed a nullptr child
    if (root == nullptr)    return;


    // Call the function, passing the root
    f(root);

    // Recursion for children
    WalkThroughTreePre<R>(root->left, f);
    WalkThroughTreePre<R>(root->right, f);
}
template<typename R>
void WalkThroughTreePost(Node* root, std::function<R(Node* node)> f)
{
    // At the end of a tree, this function will be passed a nullptr child
    if (root == nullptr)    return;


    // Recursion for children
    WalkThroughTreePost<R>(root->left, f);
    WalkThroughTreePost<R>(root->right, f);

    // Call the function, passing the root
    f(root);
}


void PrintTree(Node* root)
{
    // Pass lambda to output the node's value
    WalkThroughTreePre<void>(root, [](Node* node) { std::cout << node->data << " "; });
}
void DeleteTree(Node* root)
{
    // Pass lambda to delete the node
    WalkThroughTreePost<void>(root, [](Node* node) { delete node; });
}


int main(int argc, char** argv)
{
    /************************
               50
       20             70
     10  30         60  80
    ************************/
    Node* root = new Node(50,
        new Node(20, new Node(10), new Node(30)),
        new Node(70, new Node(60), new Node(80))
    );

    PrintTree(root);
    // pre - 50, 20, 10, 30, 70, 60, 80
    // post - 10, 30, 20, 60, 80, 70, 50

    DeleteTree(root);
    return 0;
}