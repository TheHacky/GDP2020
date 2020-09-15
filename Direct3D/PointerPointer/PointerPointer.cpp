// PointerPointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void Normal(int* pI);
void Pointer(int* pI);
void PointerPointer(int** ppI);

int main()
{
    int v = 0;
    Normal(&v);

    int* pV = nullptr;
    Pointer(pV);
    PointerPointer(&pV);

    return 0;
}

void Normal(int* pI)
{
    *pI = 20;
}

void Pointer(int* pI)
{
    pI = new int();
    *pI = 10;
}

void PointerPointer(int** ppI)
{
    *ppI = new int();
    **ppI = 10;
}
