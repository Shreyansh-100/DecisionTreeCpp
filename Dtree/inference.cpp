#include "inference.h"
#include <bits/stdc++.h>
using namespace std;

namespace
{
    vector<string> sorted_labels(const vector<vector<string>> &test_data, const vector<string> &predictions, int n)
    {
        set<string> labels;

        for (int i = 0; i < n; i++)
        {
            labels.insert(test_data[i].back());
            labels.insert(predictions[i]);
        }

        return vector<string>(labels.begin(), labels.end());
    }
}

void tree_metrics::prediction_display()
{
    if(size(predictions)==0)
    {
        cerr<<"\nError: No predictions made till now!!\n";
        return;
    }
    cout<<"\nPredictions: -"<<endl;
    cout<<"-------------------------"<<endl;  
    for(auto i:predictions)
    {
        cout<<i<<"-> ";
    }
    
    cout<<'\n'<<"-------------------------"<<endl;

}

//->FRIEND FUNCTION OF tree_metrics class
#include <fstream>
#include <iterator>

vector<double> metric_calc(tree_metrics &tm, const string &output_path)
{
    if (tm.test_data.empty())
    {
        cerr << "\nError: Test Data is empty!!" << endl;
        return {};
    }

    if (tm.predictions.empty())
    {
        cerr << "\nError: Prediction data is empty!!" << endl;
        return {};
    }

    double correct = 0;

    int n = min(tm.test_data.size(), tm.predictions.size());

    for (int i = 0; i < n; i++)
    {
        if (tm.test_data[i].back() == tm.predictions[i])
            correct++;
    }

    double accuracy = correct / n;

    cout << "Accuracy: " << accuracy << endl;

    // Read existing CSV
    ifstream in(output_path);
    string existing(
        (istreambuf_iterator<char>(in)),
        istreambuf_iterator<char>());
    in.close();

    // Rewrite CSV with metrics at the top
    ofstream out(output_path);

    out << "Decision Tree Report\n";
    out << "Accuracy," << accuracy << "\n";

    vector<string> labels = sorted_labels(tm.test_data, tm.predictions, n);

    if (!labels.empty())
    {
        double precision_sum = 0.0;
        double recall_sum = 0.0;
        double f1_sum = 0.0;

        for (const auto &label : labels)
        {
            int tp = 0;
            int fp = 0;
            int fn = 0;

            for (int i = 0; i < n; i++)
            {
                bool actual_is_label = tm.test_data[i].back() == label;
                bool predicted_is_label = tm.predictions[i] == label;

                if (actual_is_label && predicted_is_label)
                    tp++;
                else if (!actual_is_label && predicted_is_label)
                    fp++;
                else if (actual_is_label && !predicted_is_label)
                    fn++;
            }

            double precision = (tp + fp) ? (double)tp / (tp + fp) : 0.0;
            double recall = (tp + fn) ? (double)tp / (tp + fn) : 0.0;
            double f1 = (precision + recall)
                            ? (2.0 * precision * recall) / (precision + recall)
                            : 0.0;

            precision_sum += precision;
            recall_sum += recall;
            f1_sum += f1;
        }

        double precision = precision_sum / labels.size();
        double recall = recall_sum / labels.size();
        double f1 = f1_sum / labels.size();

        out << "Precision," << precision << "\n";
        out << "Recall," << recall << "\n";
        out << "F1 Score," << f1 << "\n\n";

        out << existing;
        out.close();

        return {precision, recall, f1};
    }

    out << "\n";
    out << existing;
    out.close();

    return {};
}

  
