#include "decision_tree.h"
#include <bits/stdc++.h>
using namespace std;
double Decision_tree::calculate_gini(vector<vector<string>> subset)
{
    if (subset.empty())
        return 0.0;

    unordered_map<string, int> label;
    for (auto &row : subset)
        label[row.back()]++;

    double impurity = 0.0;
    int total_size = subset.size();

    for (auto &it : label)
    {
        double pc = static_cast<double>(it.second) / total_size;
        impurity += pc * (1 - pc);
    }

    return impurity;
}


double Decision_tree::calculate_gini(vector<vector<string>> leftsub, vector<vector<string>> rightsub) //5: FUNCTION OVERLOADING
{
    int total_size = leftsub.size() + rightsub.size();
    if (total_size == 0)
        return 0.0;

    double left_gini = calculate_gini(leftsub);
    double right_gini = calculate_gini(rightsub);

    double weighted_gini_impurity =
        ((double)leftsub.size() / total_size * left_gini) +
        ((double)rightsub.size() / total_size * right_gini);

    return weighted_gini_impurity;
}


pair<int, string> Decision_tree::find_best_split(vector<vector<string>> &data, vector<bool> &used)
{
    int best_feature_index = -1;
    double best_gini = numeric_limits<double>::max();
    string best_split_value = "";

    for (int i = 0; i < feature_dataset.size(); i++)
    {
        if (used[i])
            continue;

        set<string> uniq_val;
        for (auto &row : data)
            uniq_val.insert(row[i]);

        vector<vector<string>> leftsub, rightsub;

        for (auto &val : uniq_val)
        {
            leftsub.clear();
            rightsub.clear();

            for (auto &row : data)
            {
                if (row[i] == val)
                    leftsub.push_back(row);
                else
                    rightsub.push_back(row);
            }

            double weighted_gini = calculate_gini(leftsub, rightsub);

            if (weighted_gini < best_gini)
            {
                best_gini = weighted_gini;
                best_feature_index = i;
                best_split_value = val;
            }
        }
    }
    return {best_feature_index, best_split_value};
}


node *Decision_tree::build_tree(vector<vector<string>> data, vector<bool> used, int depth)
{
    if (data.empty())
        return nullptr;

    // stopping condition 1: pure split
    
    string label_pure = data[0].back();
    bool same_labels = true;
    for (auto& row : data)
    {
        if (row.back() != label_pure) 
        {
            same_labels = false;
            break;
        }
    }

    if (same_labels)
    {
        node* leaf = new node();
        leaf->predicted_class = label_pure;
        return leaf;
    }

    // ----- Stopping condition 2: Max depth reached -----
    if (depth >= max_depth)
    {
        unordered_map<string, int> label_count;
        for (auto& row : data)
            label_count[row.back()]++;

        string majority_label;
        int max_count = 0;
        for (auto& it : label_count)
        {
            if (it.second > max_count)
            {
                max_count = it.second;
                majority_label = it.first;
            }
        }

        node* leaf = new node();
        leaf->predicted_class = majority_label;
        return leaf;
    }

    // ----- Stopping condition 3: All features have been used -----
    bool all_used = true;
    for (bool flag : used)
    {
        if (!flag)
        {
            all_used = false;
            break;
        }
    }

    if (all_used)
    {
        unordered_map<string, int> label_count;
        for (auto& row : data)
            label_count[row.back()]++;

        string majority_label;
        int max_count = 0;
        for (auto& it : label_count)
        {
            if (it.second > max_count)
            {
                max_count = it.second;
                majority_label = it.first;
            }
        }

        node* leaf = new node();
        leaf->predicted_class = majority_label;
        return leaf;
    }

  pair<int, string> best_found = find_best_split(data, used);
    int best_feature = best_found.first;
    string best_val = best_found.second;

    if (best_feature == -1)
    {
        node *leaf = new node();
        leaf->predicted_class = data[0].back();
        return leaf;
    }

    vector<vector<string>> leftdata, rightdata;
    for (auto &row : data)
    {
        if (row[best_feature] == best_val)
            leftdata.push_back(row);
        else
            rightdata.push_back(row);
    }

    auto used_left = used;
    auto used_right = used;
    used_left[best_feature] = true;
    used_right[best_feature] = true;

    node *root = new node();
    root->feature_index = best_feature;
    root->feature_value = best_val;
    root->gini = calculate_gini(leftdata, rightdata);

    root->left = build_tree(leftdata, used_left, depth + 1);
    root->right = build_tree(rightdata, used_right, depth + 1);

    return root;
}


void Decision_tree::train()
{
    if (train_data.empty())
    {
        cerr << "Error: No training data loaded" << endl;
        return;
    }

    vector<bool> used(feature_dataset.size(), false);
    root = build_tree(train_data, used, 0);

    cout << "\nTraining Completed!!" << endl;
}


void Decision_tree::predict()
{
    if (!root)
    {
        cerr << "\nError: Model is not trained yet!!" << endl;
        return;
    }

    for (auto &test : test_data)
    {
        node *curr = root;
        while (curr->left && curr->right)
        {
            string feature_val = test[curr->feature_index];
            if (feature_val == curr->feature_value)
                curr = curr->left;
            else
                curr = curr->right;
        }
        predictions.push_back(curr->predicted_class);
    }
}