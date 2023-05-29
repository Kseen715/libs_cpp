#ifndef __KSI_FOUR_AR_TREE_HPP
#define __KSI_FOUR_AR_TREE_HPP

#include <iostream>
#include <stack>
#include <queue>

template <typename T>
class FourArTree
{
public:
    FourArTree();
    ~FourArTree();

    void insert(const T &data);
    void remove(const T &data);
    bool find(const T &data) const;

    void print() const;
    void printBFS() const;
    void sortGroup();

private:
    struct Node
    {
        Node(const T &data);
        ~Node();

        T data;
        Node *parent;
        Node *left;
        Node *middleLeft;
        Node *middleRight;
        Node *right;
    };

    Node *root;

    void insert(Node *node, const T &data);
    void remove(Node *node, const T &data);
    bool find(Node *node, const T &data) const;
    void sortGroup(Node *node) const;
};

template <typename T>
void FourArTree<T>::sortGroup(Node *node) const
{
    if (node == nullptr)
    {
        return;
    }

    sortGroup(node->left);
    sortGroup(node->middleLeft);
    sortGroup(node->middleRight);
    sortGroup(node->right);

    if (node->left != nullptr && node->middleLeft != nullptr &&
        node->middleRight != nullptr && node->right != nullptr)
    {
        std::vector<Node *> nodes = {node->left, node->middleLeft,
                                     node->middleRight, node->right};
        std::sort(nodes.begin(), nodes.end(), [](Node *a, Node *b)
                  { return a->data.getAverageScore() >
                           b->data.getAverageScore(); });

        node->left = nodes[0];
        node->middleLeft = nodes[1];
        node->middleRight = nodes[2];
        node->right = nodes[3];
    }
}

template <typename T>
void FourArTree<T>::sortGroup()
{
    sortGroup(root);
}

template <typename T>
FourArTree<T>::FourArTree()
{
    root = nullptr;
}

template <typename T>
FourArTree<T>::~FourArTree()
{
    delete root;
}

template <typename T>
void FourArTree<T>::insert(const T &data)
{
    if (root == nullptr)
    {
        root = new Node(data);
    }
    else
    {
        insert(root, data);
    }
}

template <typename T>
void FourArTree<T>::remove(const T &data)
{
    if (root != nullptr)
    {
        remove(root, data);
    }
}

template <typename T>
bool FourArTree<T>::find(const T &data) const
{
    if (root != nullptr)
    {
        return find(root, data);
    }

    return false;
}

template <typename T>
FourArTree<T>::Node::Node(const T &data)
{
    this->data = data;
    parent = nullptr;
    left = nullptr;
    middleLeft = nullptr;
    middleRight = nullptr;
    right = nullptr;
}

template <typename T>
FourArTree<T>::Node::~Node()
{
    delete left;
    delete middleLeft;
    delete middleRight;
    delete right;
}

template <typename T>
void FourArTree<T>::insert(Node *node, const T &data)
{
    if (data < node->data)
    {
        if (node->left == nullptr)
        {
            node->left = new Node(data);
            node->left->parent = node;
        }
        else
        {
            insert(node->left, data);
        }
    }
    else if (data > node->data)
    {
        if (node->right == nullptr)
        {
            node->right = new Node(data);
            node->right->parent = node;
        }
        else
        {
            insert(node->right, data);
        }
    }
    else
    {
        if (node->middleLeft == nullptr)
        {
            node->middleLeft = new Node(data);
            node->middleLeft->parent = node;
        }
        else if (node->middleRight == nullptr)
        {
            node->middleRight = new Node(data);
            node->middleRight->parent = node;
        }
        else
        {
            insert(node->middleLeft, data);
        }
    }
}

template <typename T>
void FourArTree<T>::remove(Node *node, const T &data)
{
    if (data < node->data)
    {
        if (node->left != nullptr)
        {
            remove(node->left, data);
        }
    }
    else if (data > node->data)
    {
        if (node->right != nullptr)
        {
            remove(node->right, data);
        }
    }
    else
    {
        if (node->middleLeft != nullptr)
        {
            remove(node->middleLeft, data);
        }
        else if (node->middleRight != nullptr)
        {
            remove(node->middleRight, data);
        }
        else
        {
            if (node->left != nullptr)
            {
                node->data = node->left->data;
                remove(node->left, node->data);
            }
            else if (node->right != nullptr)
            {
                node->data = node->right->data;
                remove(node->right, node->data);
            }
            else
            {
                if (node->parent != nullptr)
                {
                    if (node->parent->left == node)
                    {
                        node->parent->left = nullptr;
                    }
                    else if (node->parent->right == node)
                    {
                        node->parent->right = nullptr;
                    }
                    else if (node->parent->middleLeft == node)
                    {
                        node->parent->middleLeft = nullptr;
                    }
                    else if (node->parent->middleRight == node)
                    {
                        node->parent->middleRight = nullptr;
                    }
                }
                else
                {
                    root = nullptr;
                }

                delete node;
            }
        }
    }
}

template <typename T>
bool FourArTree<T>::find(Node *node, const T &data) const
{
    if (data < node->data)
    {
        if (node->left != nullptr)
        {
            return find(node->left, data);
        }
    }
    else if (data > node->data)
    {
        if (node->right != nullptr)
        {
            return find(node->right, data);
        }
    }
    else
    {
        if (node->middleLeft != nullptr)
        {
            return find(node->middleLeft, data);
        }
        else if (node->middleRight != nullptr)
        {
            return find(node->middleRight, data);
        }
        else
        {
            return true;
        }
    }

    return false;
}

// DFS algorithm
template <typename T>
void FourArTree<T>::print() const
{
    if (root != nullptr)
    {
        std::stack<Node *> stack;
        stack.push(root);

        while (!stack.empty())
        {
            Node *node = stack.top();
            stack.pop();

            std::cout << node->data << " ";

            if (node->right != nullptr)
            {
                stack.push(node->right);
            }

            if (node->middleRight != nullptr)
            {
                stack.push(node->middleRight);
            }

            if (node->middleLeft != nullptr)
            {
                stack.push(node->middleLeft);
            }

            if (node->left != nullptr)
            {
                stack.push(node->left);
            }
        }
    }
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const FourArTree<T> &tree)
{
    tree.print();
    return out;
}

template <typename T>
std::istream &operator>>(std::istream &in, FourArTree<T> &tree)
{
    T data;
    in >> data;
    tree.insert(data);
    return in;
}

template <typename T>
void FourArTree<T>::printBFS() const
{
    if (root != nullptr)
    {
        std::queue<Node *> queue;
        queue.push(root);

        while (!queue.empty())
        {
            Node *node = queue.front();
            queue.pop();

            std::cout << node->data << " ";

            if (node->left != nullptr)
            {
                queue.push(node->left);
            }

            if (node->middleLeft != nullptr)
            {
                queue.push(node->middleLeft);
            }

            if (node->middleRight != nullptr)
            {
                queue.push(node->middleRight);
            }

            if (node->right != nullptr)
            {
                queue.push(node->right);
            }
        }
    }
}

#endif // __KSI_FOUR_AR_TREE_HPP
