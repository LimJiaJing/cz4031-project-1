#include <cmath>
#include <iostream>
#include "Storage.h"
#include "Storage.cpp"
#include "BlockInfo.h"
#include "BlockInfo.cpp"
#include <cstdlib>
#include <fstream> //ifstream
#include <sstream>  // stringstream
#include <iostream> // cout, endl
#include <iomanip>  // ws
#include <map>      // map
#include <string>
#pragma pack(1)
void test(Storage data);

int main() {
    Storage data = Storage(20000000, 200);
    //test(data);

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
    cout<<data.blk_size<<endl;
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
        cout <<  temp.getName() << "\t"<<  temp.getAvgRating() << "\t"<<  temp.getNumOfVotes();
        //insert to block
        data.insert_item(&temp, RECORD_SIZE);
        cout << "\n";
        //move on to next record by incrementing array pointer
        record_number++;
    }
    infile.close();


    cout << "Total storage space: " << data.get_storage_size() << " Byte" << endl;
    cout << "Block size: " << data.get_blk_size() << " Bytes" << endl;
    cout << "Record size: " << RECORD_SIZE << " Btyes" <<endl;
    cout << "Allocated number of blocks: " << data.get_allocated_nof_blk() << endl;
    cout << "Allocated size: " << data.allocated_size<<endl;

    return 0;
}

void test(Storage data) {

    for (int i = 0; i < 30; i++) {
        Record test(i, (int16_t)3+i, i*4);
        data.insert_item(&test, RECORD_SIZE);
    }
    Record test(1, (int16_t)55, 5);
    Record test1(2, (int16_t)8, 9);
    Record* r;
    data.insert_item(&test, RECORD_SIZE);
    data.update_item((char*)data.storage_ptr, RECORD_SIZE, &test1);
    memcpy(r,(char*)data.storage_ptr, RECORD_SIZE);
    cout << r->getName() << " " << r->getAvgRating() << " " << r->getNumOfVotes() << endl;
    data.delete_item((char*)data.storage_ptr, RECORD_SIZE);
    // Test delete by exact address
    data.delete_item((char*)data.storage_ptr, RECORD_SIZE);

    data.insert_item(&test1, RECORD_SIZE);

    // Test retrieval
    Record rr = data.retrieve_record((char*)data.storage_ptr + 10);

    cout << rr.getName() << " " << rr.getAvgRating() << " " << rr.getNumOfVotes() << endl;
}
