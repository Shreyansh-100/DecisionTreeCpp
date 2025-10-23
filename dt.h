#ifndef DT_H
#define DT_H
#include <bits/stdc++.h>
#include "decision_tree.h"
using namespace std;

class tree_metrics:public Decision_tree
{
    protected:
    double acc=0.0;

    public:
    void prediction_display();
    void accuracy();
};






#endif