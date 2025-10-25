#include <bits/stdc++.h>
#include "data_handler.h"
#include "decision_tree.h"
#include "inference.h"
using namespace std;

// 6: ABSTRACT BASE CLASS WITH PURE VIRTUAL FUNCTION
class Run {
protected:
    int allowed = 1;

public:
    virtual void running() = 0; 
};


class ToHelp : public Run //1: INHERITANCE: MULTILEVEL INHERITANCE IS USED ACROSS ALL FILES AND CLASSES
{
public:
    int option = 0;

    void running() override {
        if (allowed == 1) {
            cout << "\n==============================================\n";
            cout << "Welcome to the World of Trees. Tread Carefully!" << '\n';
            cout << "==============================================\n\n";
            cout << "Here is a list of all available functions you can call using their designated option numbers:\n";
            cout << "--------------------------------------------------------------\n";
            cout << "-> For uploading your CSV file:           Enter 1" << endl;
            cout << "-> For performing dataset split:          Enter 2" << endl;
            cout << "-> For training the model:                Enter 3" << endl;
            cout << "-> For making predictions:                Enter 4" << endl;
            cout << "-> For viewing predictions:               Enter 5" << endl;
            cout << "-> For viewing tree metrics:              Enter 6" << endl;
            cout << "-> To exit:                               Enter 42" << endl;
            cout << "--------------------------------------------------------------\n";
        }
    }
};

// Class to run the program menu options

class ToRun : public ToHelp {
private:
    tree_metrics dtree;
    //WE WONT INHERIT dtree because we need to protect its method hence initialize it as a private object


public:
    ToRun()
    {
        if (allowed == 1) 
        {
            cout << "\nYou have now entered the running state." << endl;
            cout << "Use the functions above to get your model working!\n";
        }

    }
    void running() override { //--------------2: POLYMORPHISM :OVERRIDE A METHOD OF BASE CLASS IN DERIVED, THE METHOD BEHAVES DIFFERENTLY DEPENDING ON WHICH TYPE OF OBJECT CALLS IT
                                //THIS IS DIFFERENT FROM FUNCTION OVERLOADING !!

       

            int start = 0;

            do {
                //3:ABSTRACTION: INTERFACE LED PROGRAMS HAVE 100% ABSTRACTION, USERS HAVE NO IMPLEMENTATION DETAILS GIVEN TO THEM

                cout << "\nEnter a valid option: ";
                cin >> start;

                switch (start) {
                    case 1:
                        
                        dtree.read_csv();
                        this_thread::sleep_for(chrono::milliseconds(500));
                        cout << "\nUploaded!!\n";
                        break;
                        
                    case 2:
                        

                        cout << "\nPerforming train-test split...\n";
                        dtree.train_test_split();
                        cout<<'\n'<<"Done!"<<'\n';
                        break;

                    case 3:
                        
                        cout << "\nTraining model...\n";
                        dtree.train();
                        break;

                    case 4:
                        cout << "\nMaking predictions!!\n";
                        dtree.predict();
                        break;
                    case 5:
                        cout<<"\nPredictions:- \n";
                        dtree.prediction_display();
                        break;

                    case 6:
                        cout << "\nDisplaying tree metrics:- \n"<<endl;
                        metric_calc(dtree);
                        break;

                    case 42:
                        break;

                    default:
                        cout << "\nOops! Invalid option. Please try again!\n";
                        break;
                }

            } while (start != 42);

           
        }

        ~ ToRun() //9: DESTRUCTOR TO PROTECT MEMORY
        {
            cout<<"\nFreeing Up Resources!!\n";
            this_thread::sleep_for(chrono::milliseconds(1500));
            
            cout<<"\nPurging the Decision TREE : | ";
            this_thread::sleep_for(chrono::milliseconds(180));
            cout<<" | ";
            this_thread::sleep_for(chrono::milliseconds(180));
            cout<<" | ";
            this_thread::sleep_for(chrono::milliseconds(180));
            cout<<" | ";
            this_thread::sleep_for(chrono::milliseconds(180));
            cout<<" | ";
            this_thread::sleep_for(chrono::milliseconds(180));
            cout<<" | ";
            this_thread::sleep_for(chrono::milliseconds(180));
            cout<<" | ";
            cout<<"\n";

            
            cout << "\nProgram Terminated. Goodbye!\n";
        }
};

int main() {
    ToHelp helper;
    helper.running();

    this_thread::sleep_for(chrono::seconds(1));
    ToRun runner;
    runner.running();
}