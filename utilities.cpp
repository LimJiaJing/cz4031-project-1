#include <iostream>

using namespace std;

int main(){
    char sel1;
    int blockSize;
    int dsSize; //disk storage size, in MB
    cout << "Allocating disk storage of size " << dsSize << "MB...\n";
    //code to allocate memory
    cout << "Allocation complete. Disk storage of size " << dsSize << "MB is now allocated.\n";
    cout << "Please select block size. (Enter 1 or 2)\n";
    cout << "1. 200 B\n"
         << "2. 500 B\n";

    while (true){
        cout << "Selection: ";
        cin >> sel1;
        if ((sel1 == '1') || (sel1 == '2'))
        {
            cout << "You have selected option " << sel1 << ".\n";
            break;
        }
        else{
            cout << "Your selection (" << sel1 << ") is invalid. Please selection a valid option. (Enter 1 or 2)\n";
        }
    }
    if (sel1 == '1')
    {
        blockSize = 200;
    }
    else if (sel1 == '2')
    {
        blockSize = 500;
    }
    else {
        cout << "!!!!!!!!This part of the code should never run.\n";
    }

    cout << "Initializing block size to " << blockSize << "B...\n";
    //code to initialize block size to 200B
    cout << "Initialization complete. Block size has been set to " << blockSize << "B.\n";

    char sel2 = 'n';
    while (sel2 != '6')
    {
        cout << "Please select one of the options below. (0, 1, 2, 3, 4, 5, or 6)\n";
        cout << "0. Change block size (200B or 500B)\n"
             << "1. Run experiment 1\n"
             << "2. Run experiment 2\n"
             << "3. Run experiment 3\n"
             << "4. Run experiment 4\n"
             << "5. Run experiment 5\n"
             << "6. Terminate program\n";
    
        bool validSelection = true;
        do{
            validSelection = true;
            cout << "Selection: ";
            cin >> sel2;
            cout << "You have selected option " << sel2 << ".\n";
            switch (sel2)
            {
            case '0':
                char sel3;
                cout << "Change block size\n";
                cout << "Please select block size to change to. (Enter 1 or 2)\n";
                cout << "1. 200 B\n"
                     << "2. 500 B\n";

                while (true)
                {
                    cout << "Selection: ";
                    cin >> sel3;
                    if ((sel3 == '1') || (sel3 == '2'))
                    {
                        cout << "You have selected option " << sel3 << ".\n";
                        break;
                    }
                    else
                    {
                        cout << "Your selection (" << sel3 << ") is invalid. Please selection a valid option. (Enter 1 or 2)\n";
                    }
                }
                if (sel3 == '1')
                {
                    blockSize = 200;
                }
                else if (sel3 == '2')
                {
                    blockSize = 500;
                }
                else
                {
                    cout << "!!!!!!!!This part of the code should never run";
                }

                cout << "Changing database block size to " << blockSize << "B...\n";
                // code to initialize database block size to 200B
                cout << "Change complete. Block size has been set to " << blockSize << "B.\n";
                break;
            case '1':
                cout << "Run experiment 1\n";
                // code to run experiment 1
                break;
            case '2':
                // code to run experiment 2
                cout << "Run experiment 2\n";
                break;
            case '3':
                // code to run experiment 3
                cout << "Run experiment 3\n";
                break;
            case '4':
                // code to run experiment 4
                cout << "Run experiment 4\n";
                break;
            case '5':
                // code to run experiment 5
                cout << "Run experiment 5\n";
                break;
            case '6':
                cout << "Terminating program....\n";
                // clean up code if any
                cout << "Bye!";
                break;
            default:
                validSelection = false;
                cout << "Your selection is invalid, please select a valid option. (0, 1, 2, 3, 4, 5, or, 6)\n";
            }
            
        } while (!validSelection);
    }
}

