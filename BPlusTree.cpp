
#include "BPlusTree.h"
#include "stdio.h"
#include "stdlib.h"
#include "Record.h"


using std::cout;
int num_nodes_deleted = 0;

CNode::CNode()
{
    m_Type = NODE_TYPE_LEAF;
    m_Count = 0;
    m_pFather = nullptr;

}
CNode::~CNode()
{
    DeleteChildren();
}

CNode* CNode::GetBrother(int& flag)
{
    CNode* pFather = GetFather();
    if (nullptr == pFather)
    {
        return nullptr;
    }

    CNode* pBrother = nullptr;

    for (int i = 1; i <= pFather->GetCount() + 1; i++)
    {
        if (pFather->GetPointer(i) == this)
        {
            if (i == (pFather->GetCount() + 1))
            {
                pBrother = pFather->GetPointer(i - 1);
                flag = FLAG_LEFT;
            }
            else
            {
                pBrother = pFather->GetPointer(i + 1);
                flag = FLAG_RIGHT;
            }
        }
    }

    return pBrother;
}

void CNode::DeleteChildren()
{
    for (int i = 1; i <= GetCount(); i++)
    {
        if(this->m_Type==NODE_TYPE_LEAF)
        {
            return;
        }
        CNode * pNode = GetPointer(i);
        if (nullptr != pNode)
        {
            pNode->DeleteChildren();
        }
        delete pNode;
    }
}

CInternalNode::CInternalNode(int MAXNUM_KEY, int MAXNUM_POINTER)
{
    MAX_KEYS = MAXNUM_KEY;
    ORDER_V = MAX_KEYS / 2;

    m_Keys = (KEY_TYPE*)malloc(MAX_KEYS * sizeof(KEY_TYPE));
    m_Pointers = (CNode**)malloc(MAXNUM_POINTER * sizeof(CNode*));
    m_Type = NODE_TYPE_INTERNAL;

    int i = 0;
    for (i = 0; i < MAX_KEYS; i++)
    {
        m_Keys[i] = INVALID;
    }

    for (i = 0; i < MAXNUM_POINTER; i++)
    {
        m_Pointers[i] = nullptr;
    }
}
CInternalNode::~CInternalNode()
{
    for (int i = 0; i < (MAX_KEYS+1); i++)
    {
        m_Pointers[i] = nullptr;
    }
}


bool CInternalNode::Insert(KEY_TYPE value, CNode* pNode)
{
    int i;
    if (GetCount() >= MAX_KEYS)
    {
        return false;
    }

    int j = 0;

    for (i = 0; (value > m_Keys[i]) && ( i < m_Count); i++)
    {
    }

    for (j = m_Count; j > i; j--)
    {
        m_Keys[j] = m_Keys[j - 1];
    }

    for (j = m_Count + 1; j > i + 1; j--)
    {
        m_Pointers[j] = m_Pointers[j - 1];
    }

    m_Keys[i] = value;
    m_Pointers[i + 1] = pNode;
    pNode->SetFather(this);

    m_Count++;

    // 返回成功
    return true;
}


bool CInternalNode::Delete(KEY_TYPE key)
{
    int i,j,k;
    for (i = 0; (key >= m_Keys[i]) && (i < m_Count); i++)
    {
    }

    for (j = i - 1; j < m_Count - 1; j++)
    {
        m_Keys[j] = m_Keys[j + 1];
    }
    m_Keys[j] = INVALID;

    for (k = i; k < m_Count; k++)
    {
        m_Pointers[k] = m_Pointers[k + 1];
    }
    m_Pointers[k] = nullptr;

    m_Count--;

    return true;
}

KEY_TYPE CInternalNode::Split(CInternalNode* pNode, KEY_TYPE key, int* flag)
{
    int i = 0, j = 0;

    if ((key > this->GetElement(ORDER_V)) && (key < this->GetElement(ORDER_V + 1)))
    {
        *flag = 0;
        for (i = ORDER_V + 1; i <= MAX_KEYS; i++)
        {
            j++;
            pNode->SetElement(j, this->GetElement(i));
            this->SetElement(i, INVALID);
        }

        j = 1;
        for (i = ORDER_V + 2; i <= (MAX_KEYS+1); i++)
        {
            j++;
            this->GetPointer(i)->SetFather(pNode);
            pNode->SetPointer(j, this->GetPointer(i));
            this->SetPointer(i, nullptr);
        }

        this->SetCount(ORDER_V);
        pNode->SetCount(ORDER_V);

        return key;
    }

    int position = 0;
    if (key < this->GetElement(ORDER_V))
    {
        position = ORDER_V;
        *flag = 1 ;
    }
    else
    {
        position = ORDER_V + 1;
        *flag = 2;
    }

    KEY_TYPE RetKey = this->GetElement(position);

    j = 0;
    for (i = position + 1; i <= MAX_KEYS; i++)
    {
        j++;
        pNode->SetElement(j, this->GetElement(i));
        this->SetElement(i, INVALID);
    }

    j = 0;
    for (i = position + 1; i <= (MAX_KEYS+1); i++)
    {
        j++;
        this->GetPointer(i)->SetFather(pNode);
        pNode->SetPointer(j, this->GetPointer(i));
        this->SetPointer(i, nullptr);
    }

    this->SetElement(position, INVALID);

    this->SetCount(position - 1);
    pNode->SetCount(MAX_KEYS - position);


    return RetKey;
}

bool CInternalNode::Combine(CNode* pNode)
{
    if (this->GetCount() + pNode->GetCount() + 1> MAX_KEYS)
    {
        return false;
    }

    KEY_TYPE NewKey = pNode->GetPointer(1)->GetElement(1);

    m_Keys[m_Count] = NewKey;
    m_Count++;
    m_Pointers[m_Count] = pNode->GetPointer(1);

    for (int i = 1; i <= pNode->GetCount(); i++)
    {
        m_Keys[m_Count] = pNode->GetElement(i);
        m_Count++;
        m_Pointers[m_Count] = pNode->GetPointer(i+1);
    }
    num_nodes_deleted++;
    return true;
}

bool CInternalNode::MoveOneElement(CNode* pNode)
{
    if (this->GetCount() >= MAX_KEYS)
    {
        return false;
    }

    int i,j;

    if (pNode->GetElement(1) < this->GetElement(1))
    {
        for (i = m_Count; i > 0; i--)
        {
            m_Keys[i] = m_Keys[i -1];
        }
        for (j = m_Count + 1; j > 0; j--)
        {
            m_Pointers[j] = m_Pointers[j -1];
        }

        m_Keys[0] = GetPointer(1)->GetElement(1);
        m_Pointers[0] = pNode->GetPointer(pNode->GetCount() + 1);

        pNode->SetElement(pNode->GetCount(), INVALID);
        pNode->SetPointer(pNode->GetCount() + 1, nullptr);
    }
    else
    {
        m_Keys[m_Count] = pNode->GetPointer(1)->GetElement(1);
        m_Pointers[m_Count + 1] = pNode->GetPointer(1);

        for (i = 1; i < pNode->GetCount() - 1; i++)
        {
            pNode->SetElement(i, pNode->GetElement(i + 1));
        }
        for (j = 1; j < pNode->GetCount(); j++)
        {
            pNode->SetPointer(j, pNode->GetPointer(j + 1));
        }
    }

    this->SetCount(this->GetCount() + 1);
    pNode->SetCount(pNode->GetCount() - 1);

    return true;
}

CLeafNode::CLeafNode(int MAXNUM_DATA, int MAXNUM_POINTER)
{
    MAX_KEYS = MAXNUM_DATA;
    ORDER_V = MAX_KEYS / 2;
    m_Type = NODE_TYPE_LEAF;
    m_Datas = (KEY_TYPE*)malloc(MAX_KEYS * sizeof(KEY_TYPE));
    m_Pointers = (Parray**)malloc((MAXNUM_POINTER-1) * sizeof(Parray*));
    for (int i = 0; i < MAX_KEYS; i++)
    {
        m_Datas[i] = 0;
        m_Pointers[i] = nullptr;
        delete m_Pointers[i];

    }

    m_pPrevNode = nullptr;
    m_pNextNode = nullptr;
}
CLeafNode::~CLeafNode()
{
  for (int i = 0; i < MAX_KEYS; i++)
    {
        m_Pointers[i]->cleararray();
        delete m_Pointers[i];
        m_Pointers[i] = nullptr;
    }
}

bool CLeafNode::Insertdata(KEY_TYPE value, Record* rdata)
{
    int i,j;
    for (i = 0; (value > m_Datas[i]) && ( i < m_Count); i++){}
     if(value == m_Datas[i]){
        m_Pointers[i]->insertarray(rdata);
          return true;
     }

     if (GetCount() >= MAX_KEYS)
     {
         return false;
     }

    for (j = m_Count; j > i; j--)
    {
        m_Datas[j] = m_Datas[j - 1];
       m_Pointers[j] = m_Pointers[j-1];
    }
    m_Datas[i] = value;
    Parray* temp = new Parray();
    temp->insertarray(rdata);
    m_Pointers[i] = temp;
    m_Count++;
    return true;
}

bool CLeafNode::Insert(KEY_TYPE value, Parray* Apointer) //
{
    int i,j;
    if (GetCount() >= MAX_KEYS)
    {
        return false;
    }
    for (i = 0; (value > m_Datas[i]) && ( i < m_Count); i++)
    {
    }

    for (j = m_Count; j > i; j--)
    {
        m_Datas[j] = m_Datas[j - 1];
       m_Pointers[j] = m_Pointers[j-1];
    }

    m_Datas[i] = value;
    m_Pointers[i] = Apointer;
    m_Count++;

    return true;
}
bool CLeafNode::Delete(KEY_TYPE value)
{
    int i,j;
    bool found = false;
    for (i = 0; i < m_Count; i++)
    {
        if (value == m_Datas[i])
        {
            found = true;
            break;
        }
    }
    if (false == found)
    {
        return false;
    }

    for (j = i; j < m_Count - 1; j++)
    {
       m_Datas[j] = m_Datas[j + 1];
       m_Pointers[j]->cleararray();
       delete m_Pointers[j];
       m_Pointers[j] = m_Pointers[j-1];
    }

    m_Datas[j] = INVALID;
    m_Pointers[j]->cleararray();
    delete m_Pointers[j];
    m_Count--;

    return true;

}

KEY_TYPE CLeafNode::Split(CLeafNode* pNode)
{
    int j = 0;
    for (int i = ORDER_V + 1; i <= MAX_KEYS; i++)
    {
        j++;
        pNode->SetElement(j, this->GetElement(i));
        pNode->SetPointer1(j, this->GetPointer1(i));
        this->SetElement(i, INVALID);
    }
    this->SetCount(this->GetCount() - j);
    pNode->SetCount(pNode->GetCount() + j);

    return pNode->GetElement(1);
}

bool CLeafNode::Combine(CLeafNode* pNode)
{
    if (this->GetCount() + pNode->GetCount() > MAX_KEYS)
    {
        return false;
    }

    for (int i = 1; i <= pNode->GetCount(); i++)
    {

        this->Insert(pNode->GetElement(i),pNode->GetPointer1(i));
    }

    num_nodes_deleted++;
    return true;
}
BPlusTree::BPlusTree(int Order)
{
    m_Depth = 0;
    m_Root = nullptr;
    m_pLeafHead = nullptr;
    m_pLeafTail = nullptr;
    MAX_KEYS = Order;
    ORDER_V = Order/2;
}
BPlusTree::~BPlusTree()
{
    ClearTree();
}

bool BPlusTree::Search(KEY_TYPE data, char* sPath)
{
    int i = 0;
    int offset = 0;
    if (nullptr != sPath)
    {
        (void)sprintf(sPath+offset, "The search path is:");
        offset+=19;
    }

    CNode * pNode = GetRoot();
    while (nullptr != pNode)
    {
        if (NODE_TYPE_LEAF == pNode->GetType())
        {
            break;
        }

        for (i = 1; (data >= pNode->GetElement(i) )&& (i <= pNode->GetCount()); i++)
        {
        }

        if (nullptr != sPath)
        {
            (void)sprintf(sPath+offset, " %3d -->", pNode->GetElement(1));
            offset+=8;
        }

        pNode = pNode->GetPointer(i);
    }

    if (nullptr == pNode)
    {
        return false;
    }

    if (nullptr != sPath)
    {
        (void)sprintf(sPath+offset, "%3d", pNode->GetElement(1));
        offset+=3;
    }

    bool found = false;
    for (i = 1; (i <= pNode->GetCount()); i++)
    {
        if (data == pNode->GetElement(i))
        {
            found = true;
        }
    }


    if (nullptr != sPath)
    {
        if (true == found)
        {

            (void)sprintf(sPath+offset, " ,successed.");
        }
        else
        {
            (void)sprintf(sPath+offset, " ,failed.");
        }
    }

    return found;
}

bool BPlusTree::Insert(KEY_TYPE data, Record* rdata)
{
    bool found = Search(data, nullptr);
    CLeafNode* pOldNode = SearchLeafNode(data);
    if (pOldNode == nullptr)
    {
        pOldNode = new CLeafNode(MAX_KEYS, MAX_KEYS+1);
        m_pLeafHead = pOldNode;
        m_pLeafTail = pOldNode;
        SetRoot(pOldNode);
    }
    if(found)
    {
        pOldNode->Insertdata(data, rdata);
        return true;
    }
    if (pOldNode->GetCount() < MAX_KEYS)
    {
         pOldNode->Insertdata(data,rdata);
         return true;
    }

    CLeafNode* pNewNode = new CLeafNode(MAX_KEYS, MAX_KEYS+1);
    KEY_TYPE key = INVALID;
    key = pOldNode->Split(pNewNode);

    CLeafNode* pOldNext = pOldNode->m_pNextNode;
    pOldNode->m_pNextNode = pNewNode;
    pNewNode->m_pNextNode = pOldNext;
    pNewNode->m_pPrevNode = pOldNode;
    if (nullptr == pOldNext)
    {
        m_pLeafTail = pNewNode;
    }
    else
    {
        pOldNext->m_pPrevNode = pNewNode;
    }

    if (data < key)
    {
        pOldNode->Insertdata(data, rdata);
    }
    else
    {
        pNewNode->Insertdata(data, rdata);
    }

    CInternalNode* pFather = (CInternalNode*)(pOldNode->GetFather());

    if (nullptr == pFather)
    {
        CNode* pNode1 = new CInternalNode(MAX_KEYS, MAX_KEYS+1);
        pNode1->SetPointer(1, pOldNode);
        pNode1->SetElement(1, key);
        pNode1->SetPointer(2, pNewNode);
        pOldNode->SetFather(pNode1);
        pNewNode->SetFather(pNode1);
        pNode1->SetCount(1);

        SetRoot(pNode1);
        return true;
    }

    bool ret = InsertInternalNode(pFather, key, pNewNode);
    return ret;
}


bool BPlusTree::Delete(KEY_TYPE data)
{
    num_nodes_deleted = 0;
    CLeafNode* pOldNode = SearchLeafNode(data);
    if (nullptr == pOldNode)
    {
        return false;
    }

    bool success = pOldNode->Delete(data);
    if (false == success)
    {
        return false;
    }

    CInternalNode* pFather = (CInternalNode*)(pOldNode->GetFather());
    if (nullptr == pFather)
    {
        if (0 == pOldNode->GetCount())
        {
            delete pOldNode;
            m_pLeafHead = nullptr;
            m_pLeafTail = nullptr;
            SetRoot(nullptr);
        }

        return true;
    }

    if (pOldNode->GetCount() >= ORDER_V)
    {
        for (int i = 1; (data >= pFather->GetElement(i)) && (i <= pFather->GetCount()); i++)
        {
            if (pFather->GetElement(i) == data)
            {
                pFather->SetElement(i, pOldNode->GetElement(1));
            }
        }

        return true;
    }

    int flag = FLAG_LEFT;
    CLeafNode* pBrother = (CLeafNode*)(pOldNode->GetBrother(flag));

    KEY_TYPE NewData = INVALID;
    Parray* NewPointer = nullptr;
    if (pBrother->GetCount() > ORDER_V)
    {
        if (FLAG_LEFT == flag)
        {
            NewData = pBrother->GetElement(pBrother->GetCount());
            NewPointer = pBrother->GetPointer1(pBrother->GetCount());
        }
        else
        {
            NewData = pBrother->GetElement(1);
            NewPointer = pBrother->GetPointer1(1);
        }

        pOldNode->Insert(NewData,NewPointer);
        pBrother->Delete(NewData);

        if (FLAG_LEFT == flag)
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pOldNode && i > 1)
                {
                    pFather->SetElement(i - 1 , pOldNode->GetElement(1));
                }
            }
        }
        else
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pOldNode && i > 1)
                {
                    pFather->SetElement(i - 1, pOldNode->GetElement(1));
                }
                if (pFather->GetPointer(i) == pBrother && i > 1)
                {
                    pFather->SetElement(i - 1 , pBrother->GetElement(1));
                }
            }
        }


        return true;
    }

    KEY_TYPE NewKey = NULLNODE;

    if (FLAG_LEFT == flag)
    {
        (void)pBrother->Combine(pOldNode);
        NewKey = pOldNode->GetElement(1);

        CLeafNode* pOldNext = pOldNode->m_pNextNode;
        pBrother->m_pNextNode = pOldNext;
        if (nullptr == pOldNext)
        {
            m_pLeafTail = pBrother;
        }
        else
        {
            pOldNext->m_pPrevNode = pBrother;
        }
        delete pOldNode;
    }
    else
    {
        (void)pOldNode->Combine(pBrother);
        NewKey = pBrother->GetElement(1);

        CLeafNode* pOldNext = pBrother->m_pNextNode;
        pOldNode->m_pNextNode = pOldNext;
        if (nullptr == pOldNext)
        {
           m_pLeafTail = pOldNode;
        }
        else
        {
            pOldNext->m_pPrevNode = pOldNode;
        }
        delete pBrother;
    }

    return DeleteInternalNode(pFather, NewKey);
}

void BPlusTree::ClearTree()
{
    CNode* pNode = GetRoot();
    if (nullptr != pNode)
    {
        pNode->DeleteChildren();

        delete pNode;
    }

    m_pLeafHead = nullptr;
    m_pLeafTail = nullptr;
    SetRoot(nullptr);
}

bool BPlusTree::CheckTree()
{
    CLeafNode * pThisNode = m_pLeafHead;
    CLeafNode * pNextNode = nullptr;
    while (nullptr != pThisNode)
    {
        pNextNode = pThisNode->m_pNextNode;
        if (nullptr != pNextNode)
        {
           if (pThisNode->GetElement(pThisNode->GetCount()) > pNextNode->GetElement(1))
           {
               return false;
           }
        }
        pThisNode = pNextNode;
    }

    return CheckNode(GetRoot());
}

bool BPlusTree::CheckNode(CNode* pNode)
{
    if (nullptr == pNode)
    {
        return true;
    }

    int i = 0;
    bool ret = false;

    if ((pNode->GetCount() < ORDER_V) && (pNode != GetRoot()))
    {
        return false;
    }

    for (i = 1; i < pNode->GetCount(); i++)
    {
        if (pNode->GetElement(i) > pNode->GetElement(i + 1))
        {
            return false;
        }
    }

    if (NODE_TYPE_LEAF == pNode->GetType())
    {
        return true;
    }

    for (i = 1; i <= pNode->GetCount() + 1; i++)
    {
        ret = CheckNode(pNode->GetPointer(i));
        if (false == ret)
        {
            return false;
        }
    }

    return true;

}


CLeafNode* BPlusTree::SearchLeafNode(KEY_TYPE data)
{
    int i = 0;

    CNode * pNode = GetRoot();
    while (nullptr != pNode)
    {
        if (NODE_TYPE_LEAF == pNode->GetType())
        {
            break;
        }

        for (i = 1; i <= pNode->GetCount(); i++)
        {
            if (data < pNode->GetElement(i))
            {
                break;
            }
        }

        pNode = pNode->GetPointer(i);
    }

    return (CLeafNode*)pNode;
}

bool BPlusTree::InsertInternalNode(CInternalNode* pNode, KEY_TYPE key, CNode* pRightSon)
{
    if (nullptr == pNode || NODE_TYPE_LEAF ==pNode->GetType())
    {
        return false;
    }

    if (pNode->GetCount() < MAX_KEYS)
    {
        return pNode->Insert(key, pRightSon);
    }

    CInternalNode* pBrother = new CInternalNode(MAX_KEYS, MAX_KEYS+1);
    KEY_TYPE NewKey = INVALID;
    int flag = -1;
    NewKey = pNode->Split(pBrother, key, &flag);

    if (flag == 1 )
    {
        pNode->Insert(key, pRightSon);
    }
    else if (flag == 2)
    {
         pBrother->Insert(key, pRightSon);
    }
    else
    {
        pBrother->SetPointer(1,pRightSon);
        pRightSon->SetFather(pBrother);
    }

    CInternalNode* pFather = (CInternalNode*)(pNode->GetFather());
    if (nullptr == pFather)
    {
        pFather = new CInternalNode(MAX_KEYS, MAX_KEYS+1);
        pFather->SetPointer(1, pNode);
        pFather->SetElement(1, NewKey);
        pFather->SetPointer(2, pBrother);
        pNode->SetFather(pFather);
        pBrother->SetFather(pFather);
        pFather->SetCount(1);

        SetRoot(pFather);
        return true;
    }

    return InsertInternalNode(pFather, NewKey, pBrother);
}

bool BPlusTree::DeleteInternalNode(CInternalNode* pNode, KEY_TYPE key)
{
    bool success = pNode->Delete(key);
    if (false == success)
    {
        return false;
    }

    CInternalNode* pFather = (CInternalNode*)(pNode->GetFather());
    if (nullptr == pFather)
    {
        if (0 == pNode->GetCount())
        {
            SetRoot(pNode->GetPointer(1));
            delete pNode;
        }

        return true;
    }

    if (pNode->GetCount() >= ORDER_V)
    {
        for (int i = 1; (key >= pFather->GetElement(i)) && (i <= pFather->GetCount()); i++)
        {
            if (pFather->GetElement(i) == key)
            {
                pFather->SetElement(i, pNode->GetElement(1));
            }
        }

        return true;
    }

    int flag = FLAG_LEFT;
    CInternalNode* pBrother = (CInternalNode*)(pNode->GetBrother(flag));

    KEY_TYPE NewData = INVALID;
    if (pBrother->GetCount() > ORDER_V)
    {
        pNode->MoveOneElement(pBrother);

        if (FLAG_LEFT == flag)
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pNode && i > 1)
                {
                    pFather->SetElement(i - 1 , pNode->GetElement(1));
                }
            }
        }
        else
        {
            for (int i = 1; i <= pFather->GetCount() + 1; i++)
            {
                if (pFather->GetPointer(i) == pNode && i > 1)
                {
                    pFather->SetElement(i - 1, pNode->GetElement(1));
                }
                if (pFather->GetPointer(i) == pBrother && i > 1)
                {
                    pFather->SetElement(i - 1 , pBrother->GetElement(1));
                }
            }
        }

        return true;
    }

    KEY_TYPE NewKey = NULLNODE;

    if (FLAG_LEFT == flag)
    {
        (void)pBrother->Combine(pNode);
        NewKey = pNode->GetElement(1);
        delete pNode;
    }
    else
    {
        (void)pNode->Combine(pBrother);
        NewKey = pBrother->GetElement(1);
        delete pBrother;
    }

    return DeleteInternalNode(pFather, NewKey);
}

int BPlusTree::NumofNode(CNode *root)
{
    int numofchildnode = 0;
    if (root == nullptr)
    {
        return 0;
    }
    if (root->GetType() == NODE_TYPE_LEAF)
    {
        return 0;
    }
    for (int i = 1; i <= root->GetCount() + 1; i++)
    {
        numofchildnode = numofchildnode + this->NumofNode(root->GetPointer(i));
    }
    numofchildnode = root->GetCount() + 1 + numofchildnode;
    return numofchildnode;
}

vector<CNode*> BPlusTree::AncestoryOfLeafNode(CLeafNode *node){
// only works if leaf node is not the root node

   vector<CNode *> chain = {};
    int i = 0;

    CNode * pNode = GetRoot();
    
    while (nullptr != pNode)
    {
     
        if (NODE_TYPE_LEAF == pNode->GetType())
        {
            break;
        }

        for (i = 1; i <= pNode->GetCount(); i++)
        {
            if (data < pNode->GetElement(i))
            {
                break;
            }
        }
        chain.push_back(pNode);
        pNode = pNode->GetPointer(i);
    }
    chain.push_back(pNode);
    return chain
}

bool Parray::insertarray(Record* Ppointer){
   if(Ppointer== nullptr)
    {
        return false;
        }
    Rpointer.push_back(Ppointer);

   return true;

}

vector<Record*> Parray::getarray(){
  return Rpointer;
}

void Parray::cleararray(){
    if (this==nullptr){
        return;
    }
    if (nullptr != (this->next))
    {
        this->next->cleararray();
        delete next;
  }
  if(next == nullptr)
  {return;}
  return ;
}
