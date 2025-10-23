#include "data_handler.h"
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <random>
 #include <unistd.h>
using namespace std;

void tree_data::read_csv() {
    fstream iptr;

    iptr.open("D:/project/Project_oops/read.csv",ios::in);

    if (!iptr.is_open()) {
        allow=0;
        std::cerr << "Error: Could not open file " << endl;
        perror("Reason");
        return;
    }

    vector <string> row_data;
    string line,word;

   while (std::getline(iptr, line)) {   // Read line by line
        row_data.clear();

        std::stringstream s(line);
        while (std::getline(s, word, ',')) {  // Split by commas
            row_data.push_back(word);
        }

     
        if (!row_data.empty()) {
            dataframe.push_back(row_data);
        }
    }

    iptr.close();

}

void tree_data::train_test_split() {
    if(allow)
    {
        cout<<"\nEnter test_size: ";
        double test_size;
        cin>>test_size;

        if(dataframe.empty())
        {
            cerr<<"Dataframe is empty!! Load the Data before splitting \n";
            return ;
        }

        if(test_size<0.0 || test_size>1.0)
        {
            cerr<<"Invalid Test size. Must be between 0.0 and 1.0"<<'\n';
            return;
        }

        train_data.clear();
        test_data.clear();
        
        feature_dataset = dataframe[0];
        feature_dataset.pop_back();  // Remove "target" column name
        dataframe.erase(dataframe.begin());


        //to perform splitting what we ll do is
        //make a vector of random indices, using those we will go to
        //to those random indices in df and populate the train and test data accordingly

        vector<size_t> indices(size(dataframe));
        iota(indices.begin(),indices.end(),0);
        random_device random_gen;
        mt19937 g(101); //101 is the random state 
        shuffle(indices.begin(),indices.end(),g);

        //size_t is an unsigned int used to hold counts/sizes etc.

        size_t test_target_size = static_cast<size_t>(test_size * dataframe.size());
        int i = 0;
        while (test_data.size() < test_target_size && i < indices.size()) {
            
            test_data.push_back(dataframe[indices[i]]);
            i++;
        }

        while (i < indices.size()) {
            train_data.push_back(dataframe[indices[i]]);
            i++;
        }
    }
}

// ---------TESTING------------------
        /*cout<<"features: -"<<endl;
        for(auto i: feature_dataset)
        {
            cout<<i<<" ";
        }
        cout<<endl;
        cout<<"training:- ";
        
         for(int i=0;i<size(train_data);i++)
        {
            vector <string> temp=train_data[i];
            for(auto j: temp)
            {
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"test:- ";

         for(int i=0;i<size(test_data);i++)
        {
            vector <string> temp=test_data[i];
            for(auto j: temp)
            {
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        

    }*/

//---------------------------------------------






