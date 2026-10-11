#include <bits/stdc++.h>
#include "data_handler.h"
#include "decision_tree.h"
#include "inference.h"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: ./dtree input.csv output.csv\n";
        return 1;
    }

    string input_path = argv[1];
    string output_path = argv[2];

    tree_metrics dtree;

    dtree.read_csv(input_path);

    dtree.train_test_split(0.5);
    dtree.train();

    dtree.predict(output_path);

    metric_calc(dtree,output_path);

    return 0;
}