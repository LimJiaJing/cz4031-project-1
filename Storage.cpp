#include <iostream>
#include "Storage.h"
#include "BlockInfo.h"
#include "constants.h"
#include "Record.h"
#pragma pack(1)


using namespace std;

/* The total size of allocated storage is fixed.
    initialize 2 storages: data and index
*/

Storage::Storage(unsigned int storage_size, unsigned int blk_size){
    this->storage_size = storage_size;
    this->blk_size = blk_size;
    this->total_nof_blk = storage_size / blk_size;
    this->allocated_nof_blk = 0;
    this->allocated_size = 0;
    this->cur_blk_id = -1;

    this->deleted_slots = {};

    this->blks = (BlockInfo*)malloc(total_nof_blk * sizeof(BlockInfo));
    BlockInfo init = BlockInfo(blk_size);
    for (int i = 0; i <total_nof_blk; i++) {
        blks[i] = init;
    }
    this->storage_ptr = operator new(storage_size);
}

/*
First check whether there is enough space to allocate a new block.
*/
bool Storage::allocate_block() {
    if (storage_size >= (allocated_nof_blk + 1) * blk_size) {
        allocated_nof_blk++;
        cur_blk_id++;
        return true;
    } else {
        return false;
    }
}

void Storage::release_blk() {
    allocated_nof_blk--;
}

pair<int, char*> Storage::get_available_ptr(int store_size) {
    if (deleted_slots.size() != 0) {
        if (deleted_slots.front().second >= store_size) {
            char* target_addr = deleted_slots.front().first;
            deleted_slots.erase(deleted_slots.begin());
            return make_pair(get_blk_id(target_addr), target_addr);
        }
    }
    bool is_allocated = true;
    if (allocated_nof_blk == 0 || blk_size - blks[cur_blk_id].space_used < store_size) {
        is_allocated = allocate_block();
    }
    if (is_allocated) {
        unsigned int target_ptr = blks[cur_blk_id].get_avail_ptr();
        return make_pair(cur_blk_id, (char*)storage_ptr + (cur_blk_id) * blk_size + target_ptr);
    } else {
        return make_pair(-1, nullptr);
    }
}

unsigned int Storage::get_blk_id(char* addr) {
    return (addr - (char*)storage_ptr) / blk_size;
}
/*
Insert a record to the storage memory.
*/
void Storage::insert_item(void* item_addr, int item_size) {
    if (item_size > blk_size) {
        cout<<"Insertion fails since the record size is larger than the block size!"<<endl;
    }
    pair<int, char*> target_pos = get_available_ptr(item_size);
    int blk_id = target_pos.first;
    char* target_addr = target_pos.second;
    if (target_addr != nullptr){
        memcpy(target_addr, (char*) item_addr, item_size);
        blks[blk_id].store(item_size);
        allocated_size += item_size;

        cout << "Successfully insert the item at block " << blk_id << endl;
        cout << "Block "<< blk_id << " now has " << blks[blk_id].get_space_used() << " bytes used."<<endl;
    } else {
        cout << "The storage is full. No more space for new items." << endl;
    }
    return;
}

void Storage::delete_item(char* addr, int size_to_delete) {
    int target_blk_id = get_blk_id(addr);
    if (target_blk_id == cur_blk_id) {
        cur_blk_id--;
    }
    blks[target_blk_id].delete_size(size_to_delete);
    if (blks[target_blk_id].get_space_used() == 0) {
        release_blk();
    }
    allocated_size -= size_to_delete;
    deleted_slots.push_back(make_pair(addr, size_to_delete));
    cout << "Record at block " << target_blk_id << " has been successfully deleted." <<endl;
    cout << "Block "<< target_blk_id << " now has " << blks[target_blk_id].get_space_used() << " bytes used."<<endl;
}

void Storage::update_item(char* addr, int size_to_update, void* new_item) {
    memcpy(addr, (char*)new_item, size_to_update);
}


Record Storage::retrieve_record(char* addr) {
    int i, k;
    int16_t j;
    memcpy(&i, addr, 4);
    memcpy(&j, addr + 4, 2);
    memcpy(&k, addr + 6, 4);
    Record result;
    result.Record::SetRecord(i, j, k);
    return result;
}


int Storage::get_storage_size() {
    return storage_size;
}

int Storage::get_blk_size() {
    return blk_size;
}

int Storage::get_allocated_nof_blk() {
    return allocated_nof_blk;
}

int Storage::get_allocated_size() {
    return allocated_size;
}
