#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

struct TreeNode {
    long long key_;
    long long left_value_;
    long long right_value_;

    TreeNode() : key_(0), left_value_(0), right_value_(0) {
    }

    explicit TreeNode(long long key)
            : key_(key), left_value_(0), right_value_(0) {
    }

    TreeNode(long long key, long long max_left_child_value, long long min_right_child_value)
            : key_(key),
              left_value_(max_left_child_value),
              right_value_(min_right_child_value) {
    }
};

int main() {
    std::ifstream in("bst.in");

    bool isBST = true;

    TreeNode *tree;

    int str_number = 1;
    long long key;
    int parent_str_num;
    std::string direction;

    if (in.is_open()) {
        // создается дерево (массив вершин)
        std::string line;
        getline(in, line);

        tree = new TreeNode[stoi(line)];

        // добавляется корень дерева
        getline(in, line);
        tree[0] = TreeNode(stoi(line), LLONG_MIN, LLONG_MAX);

        // обрабатываются остальные вершины
        std::string item;
        std::stringstream s;

        while (getline(in, line)) {
            s << line;

            s >> key >> parent_str_num >> direction;

            tree[str_number] = TreeNode(key);
            TreeNode *node = &tree[str_number++];

            TreeNode *parent_node = &tree[parent_str_num - 1];

            if (direction == "L" && key < parent_node->key_ && key >= parent_node->left_value_) {
                node->left_value_ = parent_node->left_value_;
                node->right_value_ = parent_node->key_;
            } else if (direction == "R" && key >= parent_node->key_ && key < parent_node->right_value_) {
                node->left_value_ = parent_node->key_;
                node->right_value_ = parent_node->right_value_;
            } else {
                isBST = false;
                break;
            }
            s.clear();
        }
    }
    in.close();

    std::ofstream out;
    out.open("bst.out");
    if (out.is_open()) {
        out << (isBST ? "YES" : "NO");
    }

    return 0;
}
