#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    map<pair<int, int>, vector<TreeNode*>> dp;

    vector<TreeNode*> solution(int start, int end) {
        if (start > end) return dp[{start, end}] = {nullptr};
        if (start == end) {
            TreeNode* root = new TreeNode(start);
            return dp[{start, end}] = {root};
        }
        if (dp.find({start, end}) != dp.end()) return dp[{start, end}];

        vector<TreeNode*> ans;
        for (int i = start; i <= end; i++) {
            auto leftSubtrees = solution(start, i - 1);
            auto rightSubtrees = solution(i + 1, end);
            for (auto left : leftSubtrees) {
                for (auto right : rightSubtrees) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    ans.push_back(root);
                }
            }
        }
        return dp[{start, end}] = ans;
    }

    vector<TreeNode*> generateTrees(int n) {
        return solution(1, n);
    }
};

// Helper function to serialize a tree into a vector (level-order traversal)
vector<string> serialize(TreeNode* root) {
    vector<string> result;
    if (!root) return result;

    vector<TreeNode*> queue = {root};
    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.erase(queue.begin());
        if (node) {
            result.push_back(to_string(node->val));
            queue.push_back(node->left);
            queue.push_back(node->right);
        } else {
            result.push_back("null");
        }
    }

    // Remove trailing "null" values
    while (!result.empty() && result.back() == "null") {
        result.pop_back();
    }

    return result;
}

// Helper function to print a vector of serialized trees
void printTrees(const vector<TreeNode*>& trees) {
    cout << "[";
    for (size_t i = 0; i < trees.size(); ++i) {
        vector<string> serializedTree = serialize(trees[i]);
        cout << "[";
        for (size_t j = 0; j < serializedTree.size(); ++j) {
            cout << serializedTree[j];
            if (j + 1 < serializedTree.size()) cout << ",";
        }
        cout << "]";
        if (i + 1 < trees.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Example 1
    int n1 = 3;
    cout << "Input: n = " << n1 << endl;
    vector<TreeNode*> result1 = solution.generateTrees(n1);
    cout << "Output: ";
    printTrees(result1);

    // Example 2
    int n2 = 1;
    cout << "Input: n = " << n2 << endl;
    vector<TreeNode*> result2 = solution.generateTrees(n2);
    cout << "Output: ";
    printTrees(result2);

    return 0;
}
