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

void PreOrderTraversal(TreeNode *node, std::ofstream &out) {
    if (node) {
        out << node->key_ << std::endl;
        PreOrderTraversal(node->left_child_, out);
        PreOrderTraversal(node->right_child_, out);
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

    void Remove(int key) {
        TreeNode *current_node = root_;
        TreeNode *parent = nullptr;
        while (current_node) {
            if (key < current_node->key_) {
                parent = current_node;
                current_node = current_node->left_child_;
            } else if (key > current_node->key_) {
                parent = current_node;
                current_node = current_node->right_child_;
            } else {
                TreeNode *replaced_node = nullptr;
                if (current_node->left_child_ == nullptr) {
                    replaced_node = current_node->right_child_;
                } else if (current_node->right_child_ == nullptr) {
                    replaced_node = current_node->left_child_;
                } else {
                    replaced_node = current_node->right_child_;

                    TreeNode *replaced_node_parent = current_node;

                    while (replaced_node->left_child_) {
                        replaced_node_parent = replaced_node;
                        replaced_node = replaced_node->left_child_;
                    }

                    current_node->key_ = replaced_node->key_;
                    if (replaced_node_parent->right_child_ == replaced_node) {
                        replaced_node_parent->right_child_ = replaced_node->right_child_;
                    } else if (replaced_node_parent->left_child_ == replaced_node) {
                        replaced_node_parent->left_child_ = replaced_node->right_child_;
                    }
                    replaced_node = current_node;
                }

                if(parent == nullptr) {
                    root_ = replaced_node;
                } else if (parent->right_child_ == current_node) {
                    parent->right_child_ = replaced_node;
                } else if (parent->left_child_ == current_node) {
                    parent->left_child_ = replaced_node;
                }
                return;
            }
        }
    }

    void PreOrderTraversal(std::ofstream &out) {
        ::PreOrderTraversal(root_, out);
    }

private:
    TreeNode *root_ = nullptr;
};

int main() {
    BinarySearchTree tree;

    std::string removing_node_str;
    std::string line;
    std::ifstream in("input.txt");
    if (in.is_open()) {
        getline(in, removing_node_str);
        getline(in, line);
        while (getline(in, line)) {
            tree.add(stoi(line));
        }
    }
    in.close();

    std::ofstream out;
    out.open("output.txt");

    tree.Remove(stoi(removing_node_str));

    if (out.is_open()) {
        tree.PreOrderTraversal(out);
    }

    return 0;
}
