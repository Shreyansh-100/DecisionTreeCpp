#include "dt.h"
#include <bits/stdc++.h>
using namespace std;

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
        cout<<i<<" ";
    }
    
    cout<<'\n'<<"-------------------------"<<endl;

}

void tree_metrics::accuracy()
{
    if( size(test_data)==0)
    {
        cerr<<"\nError: Test Data is empty!!"<<endl;
        return;
    }
    else if(size(predictions)==0)
    {
        cerr<<"\nError: Prediction data is  is empty!!"<<endl;
        return;
    }
    double solver=0;
    for(int i=0;i<size(test_data);i++)
    {
        if(test_data[i].back()==predictions[i])
        {
            solver++;
        }
    }

    acc=solver/(double)size(test_data);

    cout<<"Accuracy of your model is: "<<acc<<endl;
}