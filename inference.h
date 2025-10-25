#ifndef INFERENCE_H
#define INFERENCE_H
#include <bits/stdc++.h>
#include "decision_tree.h"
using namespace std;

class tree_metrics:public Decision_tree
{
    protected:
    double acc=0.0;
    friend void metric_calc(tree_metrics &tm); //FRIEND FUNCTION

    public:
    void prediction_display();
    void metrics();
};






#endif