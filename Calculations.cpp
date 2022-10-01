#include <cmath>
#include <iostream>
#include "Calculations.h"
#include "constants.h"

using namespace std;

int Calculations::GetMaxNumOfRecordsPerBlock(int blockSize)
{
    int numOfRecords = 1;
    // 8 is the number of bits in 1 byte
    while (ceil(numOfRecords / 8) + (numOfRecords * RECORD_SIZE) <= blockSize)
    {
        numOfRecords++;
    }

    return numOfRecords - 1;
}

int Calculations::GetMaxNumOfRecordBlocks(int blockSize)
{
    int numOfRecords = GetMaxNumOfRecordsPerBlock(blockSize);
    int numOfBlocks = ceil(TOTAL_NUM_OF_RECORDS / numOfRecords);

    return numOfBlocks;
}

int Calculations::GetMaxNumOfKeysPerIndexBlock(int blockSize)
{
    int numOfKeysForInternalNode = 1;
    while (INDEX_HEADER_SIZE + (numOfKeysForInternalNode * INDEX_KEY_SIZE) + ((numOfKeysForInternalNode + 1) * INDEX_POINTER_SIZE) <= blockSize)
    {
        numOfKeysForInternalNode++;
    }

    int numOfKeysForLeafNode = 1;
    while (INDEX_HEADER_SIZE + (numOfKeysForLeafNode * INDEX_KEY_SIZE) + ((numOfKeysForLeafNode + 2) * INDEX_POINTER_SIZE) <= blockSize)
    {
        numOfKeysForLeafNode++;
    }

    if (numOfKeysForInternalNode == numOfKeysForLeafNode)
    {
        return numOfKeysForInternalNode - 1;
    } else {
        cout << "Number of keys should be the same!" << endl;
        return 0;
    }
}

int Calculations::GetMinNumOfKeysPerInternalNode(int blockSize)
{
    int maxNumOfKeys = GetMaxNumOfKeysPerIndexBlock(blockSize);
    int minNumOfKeys = floor(maxNumOfKeys / 2);

    return minNumOfKeys;
}

int Calculations::GetMinNumOfKeysPerLeafNode(int blockSize)
{
    int maxNumOfKeys = GetMaxNumOfKeysPerIndexBlock(blockSize);
    int minNumOfKeys = floor((maxNumOfKeys + 1) / 2);

    return minNumOfKeys;
}

int Calculations::GetMaxHeightOfBPlusTree(int blockSize)
{
    int minNumOfKeysPerInternalNode = GetMinNumOfKeysPerInternalNode(blockSize);
    int minNumOfKeysPerLeafNode = GetMinNumOfKeysPerLeafNode(blockSize);
    int height = 1;
    while ((2 * pow(minNumOfKeysPerInternalNode + 1, height - 2) * minNumOfKeysPerLeafNode) <= TOTAL_NUM_OF_RECORDS)
    {
        height++;
    }

    return height - 1;
}

int Calculations::GetMaxNumOfIndexBlocks(int blockSize)
{
    int maxHeight = GetMaxHeightOfBPlusTree(blockSize);
    int minNumOfKeysPerInternalNode = GetMinNumOfKeysPerInternalNode(blockSize); 
    int numOfBlocks = 1;
    for (int i = 2; i <= maxHeight; i++)
    {
        numOfBlocks += 2 * pow(minNumOfKeysPerInternalNode + 1, i - 2);
    }

    return numOfBlocks;
}

int Calculations::GetMaxSizeOfRecordBlocks(int blockSize)
{
    int numOfBlocks = GetMaxNumOfRecordBlocks(blockSize);
    int sizeOfBlocks = numOfBlocks * blockSize;

    return sizeOfBlocks;
}

int Calculations::GetMaxSizeOfIndexBlocks(int blockSize)
{
    int numOfBlocks = GetMaxNumOfIndexBlocks(blockSize);
    int sizeOfBlocks = numOfBlocks * blockSize;

    return sizeOfBlocks;
}

int Calculations::GetTotalBlockSize(int blockSize)
{
    int sizeOfRecordBlocks = GetMaxSizeOfRecordBlocks(blockSize);
    int sizeOfIndexBlocks = GetMaxSizeOfIndexBlocks(blockSize);
    int totalSize = sizeOfRecordBlocks + sizeOfIndexBlocks;

    return totalSize;
}

int Calculations::GetMaxNumOfPointersInLinkedListBlock(int blockSize)
{
    return floor((blockSize - LINKED_LIST_POINTER_SIZE) / LINKED_LIST_POINTER_SIZE);
}   