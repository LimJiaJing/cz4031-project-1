#include <iostream>
#include <cmath>
#include <iostream>
#include "Storage.h"
#include "Storage.cpp"
#include "BlockInfo.h"
#include "BlockInfo.cpp"
#include "Calculations.cpp"
#include <cstdlib>
#include <fstream> //ifstream
#include <sstream>  // stringstream
#include <iostream> // cout, endl
#include <iomanip>  // ws
#include <map>      // map
#include <string>
#pragma pack(1)
using namespace std;

void store_records(Storage* data);

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
                {
                    cout << "Run experiment 1\n";
                    // code to run experiment 1
                    //test(data);
                    Calculations cals;
                    int storage_size = cals.GetMaxSizeOfRecordBlocks(blockSize);
                    int reservation = 1000000;
                    Storage data = Storage(storage_size + reservation, blockSize);
                    store_records(&data);
                    break;
                }
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
void store_records(Storage* data) {
//    for (int i = 0; i < 30; i++) {
//        Record test(i, (int16_t)(3+i), i*4);
//        data.insert_item(&test, RECORD_SIZE);
//    }
//    Record test(1, (int16_t)55, 5);
//    data.insert_item(&test, RECORD_SIZE);
//    data.delete_item((char*) data.storage_ptr, RECORD_SIZE);
//    data.insert_item(&test, RECORD_SIZE);
//    Record rr = data.retrieve_record((char*)data.storage_ptr +10);
//    cout <<"Retrieved record: "<< rr.getName() << " " << rr.getAvgRating() << " " << rr.getNumOfVotes() << endl;
    ifstream testfile("data.tsv");
    string testline;
    // this commeneted out block is to find out number of records im working on a dynamic one but this one works fine like so it works but not best implementation
    int numofrecords= -1;
    while (getline(testfile, testline))
    {
        numofrecords+=1;
    }
    // cout<< numofrecords;
    //actual number of record is 1070318
    int skip_header = 0;
    int record_number = 0;
    // cout<< "ok";
    ifstream infile("data.tsv");
    string line;
    cout<<data->blk_size<<endl;
    while (getline(infile, line))
    {
        if(skip_header ==0)
        {
            skip_header = 1;
            continue;
        }
        string string_component;
        stringstream record_string(line);
        cout << "This is the Record line from dataset "<<line;
        cout << "\n";
        int name;
        int16_t average_rating_int;
        int numofvotes;
        for (int i = 0; i < 3; i++) {
         getline(record_string, string_component, '\t');
         if(i==0)
         {
            string_component.erase(0,2);
            name = stoi(string_component);
         }
         else if (i==1)
         {
            float average_rating_float = stof(string_component);
            average_rating_int = static_cast<int16_t>(average_rating_float*10);
         }
         else
         {
            numofvotes = stoi(string_component);
         }
        }
        //storing in the pointer array
        Record temp(name,(int16_t)average_rating_int,numofvotes);
        //displaying the stored value
        //cout <<  temp.getTconst() << "\t"<<  temp.rating2Dec() << "\t"<<  temp.getNumOfVotes();

        data->insert_item(&temp, RECORD_SIZE);
        cout << "\n";
        //move on to next record by incrementing array pointer
        record_number++;
    }
    infile.close();


    cout << "Total storage space: " << data->get_storage_size() << " Byte" << endl;
    cout << "Block size: " << data->get_blk_size() << " Bytes" << endl;
    cout << "Record size: " << RECORD_SIZE << " Btyes" <<endl;
    cout << "Allocated number of blocks: " << data->get_allocated_nof_blk() << endl;
    cout << "Allocated size: " << data->allocated_size<<endl;

    return;
}

