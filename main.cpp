#include <iostream>
using namespace std;

template<typename V>
class RedBlackTree {
private:
    enum class ColorNode {
        RED, BLACK
    };
    // определяем узел дерева
    struct Node {
        Node* left;
        Node* right;
        V data;
        ColorNode color;

        Node(V data) : data(data), color(ColorNode::RED), left(nullptr), right(nullptr) {}
    };

    Node* root;
//  поворот узла влево
    Node* rotateLeft(Node* myNode) {
        Node* child = myNode->right;
        Node* childLeft = child->left;
        child->left = myNode;
        myNode->right = childLeft;
        return child;
    }
//  поворот узла влево
    Node* rotateRight(Node* myNode) {
        Node* child = myNode->left;
        Node* childRight = child->right;
        child->right = myNode;
        myNode->left = childRight;
        return child;
    }
// если узел красный, возвращаем true
    bool isRed(Node* myNode) {
        return myNode != nullptr && myNode->color == ColorNode::RED;
    }

    void swapColors(Node* node1, Node* node2) {
        ColorNode temp = node1->color;
        node1->color = node2->color;
        node2->color = temp;
    }
// Рекурсивный метод вставки нового узла в дерево
    Node* insert(Node* myNode, V data) {
        // Если узел пуст, создаем новый узел с данными data и цветом RED
        if (myNode == nullptr) {
            Node* newNode = new Node(data);
            newNode->color = ColorNode::RED;
            return newNode;
        }

        // Если значение data меньше, чем значение данных в текущем узле, идем влево
        if (myNode->data > data) {
            myNode->left = insert(myNode->left, data);
            // Если значение data больше, чем значение данных в текущем узле, идем вправо
        } else if (myNode->data < data) {
            myNode->right = insert(myNode->right, data);
            // Если значение data равно значению данных в текущем узле, возвращаем текущий узел
        } else {
            return myNode;
        }

        // делаем балансировку
        myNode = balanced(myNode);

        return myNode;
    }
// Балансировка дерева

    Node* balanced(Node* myNode) {
        // Красный узел является правым потомком, а его левый потомок черный.
        if (isRed(myNode->right) && !isRed(myNode->left)) {
            myNode = rotateLeft(myNode);
            swapColors(myNode, myNode->left);
        }

        if (isRed(myNode->left) && isRed(myNode->left->left)) {
            // Красный узел является левым потомком, а его левый потомок тоже красный.
            myNode = rotateRight(myNode);
            swapColors(myNode, myNode->right);
        }

        if (isRed(myNode->left) && isRed(myNode->right)) {
            // Красный узел имеет двух красных потомков.
            myNode->color = ColorNode::RED;
            myNode->left->color = ColorNode::BLACK;
            myNode->right->color = ColorNode::BLACK;
        }

        return myNode;
    }

    void inorder(Node* node) {
        // Рекурсивная функция для обхода дерева в порядке возрастания и печати значений узлов вместе с их цветом.
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->data << " " << (node->color == ColorNode::RED ? "RED" : "BLACK") << "|";
            inorder(node->right);
        }
    }
public:
    // Конструктор класса. Устанавливает корень в nullptr.
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

// Публичная функция для вызова обхода дерева в порядке возрастания и печати значений узлов вместе с их цветом.
    void inorder() {
                inorder(root);
            }


};


int main() {
    RedBlackTree<int> tree;
    tree.insert(15);
    tree.insert(11);
    tree.insert(32);
    tree.insert(3);
    tree.insert(9);
    tree.insert(25233);
    tree.inorder();


    return 0;
}