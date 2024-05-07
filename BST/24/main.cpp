#include "iostream"
#include <fstream>

struct TreeNode {
    int key_;
    int height_;
    int depth_;
    int number_of_paths_;
    int *path_lengths_ = nullptr;
    TreeNode *left_child_ = nullptr;
    TreeNode *right_child_ = nullptr;
    bool is_root_of_semi_path_;

    explicit TreeNode(int key)
            : key_(key),
              height_(0),
              number_of_paths_(0),
              is_root_of_semi_path_(false) {}
};

void PreOrderTraversal(TreeNode *node, std::ofstream &out) {
    if (node) {
        out << node->key_ << std::endl;
        PreOrderTraversal(node->left_child_, out);
        PreOrderTraversal(node->right_child_, out);
    }
}

// определяет высоту вершины
void FindHeight(TreeNode *node) {
    int child_height = -1;
    TreeNode *right = node->right_child_;
    TreeNode *left = node->left_child_;

    if (right && left) {
        child_height =
                (right->height_ > left->height_)
                ? right->height_
                : left->height_;
    } else if (right) {
        child_height = right->height_;
    } else if (left) {
        child_height = left->height_;
    }

    node->height_ = child_height + 1;
}

// определяет длины путей от веришны до всех листьев
void FindPathLengths(TreeNode *node) {
    TreeNode *right = node->right_child_;
    TreeNode *left = node->left_child_;

    int rn = right ? right->number_of_paths_ : 0;
    int ln = left ? left->number_of_paths_ : 0;

    if (rn + ln == 0) {
        node->number_of_paths_ = 1;
        node->path_lengths_ = new int[1];
        node->path_lengths_[0] = 0;
    } else {
        node->number_of_paths_ = rn + ln;
        node->path_lengths_ = new int[rn + ln];
    }

    int i = 0;
    if (right) {
        for (; i < rn; ++i) {
            node->path_lengths_[i] = right->path_lengths_[i] + 1;
        }
    }
    if (left) {
        for (int j = 0; j < ln; ++j) {
            node->path_lengths_[j + i] = left->path_lengths_[j] + 1;
        }
    }
}

void PostOrderTraversal(TreeNode *node) {
    if (node) {
        PostOrderTraversal(node->left_child_);
        PostOrderTraversal(node->right_child_);
        FindHeight(node);
        FindPathLengths(node);
    }
}

class BinarySearchTree {
public:
    BinarySearchTree()
            : height_(0),
              depth_(0),
              semi_path_roots_counter_(0),
              max_depth_roots_counter_(0),
              max_root_of_semi_path_depth_(0) {};

    ~BinarySearchTree() = default;

    void add(int key) {
        TreeNode **current_node = &root_;
        while (*current_node) {
            TreeNode *node = *current_node;
            if (key < node->key_) {
                current_node = &(node->left_child_);
            } else if (key >= node->key_) {
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

                if (parent == nullptr) {
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


    // определяет глубину вершины
    void NoteDepth(TreeNode *node, int parent_depth) {
        if (node) {
            node->depth_ = parent_depth + 1;
            if (node->depth_ > depth_) {
                depth_ = node->depth_;
            }
            NoteDepth(node->right_child_, node->depth_);
            NoteDepth(node->left_child_, node->depth_);
        }
    }

    // определяет вершины, через которые проходит путь длины tree.height_
    void FindRootsOfSemiPaths(TreeNode *node) {
        if (node) {
            FindRootsOfSemiPaths(node->left_child_);
            FindRootsOfSemiPaths(node->right_child_);

            if (node->depth_ >= max_root_of_semi_path_depth_) {
                if (node->right_child_ && node->left_child_) {
                    int n = node->number_of_paths_;
                    int *arr = node->path_lengths_;

                    for (int i = 0; i < node->right_child_->number_of_paths_; ++i) {
                        int a = height_ - arr[i];
                        if (a != 0) {
                            bool is_success = false;
                            for (int j = node->right_child_->number_of_paths_; j < n; ++j) {
                                if (arr[j] == a) {
                                    node->is_root_of_semi_path_ = true;
                                    ++semi_path_roots_counter_;
                                    max_root_of_semi_path_depth_ = node->depth_;
                                    is_success = true;
                                    break;
                                }
                            }
                            if (is_success) break;
                        }
                    }
                }
            }
        }
    }

    void FindRootsOfSemiPaths() {
        FindRootsOfSemiPaths(root_);
        roots_of_semi_paths_ = new int[semi_path_roots_counter_];
    }


    void CollectRootsOfSemiPaths(TreeNode *node) {
        if (node) {
            if (node->is_root_of_semi_path_ && node->depth_ == max_root_of_semi_path_depth_) {
                roots_of_semi_paths_[max_depth_roots_counter_++] = node->key_;
            }
            CollectRootsOfSemiPaths(node->right_child_);
            CollectRootsOfSemiPaths(node->left_child_);
        }
    }

    void Execute() {
        PostOrderTraversal(root_);
        height_ = root_->height_;

        NoteDepth(root_, -1);
        FindRootsOfSemiPaths();
        CollectRootsOfSemiPaths(root_);

        if (max_depth_roots_counter_ % 2 != 0) {
            Remove(roots_of_semi_paths_[max_depth_roots_counter_ / 2]);
        }

        std::ofstream out;
        out.open("tst.out");

        if (out.is_open()) {
            PreOrderTraversal(root_, out);
        }
    }

private:
    TreeNode *root_ = nullptr;
    int height_;
    int depth_;
    int semi_path_roots_counter_;
    int max_depth_roots_counter_;
    int max_root_of_semi_path_depth_;
    int *roots_of_semi_paths_ = nullptr;
};

int main() {
    BinarySearchTree tree;

    std::string line;
    std::ifstream in("tst.in");
    if (in.is_open()) {
        while (getline(in, line)) {
            tree.add(stoi(line));
        }
    }
    in.close();

    tree.Execute();

    return 0;
}
