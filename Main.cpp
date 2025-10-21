#include <bits/stdc++.h>
using namespace std;

// Abstract base class
class Run {
protected:
    int allowed = 1;

public:
    virtual void running() = 0; // Pure virtual function
};


class ToHelp : public Run {
public:
    int option = 0;

    void running() override {
        if (allowed == 1) {
            cout << "\n==============================================\n";
            cout << "Welcome to the World of Trees. Tread Carefully!" << '\n';
            cout << "==============================================\n\n";

            cout << "Here’s a list of all available functions you can call using their designated option numbers:\n";
            cout << "--------------------------------------------------------------\n";
            cout << "-> For uploading your CSV file:           Enter 1" << endl;
            cout << "-> For reading your CSV file:             Enter 2" << endl;
            cout << "-> For performing dataset split:          Enter 3" << endl;
            cout << "-> For training the model:                Enter 4" << endl;
            cout << "-> For making predictions:                Enter 5" << endl;
            cout << "-> For viewing predictions:               Enter 6" << endl;
            cout << "-> For viewing tree metrics:              Enter 7" << endl;
            cout << "-> To exit:                               Enter 42" << endl;
            cout << "--------------------------------------------------------------\n";
        }
    }
};

// Class to run the program menu options
class ToRun : public ToHelp {
public:
    void running() override {
        if (allowed == 1) {
            cout << "\nYou have now entered the running state." << endl;
            cout << "Use the functions above to get your model working!\n";

            int start = 0;

            do {
                cout << "\nEnter a valid option: ";
                cin >> start;

                switch (start) {
                    case 1:
                        // push_csv();
                        this_thread::sleep_for(chrono::milliseconds(500));
                        cout << "\n[Placeholder] Uploaded!!\n";
                        break;

                    case 2:
                        cout << "\n[Placeholder] Reading CSV file...\n";
                         this_thread::sleep_for(chrono::milliseconds(500));
                        // read_csv();
                       
                        break;

                    case 3:
                        // train_test_split();
                        cout << "\n[Placeholder] Performing train-test split...\n";
                        break;

                    case 4:
                        
                        cout << "\n[Placeholder] Training model...\n";
                        //train();
                        this_thread::sleep_for(chrono::seconds(2));
                        break;

                    case 5:
                        cout << "\n[Placeholder] Making predictions!!\n";
                        // predict();
                        break;
                    case 6:
                        cout<<"\nPredictions:- \n";
                        //prediction_output();
                        break;

                    case 7:
                        cout << "\n[Placeholder] Displaying tree metrics\n";
                        // tree_metrics();
                        break;

                    case 42:
                        cout << "\nExiting...\n";
                        break;

                    default:
                        cout << "\nOops! Invalid option. Please try again!\n";
                        break;
                }

            } while (start != 42);

            this_thread::sleep_for(chrono::seconds(2));
            cout << "\nProgram Terminated. Goodbye!\n";
        }
    }
};

int main() {
    ToHelp helper;
    helper.running();

    this_thread::sleep_for(chrono::seconds(1));
    ToRun runner;
    runner.running();

   
}
