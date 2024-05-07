#include "iostream"
#include <fstream>

struct TreeNode {

    int key_;
    TreeNode *left_child_ = nullptr;
    TreeNode *right_child_ = nullptr;

    explicit TreeNode(int key)
            : key_(key) {
    }
};

void pre_order_traversal(TreeNode *node, std::ofstream &out) {
    if (node) {
        out << node->key_ << std::endl;
        pre_order_traversal(node->left_child_, out);
        pre_order_traversal(node->right_child_, out);
    }
}

class BinarySearchTree {
public:
    BinarySearchTree() = default;

    ~BinarySearchTree() = default;

    void add(int key) {
        TreeNode **current_node = &root_;
        while (*current_node) {
            TreeNode *node = *current_node;
            if (key < node->key_) {
                current_node = &(node->left_child_);
            } else if (key > node->key_) {
                current_node = &(node->right_child_);
            } else return;
        }
        *current_node = new TreeNode(key);
    }

    void pre_order_traversal(std::ofstream &out) {
        ::pre_order_traversal(root_, out);
    }

private:
    TreeNode *root_ = nullptr;
};

int main() {
    BinarySearchTree tree;

    std::string line;
    std::ifstream in("input.txt");
    if (in.is_open()) {
        while (getline(in, line)) {
            tree.add(stoi(line));
        }
    }
    in.close();

    std::ofstream out;
    out.open("output.txt");

    if (out.is_open()) {
        tree.pre_order_traversal(out);
    }

    return 0;
}
