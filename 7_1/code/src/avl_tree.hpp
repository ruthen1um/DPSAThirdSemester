#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <stdexcept>
#include <iostream>
#include <stack>

template <typename T>
struct AVLNode {
    using value_type = T;

    value_type value;
    std::size_t height = 1;

    AVLNode* left = nullptr;
    AVLNode* right = nullptr;

    AVLNode(const value_type& value): value{value} {}
};

template <typename T>
class AVLTree {
    using value_type = T;
    using node_type = AVLNode<T>;

private:
    short int get_balance_factor(node_type* p) const {
        if (p == nullptr) {
            return 0;
        }
        return get_height(p->left) - get_height(p->right);
    }

    std::size_t get_height(node_type* p) const {
        if (p == nullptr) {
            return 0;
        }
        return p->height;
    }

    node_type* right_rotation(node_type* p) {
        auto new_p = p->left;
        auto T2 = new_p->right;

        new_p->right = p;
        p->left = T2;

        p->height = 1 + std::max(get_height(p->left), get_height(p->right));
        new_p->height = 1 + \
            std::max(get_height(new_p->left), get_height(new_p->right));

        return new_p;
    }

    node_type* left_rotation(node_type* p) {
        auto new_p = p->right;
        auto T2 = new_p->left;

        new_p->left = p;
        p->right = T2;

        p->height = 1 + std::max(get_height(p->left), get_height(p->right));
        new_p->height = 1 + \
            std::max(get_height(new_p->left), get_height(new_p->right));

        return new_p;
    }

    node_type* insert(node_type* p, const value_type& value) {
        if (p == nullptr) {
            return new node_type(value);
        }

        if (value < p->value) {
            p->left = insert(p->left, value);
        } else if (value > p->value) {
            p->right = insert(p->right, value);
        } else {
            throw std::logic_error("Значение не уникально");
        }

        p->height = 1 + std::max(get_height(p->left), get_height(p->right));

        const auto bf = get_balance_factor(p);

        if (bf > 1 && value < p->left->value) {
            return right_rotation(p);
        }

        if (bf < -1 && value > p->right->value) {
            return left_rotation(p);
        }

        if (bf > 1 && value > p->left->value) {
            p->left = left_rotation(p->left);
            return right_rotation(p);
        }

        if (bf < -1 && value < p -> right->value) {
            p->right = right_rotation(p->right);
            return left_rotation(p);
        }

        return p;
    }

    void traverse_postorder(node_type* p) const {
        if (p == nullptr) {
            return;
        }

        traverse_postorder(p->left);

        traverse_postorder(p->right);

        std::cout << p->value << " ";
    }

    void traverse_inorder(node_type* p) const {
        if (p == nullptr) {
            return;
        }

        traverse_inorder(p->left);

        std::cout << p->value << " ";

        traverse_inorder(p->right);
    }

    void destroy(node_type*& p) {
        if (p) {
            destroy(p->left);
            destroy(p->right);
            delete p;
        }
    }

public:
    node_type* root = nullptr;

    void insert(const value_type& value) {
        root = insert(root, value);
    }

    void traverse_postorder(void) const {
        traverse_postorder(root);
        std::cout << std::endl;
    }

    void traverse_inorder(void) const {
        traverse_inorder(root);
        std::cout << std::endl;
    }

    bool is_empty() const {
        return get_height(root) == 0;
    }

    ~AVLTree() {
        destroy(root);
    }
};


template <typename T>
class AVLTreeInOrderIterator {
    using node_type = AVLNode<T>;

private:
    std::stack<node_type*> traversal;

public:
    AVLTreeInOrderIterator(AVLTree<T>& tree) {
        move_left(tree.root);
    }

    void move_left(node_type* p) {
        while (p) {
            traversal.push(p);
            p = p->left;
        }
    }

    bool has_next() {
        return !traversal.empty();
    }

    node_type* next() {
        if (!has_next()) {
            throw std::runtime_error("Дерево уже пройдено");
        }

        auto p = traversal.top();
        traversal.pop();

        if (p->right) {
            move_left(p->right);
        }

        return p;
    }
};


#endif // AVL_TREE_HPP
