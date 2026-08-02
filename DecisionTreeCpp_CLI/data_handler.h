#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H
#include <vector>
#include <fstream>
#include <ostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;
class tree_data {
protected:
    int allow=1;
    vector<vector<string>> dataframe;
    vector<vector<string>> train_data;
    vector<vector<string>> test_data;

    vector <string> feature_dataset;

public:
    void read_csv();
    void train_test_split() ; //4: ENCAPSULATION: DATAFRAME WHICH WILL BE USED BY METHOD train_test_split IS DEFINED AND EVALUATED WITHIN THE CLASS
};

#endif 


















