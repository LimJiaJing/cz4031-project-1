#include <iostream>
#include <cmath>
#include <iostream>
#include "Storage.h"
#include "Storage.cpp"
#include "Calculations.cpp"
#include <cstdlib>
#include <fstream> //ifstream
#include <sstream>  // stringstream
#include <iostream> // cout, endl
#include <iomanip>  // ws
#include <map>      // map
#include <string>
#include "BPlusTree.h"
#include "BPlusTree.cpp"
#pragma pack(1)

using std::cout;

void store_records(Storage* storage);
void RunExperiment1(Storage *storage);
BPlusTree* RunExperiment2(Storage *storage);
void RunExperiment3(Storage* storage, BPlusTree *bPlusTree);
void RunExperiment4(Storage* storage, BPlusTree *bPlusTree);
void RunExperiment5(Storage *storage, BPlusTree *bPlusTree, int key);
void build_BPlus_tree(Storage *storage, BPlusTree *bPlusTree);
void report_bPlusTree_statistics(BPlusTree *bPlusTree, int block_size, bool parameter_n, bool num_nodes, bool height, bool content);
void delete_records(Storage *storage, BPlusTree *bPlusTree, int key);
void delete_key_in_index(BPlusTree *bPlusTree, int key);
void delete_records_in_db(Storage *storage, vector<char *> record_addresses);
vector<char *> get_all_record_addr(CLeafNode *start_node, int start, int end = 0);
void retrieve_search_statistics_storage(Storage *storage, vector<char *> search_results_addresses);
void retrieve_search_statistics_index(BPlusTree *bPlusTree, CLeafNode *start_node, int start, int end = 0);
vector<CLeafNode *> get_nodes_accessed_at_leaf_level(CLeafNode *start_node, int start, int end);


//global variables
Calculations cals;
int blockSize;
int storage_size;
Storage *storage;
BPlusTree *bPlusTree;

int main()
{
    char sel1;

    cout << "Please select block size. (Enter 1 or 2)\n";
    cout << "1. 200 B\n"
         << "2. 500 B\n"<< endl;

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
        cout << "This part of the code should never run!!\n";
    }

    cout << "Initializing block size to " << blockSize << "B...\n";
    //code to initialize block size to 200B

    storage_size = cals.GetMaxSizeOfRecordBlocks(blockSize);
    int reservation = 1000000;
    storage = Storage(storage_size + reservation, blockSize).addr_of_object();
    cout << "Initialization complete. Block size has been set to " << blockSize << "B.\n";
    cout << "Allocation complete. Disk storage of size " << ((storage_size + reservation) / (double)1000000) << "MB is now allocated.\n";
    cout << "Allocated storage is now empty, please run experiment 1 to load data.\n"<<endl;
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
            cout << "You have selected option " << sel2 << ".\n"<<endl;
            switch (sel2)
            {
            case '0':
            {
                char sel3;
                cout << "Change block size\n";
                cout << "Please select block size to change to. (Enter 1 or 2)\n";
                cout << "1. 200 B\n"
                     << "2. 500 B\n"<<endl;

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
                    blockSize = BLOCK_SIZE_1;
                }
                else if (sel3 == '2')
                {
                    blockSize = BLOCK_SIZE_2;
                }
                else
                {
                    cout << "This part of the code should never run!!";
                }

                cout << "Deallocating storage...\n";
                storage->clear_storage();
                // code to initialize database block size to 200B
                int storage_size = cals.GetMaxSizeOfRecordBlocks(blockSize);
                int reservation = 1000000;
                cout << "Changing database block size to " << blockSize << "B...\n";
                storage = Storage(storage_size + reservation, blockSize).addr_of_object();
                cout << "Change complete. Block size has been set to " << blockSize << "B.\n";
                cout << "Allocation complete. Disk storage of size " << ((storage_size+reservation)/(double)1000000) << "MB is now allocated.\n";

                break;
            }
            case '1':
                {
                    cout << "Running experiment 1...\n";
                    RunExperiment1(storage);
                    cout << "Completed experiment 1...\n"<<endl;
                    break;
                }
            case '2':
            {
                cout << "Running experiment 2...\n";
                bPlusTree = RunExperiment2(storage);
                cout << "Completed experiment 2...\n"<<endl;
                break;
            }
            case '3':
            {
                cout << "Running experiment 3...\n";
                RunExperiment3(storage, bPlusTree);
                cout << "Completed experiment 3...\n"<<endl;
                break;
            }
            case '4':
            {
                cout << "Running experiment 4...\n";
                RunExperiment4(storage, bPlusTree);
                cout << "Completed experiment 4...\n"<<endl;
                break;
            }
            case '5':
             {
                cout << "Running experiment 5...\n";
                // code to run experiment 5
                RunExperiment5(storage, bPlusTree, 1000);
                cout << "Completed experiment 5...\n"<<endl;
                break;
             }
            case '6':
            {
                cout << "Terminating program....\n";
                // clean up code if any
                cout << "Bye!"<<endl;
                break;
            }
            default:
            {
                validSelection = false;
                cout << "Your selection is invalid, please select a valid option. (0, 1, 2, 3, 4, 5, or, 6)\n"<<endl;
            }
            }
        } while (!validSelection);
    }
}

void RunExperiment1(Storage *storage)
{
    cout << "Loading data...\n";
    store_records(storage);
    cout << "Loading data complete.\n";
}

BPlusTree* RunExperiment2(Storage *storage)
{
    BPlusTree* bPlusTree = new BPlusTree(cals.GetMaxNumOfKeysPerIndexBlock(storage->get_blk_size()));
    build_BPlus_tree(storage, bPlusTree);
    report_bPlusTree_statistics(bPlusTree, storage->get_blk_size(), true, true, true, true);
    return bPlusTree;
}

// need to incorporate the Linked list and B+tree portion into the wrapper function if it is to be inside it.
void RunExperiment3(Storage* storage, BPlusTree *bPlusTree)
{
    int key_to_find = 500;
    CLeafNode *start_node = bPlusTree->SearchLeafNode(key_to_find);
    vector<char *> record_addresses = get_all_record_addr(start_node, key_to_find);

    retrieve_search_statistics_storage(storage, record_addresses);
    retrieve_search_statistics_index(bPlusTree, start_node, key_to_find);
}

void RunExperiment4(Storage* storage, BPlusTree* bPlusTree)
{
    int start_of_range = 30000;
    int end_of_range = 40000;
    CLeafNode *start_node = bPlusTree->SearchLeafNode(start_of_range);
    vector<char *> record_addresses = get_all_record_addr(start_node, start_of_range, end_of_range);
    retrieve_search_statistics_storage(storage, record_addresses);
    // code for number and content of index nodes the process accesses
    retrieve_search_statistics_index(bPlusTree, start_node, start_of_range, end_of_range);
}

void RunExperiment5(Storage *storage, BPlusTree *bPlusTree, int key)
{
    delete_records(storage, bPlusTree, key);
    report_bPlusTree_statistics(bPlusTree, storage->get_blk_size(), false, true, true, true);
    cout << "Number of times that a node is deleted = " << num_nodes_deleted << "\n"
    << "Note: it does not include the number of Parrays deleted (level between leaf nodes and records)"<<endl;
}

// experiment 1 helper code
void store_records(Storage *storage)
{
    int skip_header = 0;
    int record_number = 0;
    ifstream infile("data.tsv");
    string line;
    while (getline(infile, line))
    {
        if (skip_header == 0)
        {
            skip_header = 1;
            continue;
        }
        string string_component;
        stringstream record_string(line);
        int name;
        int16_t average_rating_int;
        int numofvotes;
        for (int i = 0; i < 3; i++)
        {
            getline(record_string, string_component, '\t');
            if (i == 0)
            {
                string_component.erase(0, 2);
                name = stoi(string_component);
            }
            else if (i == 1)
            {
                float average_rating_float = stof(string_component);
                average_rating_int = static_cast<int16_t>(average_rating_float * 10);
            }
            else
            {
                numofvotes = stoi(string_component);
            }
        }
        Record temp(name, (int16_t)average_rating_int, numofvotes);

        storage->insert_item(&temp, RECORD_SIZE);
        record_number++;
    }
    infile.close();

    cout << "Total storage space: " << (double)storage->get_storage_size() / 1000000.0 << " MB" << endl;
    cout << "Block size: " << storage->get_blk_size() << " Bytes" << endl;
    cout << "Record size: " << RECORD_SIZE << " Bytes" << endl;
    cout << "Allocated number of blocks: " << storage->get_allocated_nof_blk()<< endl;
    cout << "Allocated size: " << (double)storage->get_allocated_size() / 1000000.0 << " MB"  << endl;

    return;
}

// experiment 2 helper code
void build_BPlus_tree(Storage *storage, BPlusTree *bPlusTree)
{
    int offset = storage->get_blk_size();
    char *curr_block_ptr = (char *)storage->get_storage_ptr();
    int num_allocated_blocks = storage->get_allocated_nof_blk();
    for (int i = 0; i < num_allocated_blocks; i++)
    {
        vector<Record> curr_block_records = storage->retrieve_blk(curr_block_ptr);
        for (int j = 0; j < curr_block_records.size(); j++)
        {
            Record curr_record = curr_block_records.at(j);
            int numVotes = curr_record.getNumOfVotes();
            // cout << "first call to insert\n";
            char *original_record_pointer = curr_block_ptr + j * (sizeof(Record));
            bPlusTree->Insert(numVotes, (Record*)original_record_pointer);
        }
        curr_block_ptr += offset;
    }
}

void report_bPlusTree_statistics(BPlusTree *bPlusTree, int block_size, bool parameter_n, bool num_nodes, bool height, bool content)
{
    Calculations cals = Calculations();
    if (parameter_n)
    {
        cout << "Parameter n of B+ tree: " << cals.GetMaxNumOfKeysPerIndexBlock(block_size) << endl; // could change depending on BPlusTree/CNode attributes
    }
    if (num_nodes)
    {
        CNode* rootnode = bPlusTree->GetRoot();
        cout << "Number of nodes of the B+ tree: " << bPlusTree->NumofNode(rootnode) + 1 << "\n";
    }
    if (height)
    {
        int h = 0;
        CNode* curr_node = bPlusTree->GetRoot();
        while (curr_node->GetType() != NODE_TYPE_LEAF)
        {
            h++; // number of internal nodes in path
            curr_node = curr_node->GetPointer(1);
        }
        h++;
        cout << "Height of B+ tree = " << h << "\n";
    }
    if (content)
    {
        // code to print content of root node and its first child node
        CNode *root = bPlusTree->GetRoot();
        CNode *child = nullptr;
        if (root->GetType()!=NODE_TYPE_LEAF){
            child = root->GetPointer(1);
        }
        cout << "Root node keys: ";
        for (int i = 1; i <= root->GetCount();i++){
            cout << root->GetElement(i) << " | ";
        }
        cout << "\n";
        if (child == nullptr){
            cout << "Root node is a leaf node and therefore has no child;\n";
        }
        else{
            cout << "First child node keys: ";
            for (int i = 1; i <= child->GetCount(); i++){
                cout << child->GetElement(i) << " | ";
            }
            cout << "\n";
        }
    }
}

// experiment 3 and 4 helper code
vector<char *> get_all_record_addr(CLeafNode *start_node, int start, int end)
{

    if (start_node == nullptr){
        cout << "This shouldnt happen";
    }
    vector<char*> record_addr = {};
    vector<Parray*> parrays = {};

    if (end == 0){
        end = start;
    }

    int curr_key = start;
    CLeafNode *curr_node = start_node;
    bool flag_for_while = true;
    do{
        int i = 1;
        for (i = 1; (i <= curr_node->GetCount()); i++)
        {
            int curr_key_in_node = curr_node->GetElement(i);
            if (curr_key_in_node >= start && curr_key_in_node <= end){
                parrays.push_back(curr_node->GetPointer1(i));
            }
            if (curr_key_in_node > end)
            {
                flag_for_while = false;
                break;
            }
        }
        // cout << "size of parrays " << parrays.size() << "\n";
        curr_node = curr_node->m_pNextNode;
        if (curr_node == nullptr){
            break;
        }
    } while (flag_for_while);
    //copy to recordaddr
    for (int i = 0; i < parrays.size(); i++){

        Parray* curr_parray = parrays.at(i);

        vector<Record *> array = curr_parray->getarray();
        for (int j = 0; j < array.size(); j++){
            record_addr.push_back((char*)array.at(j));
        }
    }
    // cout << "number of record address:" << record_addr.size() << "\n";
    return record_addr;
}
void retrieve_search_statistics_storage(Storage *storage, vector<char *> search_results_addresses)
{
    int block_count = 0;
    int record_count = 0;
    float average_rating = 0;
    char* prev_block_address = nullptr;
    int index = 0;
    while(index<search_results_addresses.size())
    {
        char* current_block_address = storage->record_addr_to_blk_addr(search_results_addresses[index]);
        if (current_block_address == prev_block_address)
        {
            //retrieve the avg rating of the individual record
                Record temp_record = storage->retrieve_record(search_results_addresses[index]);
                average_rating += temp_record.rating2Dec();
                record_count += 1;
        }
        else{
            if(block_count<5)
            {
                cout << "This is block number " << block_count + 1 <<" and the block ID is " <<  storage->get_blk_id(current_block_address) <<endl;
                cout << endl;
                cout <<"Tconst of records in the block are"<<endl;
                cout <<endl;
                vector<Record> contents_of_block = storage->retrieve_blk(current_block_address);
                for (int i = 0; i< contents_of_block.size() ; i++)
                 {
                     cout <<contents_of_block[i].getTconst()<< " | ";
                 }
                cout <<endl;
            }
            Record temp_record = storage->retrieve_record(search_results_addresses[index]);
            average_rating += temp_record.rating2Dec();
            // increment record count no matter what, but block count only if its not consecutively the same
            record_count += 1;
            block_count +=1;
        }
        //change the prev to current for next loop
        prev_block_address = current_block_address;
         index++;
    }
    cout<< "Number of unique blocks accessed is " << block_count<< endl;
    //the contents of first 5 printed out beforehand in the if portion
    cout<< "Number of records found is " << record_count <<endl;
    //cout<< "This is the total sum" << average_rating <<endl;
    cout << "Average rating of all the records accessed is " << average_rating/record_count <<endl;

    return;
}
void retrieve_search_statistics_index(BPlusTree* bPlusTree, CLeafNode* start_node, int start, int end){
    if (end == 0)
    {
        end = start;
    }
    vector<CNode *> nodes_accessed_to_find_start = bPlusTree->AncestoryOfLeafNode(start);
    vector<CLeafNode*> leaf_nodes_accessed_after_finding_start = get_nodes_accessed_at_leaf_level(start_node, start, end);

    int total_index_blocks_accessed = nodes_accessed_to_find_start.size() + leaf_nodes_accessed_after_finding_start.size();
    cout << "total_index_blocks_accessed = " << total_index_blocks_accessed << "\n";
    int printcount = 0;
    int max_printcount = 5;
    CNode *curr_node = nullptr;
    for (int j = 0; j < nodes_accessed_to_find_start.size();j++){
        curr_node = nodes_accessed_to_find_start.at(j);
        if (curr_node == nullptr){
            cout<<"SOMETHING IS WRONG\n";
            return;
        }
        cout << "Keys index block " << printcount+1 << " accessed: ";
        for (int i = 1; i <= curr_node->GetCount();i++){
            cout << curr_node->GetElement(i)<<" | ";
        }
        cout << "\n";
        printcount++;
        if (printcount==5){
            break;
        }
    }
    for (int j = 0; j < leaf_nodes_accessed_after_finding_start.size(); j++)
    {
        if (printcount == 5){
            break;
        }
        curr_node = leaf_nodes_accessed_after_finding_start.at(j);
        if (curr_node == nullptr)
        {
            cout << "SOMETHING IS WRONG\n";
            return;
        }
        cout << "Keys index block " << printcount + 1 << " accessed: ";
        for (int i = 1; i <= curr_node->GetCount(); i++)
        {
            cout << curr_node->GetElement(i) << " | ";
        }
        cout << "\n";
        printcount++;
    }
}
vector<CLeafNode*> get_nodes_accessed_at_leaf_level(CLeafNode* start_node, int start, int end){
    vector<CLeafNode *> nodes_accessed = {}; // excepted start_node
    if (start == end) {
        return nodes_accessed;
    }
    int curr_key = start;
    CLeafNode *curr_node = start_node;
    bool flag_for_while = true;
    do
    {
        int i = 1;
        for (i = 1; (i <= curr_node->GetCount()); i++)
        {
            int curr_key_in_node = curr_node->GetElement(i);
            if (curr_key_in_node >= start && curr_key_in_node <= end)
            {
                // parrays.push_back(curr_node->GetPointer1(i));
            }
            if (curr_key_in_node > end)
            {
                flag_for_while = false;
                break;
            }
        }
        curr_node = curr_node->m_pNextNode;
        if (curr_node == nullptr)
        {
            break;
        }
        nodes_accessed.push_back(curr_node);

    } while (flag_for_while);
    return nodes_accessed;
}

// helper code for experiment 5
void delete_records_in_db(Storage *storage, vector<char *> record_addresses)
{

    for (int i = 0; i < record_addresses.size(); i++)
    {
        storage->delete_item(record_addresses.at(i), sizeof(record_addresses.at(i)));
    }
}

void delete_key_in_index(BPlusTree *bPlusTree, int key)
{
    bool res = bPlusTree->Delete(key);
    if (res)
    {
        cout << "Deleted key " << key << " in B+ tree\n";
    }
    else
    {
        cout << "Failed to delete key " << key << " in B+ tree\n";
    }
}

void delete_records(Storage *storage, BPlusTree *bPlusTree, int key)
{
    CLeafNode *start_node = bPlusTree->SearchLeafNode(key);
    vector<char *> record_addresses = get_all_record_addr(start_node, key);
    cout << "Found all records with numVotes = " << key << "\n";
    delete_records_in_db(storage, record_addresses); // this one can return a tuple detailing the number of times a node is deleted
    cout << "Deleted all records with numVotes = " << key << "\n";
    delete_key_in_index(bPlusTree, key);
    cout << "Finished deleting records from storage and updating B+ tree\n";
}
