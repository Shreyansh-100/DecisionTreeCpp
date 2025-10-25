#ifndef DECISION_TREE_H
#define DECISION_TREE_H
#include "data_handler.h"
#include <bits/stdc++.h>
using namespace std;

struct node {
    int feature_index;
    string feature_value;
    double gini;
    string predicted_class;
    node* left;
    node* right;

    node() : feature_index(-1), gini(0.0), left(nullptr), right(nullptr) {}
};

class Decision_tree:public tree_data
{
  
    protected:
        node* root = nullptr;
        double gini = 0.0;
        int max_depth = 6;

        double calculate_gini(vector<vector<string>> subset);
        double calculate_gini(vector<vector<string>> left, vector<vector<string>> right);

        pair<int,string> find_best_split(vector<vector<string>>  &data,vector <bool> &used);

        node* build_tree(vector<vector<string>> data,vector<bool>used,int depth);

        void delete_tree(node* newnode);


    public:
        
        Decision_tree() 
        {
        cout << "\nDecision_tree object created.\n";
        }
    
        vector <string> predictions;
        void train();
        void  predict();  
       

};




#endif