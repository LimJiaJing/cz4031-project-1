#include <cmath>
#include <iostream>
#include "constants.h"

using namespace std;

class Calculations 
{
    public:
        // Record
        int GetMaxNumOfRecordsPerBlock(int blockSize);
        int GetMaxNumOfRecordBlocks(int blockSize);
        int GetMaxSizeOfRecordBlocks(int blockSize);

        // Index
        int GetMaxNumOfKeysPerIndexBlock(int blockSize);
        int GetMinNumOfKeysPerInternalNode(int blockSize);
        int GetMinNumOfKeysPerLeafNode(int blockSize);
        int GetMaxHeightOfBPlusTree(int blockSize);
        int GetMaxNumOfIndexBlocks(int blockSize);
        int GetMaxSizeOfIndexBlocks(int blockSize);

        int GetTotalBlockSize(int blockSize);
};

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
    int numOfKeys = 1;
    while ((numOfKeys * INDEX_KEY_SIZE) + ((numOfKeys + 1) * INDEX_POINTER_SIZE) <= blockSize)
    {
        numOfKeys++;
    }

    return numOfKeys - 1;
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

int main()
{
    Calculations calculations;
    int totalSize1 = calculations.GetTotalBlockSize(BLOCK_SIZE_1);
    int totalSize2 = calculations.GetTotalBlockSize(BLOCK_SIZE_2);
    cout << totalSize1 << endl;
    cout << totalSize2 << endl;
    return 0;
}