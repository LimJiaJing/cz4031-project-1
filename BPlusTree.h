#ifndef BPLUSTREE_H_INCLUDED
#define BPLUSTREE_H_INCLUDED
#include "Record.h"

typedef int KEY_TYPE;

enum NODE_TYPE
{
NODE_TYPE_ROOT     = 1,
NODE_TYPE_INTERNAL = 2,
NODE_TYPE_LEAF     = 3,
};


#define INVALID 0
#define NULLNODE 0
#define FLAG_LEFT 1
#define FLAG_RIGHT 2


class CNode
{
public:
    int ORDER_V;
    int MAX_KEYS;
    CNode();
    virtual ~CNode();

    NODE_TYPE GetType() { return m_Type; }
    void SetType(NODE_TYPE type) {m_Type = type;}

    int GetCount() { return m_Count;}
    void SetCount(int i) { m_Count = i; }

    virtual KEY_TYPE GetElement(int i) {return 0;}
    virtual void SetElement(int i, KEY_TYPE value) { }

    virtual CNode* GetPointer(int i) {return nullptr;}
    virtual void SetPointer(int i, CNode* pointer) { }

    CNode* GetFather() { return m_pFather;}
    void SetFather(CNode* father) { m_pFather = father; }

    CNode* GetBrother(int& flag);

    void DeleteChildren();

protected:

    NODE_TYPE m_Type;

    int m_Count;

    CNode* m_pFather;

};

class CInternalNode : public CNode
{
public:

    CInternalNode(int MAXNUM_KEY, int MAXNUM_POINTER);
    virtual ~CInternalNode();

    KEY_TYPE GetElement(int i)
    {
        if ((i > 0 ) && (i <= MAX_KEYS))
        {
            return m_Keys[i - 1];
        }
        else
        {
            return INVALID;
        }
    }

    void SetElement(int i, KEY_TYPE key)
    {
        if ((i > 0 ) && (i <= MAX_KEYS))
        {
            m_Keys[i - 1] = key;
        }
    }

    CNode* GetPointer(int i)
    {
        if ((i > 0 ) && (i <= (MAX_KEYS+1)))
        {
            return m_Pointers[i - 1];
        }
        else
        {
            return nullptr;
        }
    }

    void SetPointer(int i, CNode* pointer)
    {
        if ((i > 0 ) && (i <= (MAX_KEYS+1)))
        {
            m_Pointers[i - 1] = pointer;
        }
    }

    bool Insert(KEY_TYPE value, CNode* pNode);
    bool Delete(KEY_TYPE value);

    KEY_TYPE Split(CInternalNode* pNode, KEY_TYPE key, int* flag);
    bool Combine(CNode* pNode);
    bool MoveOneElement(CNode* pNode);

protected:

    KEY_TYPE* m_Keys;
    CNode** m_Pointers;

};

class Parray{
public:
   vector<Record*> Rpointer;
   Parray* next;

   Parray(){
   this->Rpointer = {};
   this->next = nullptr;
   }
   bool insertarray(Record* pointer);
   vector<Record*> getarray();
   void cleararray();
};

class CLeafNode : public CNode
{
public:

    CLeafNode(int MAXNUM_DATA, int MAXNUM_POINTER);
    virtual ~CLeafNode();

    KEY_TYPE GetElement(int i)
    {
        if ((i > 0 ) && (i <= MAX_KEYS))
        {
            return m_Datas[i - 1];
        }
        else
        {
            return INVALID;
        }
    }

    void SetElement(int i, KEY_TYPE data)
    {
        if ((i > 0 ) && (i <= MAX_KEYS))
        {
            m_Datas[i - 1] = data;
        }
    }


      Parray* GetPointer1(int i)
    {
        if ((i > 0 ) && (i <= MAX_KEYS))
        {
            return m_Pointers[i - 1];
        }
        else
        {
            return nullptr;
        }
    }

    void SetPointer1(int i, Parray* pointer)
    {
        if ((i > 0 ) && (i <= MAX_KEYS))
        {
            m_Pointers[i - 1] = pointer;
        }
    }
    bool Insert(KEY_TYPE value,Parray* Apointer);
    bool Delete(KEY_TYPE value);
    bool Insertdata(KEY_TYPE value, Record* rdata);

    KEY_TYPE Split(CLeafNode* pNode);
    bool Combine(CLeafNode* pNode);
    bool insertsamekey(KEY_TYPE value, Record* rdata);

public:
    CLeafNode *m_pPrevNode;
    CLeafNode* m_pNextNode;

protected:

    KEY_TYPE* m_Datas;
    Parray** m_Pointers;
};

class BPlusTree
{
public:
    int ORDER_V;
    int MAX_KEYS;
    BPlusTree(int order);
    virtual ~BPlusTree();
    BPlusTree *addr_of_object(void) { return this; }
    bool Search(KEY_TYPE data, char* sPath);
    bool Insert(KEY_TYPE data, Record* rdata);
    bool Delete(KEY_TYPE data);
    void ClearTree();
    void PrintTree();
    BPlusTree* RotateTree();
    bool CheckTree();
    void PrintNode(CNode* pNode);
    bool CheckNode(CNode* pNode);
    CNode* GetRoot()
    {
        return m_Root;
    }

    void SetRoot(CNode* root)
    {
        m_Root = root;

    }

    int GetDepth()
    {
        return m_Depth;
    }

    void SetDepth(int depth)
    {
        m_Depth = depth;
    }

    void IncDepth()
    {
        m_Depth = m_Depth + 1;
    }

    void DecDepth()
    {
        if (m_Depth > 0)
        {
            m_Depth = m_Depth - 1;
        }
    }
    int NumofNode(CNode *root);
    vector<CNode *> AncestoryOfLeafNode(CLeafNode *node);

public:
    CLeafNode *m_pLeafHead;
    CLeafNode* m_pLeafTail;
    CLeafNode *SearchLeafNode(KEY_TYPE data);

    bool InsertInternalNode(CInternalNode* pNode, KEY_TYPE key, CNode* pRightSon);
    bool DeleteInternalNode(CInternalNode* pNode, KEY_TYPE key);

    CNode* m_Root;
    int m_Depth;
};



#endif // BPLUSTREE_H_INCLUDED
