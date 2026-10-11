#ifndef INFERENCE_H
#define INFERENCE_H
#include <bits/stdc++.h>
#include "decision_tree.h"
using namespace std;

class tree_metrics:public Decision_tree
{
    protected:
    friend vector<double> metric_calc(tree_metrics &tm , const string &output_path); //FRIEND FUNCTION

    public:
    void prediction_display();
    
};
#endif








