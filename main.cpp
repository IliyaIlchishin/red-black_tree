#include <iostream>
using namespace std;

template<typename V>
class RedBlackTree {
private:
    enum class ColorNode {
        RED, BLACK
    };
    struct Node {
        Node* left;
        Node* right;
        V data;
        ColorNode color;

        Node(V data) : data(data), color(ColorNode::RED), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* rotateLeft(Node* myNode) {
        Node* child = myNode->right;
        Node* childLeft = child->left;
        child->left = myNode;
        myNode->right = childLeft;
        return child;
    }

    Node* rotateRight(Node* myNode) {
        Node* child = myNode->left;
        Node* childRight = child->right;
        child->right = myNode;
        myNode->left = childRight;
        return child;
    }

    bool isRed(Node* myNode) {
        return myNode != nullptr && myNode->color == ColorNode::RED;
    }

    void swapColors(Node* node1, Node* node2) {
        ColorNode temp = node1->color;
        node1->color = node2->color;
        node2->color = temp;
    }

    Node* insert(Node* myNode, V data) {
        if (myNode == nullptr) {
            Node* newNode = new Node(data);
            newNode->color = ColorNode::RED;
            return newNode;
        }

        if (myNode->data > data) {
            myNode->left = insert(myNode->left, data);
        } else if (myNode->data < data) {
            myNode->right = insert(myNode->right, data);
        } else {
            return myNode;
        }

        myNode = balanced(myNode);

        return myNode;
    }

    Node* balanced(Node* myNode) {
        if (isRed(myNode->right) && !isRed(myNode->left)) {
            myNode = rotateLeft(myNode);
            swapColors(myNode, myNode->left);
        }

        if (isRed(myNode->left) && isRed(myNode->left->left)) {
            myNode = rotateRight(myNode);
            swapColors(myNode, myNode->right);
        }

        if (isRed(myNode->left) && isRed(myNode->right)) {
            myNode->color = ColorNode::RED;
            myNode->left->color = ColorNode::BLACK;
            myNode->right->color = ColorNode::BLACK;
        }

        return myNode;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->data << " " << (node->color == ColorNode::RED ? "RED" : "BLACK") << "|";
            inorder(node->right);
        }
    }
public:
    RedBlackTree() : root(nullptr) {}
    bool insert(V data) {
        Node *node;

        if (root != nullptr) {
            node = insert(root, data);

            if (node == nullptr) {
                return false;
            }
        } else {
            node = new Node(data);
            root = node;
            root->color = ColorNode::BLACK;
            return true;
        }

        return true;
    }


    void inorder() {
                inorder(root);
            }


};


int main() {
    RedBlackTree<int> tree;
    tree.insert(1);
    tree.insert(52);
    std::cout<< tree.insert(9) << endl;
    tree.insert(11);

}