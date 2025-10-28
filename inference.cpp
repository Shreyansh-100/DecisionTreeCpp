#include "inference.h"
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
        cout<<i<<"-> ";
    }
    
    cout<<'\n'<<"-------------------------"<<endl;

}

//->FRIEND FUNCTION OF tree_metrics class
void metric_calc(tree_metrics &tm) 
{
    if( size(tm.test_data)==0)
    {
        cerr<<"\nError: Test Data is empty!!"<<endl;
        return;
    }
    else if(size(tm.predictions)==0)
    {
        cerr<<"\nError: Prediction data is  is empty!!"<<endl;
        return;
    }


    unordered_map <string,int>ref;
    for(auto i: tm.predictions)
    {
        ref[i]++;
    }
    
    double acc=0.0;
    
    for(int i=0;i<size(tm.test_data) && i<size(tm.predictions);i++)
    {
        if(tm.test_data[i].back()==tm.predictions[i])
        {
            acc++;
        }
    }
    cout<<"Accuracy: "<<(double)( acc/size(tm.predictions))<<endl;

    if(size(ref)==2)
    {
        //if binary classification model
        int tp=0;
        int tn=0;
        int fn=0;
        int fp=0;

        for(int i=0;i<size(tm.test_data);i++)
        {
            if(tm.test_data[i].back()=="yes" && tm.predictions[i]=="yes")
            {
                tp++;
            }
            else if(tm.test_data[i].back()=="no" && tm.predictions[i]=="no")
            {
                tn++;
            }
            else if(tm.test_data[i].back()=="yes" && tm.predictions[i]=="yes")
            {
                fn++;
            }
            else if(tm.test_data[i].back()=="no" && tm.predictions[i]=="yes")
            {
                fp++;
            }
        }

        double precision= (double) tp/(tp+fp);
        double recall= (double) tp/(tp+fn);
        double f1= (double) 2*precision*recall/(precision+recall);

        cout<<"Precision:"<<precision<<endl;
        cout<<"Recall:"<<recall<<endl;
        cout<<"F1 Score:"<<f1<<endl;
    }
    return;

  
}
