#include "table8mod.hpp"

void print(Table *T)
{
    std::cout << std::setw(8) << std::left << "Id"
              << std::setw(16) << std::left << "Data"
              << std::setw(16) << std::left << "Key" << std::endl
              << std::setw(8) << std::left << "-------"
              << std::setw(16) << std::left << "---------------"
              << std::setw(16) << std::left << "---------------" << std::endl;
    for (unsigned i = 0; i < T->SizeBuf; i++)
    {
        if (T->Buf[i].flag == Busy)
        {
            auto t_Key = ((Element *)T->Buf[i].E)->Key;
            std::cout << std::setw(8) << std::left << i
                      << std::setw(16) << std::left
                      << (int)((Element *)T->Buf[i].E)->Data
                      << std::setw(16) << std::left << t_Key << std::endl;
        }
    }
}

void print(ElTable *ElT)
{
    if (ElT->flag != Busy)
        return;
    auto t_Key = ((Element *)ElT->E)->Key;
    std::cout << std::setw(16) << std::left << "Key"
              << std::setw(16) << std::left << "Data" << std::endl
              << std::setw(16) << std::left << "---------------"
              << std::setw(16) << std::left << "---------------" << std::endl
              << std::setw(16) << std::left
              << (int)((Element *)ElT->E)->Data
              << std::setw(16) << std::left << t_Key << std::endl;
}

void print(Element *E)
{
    auto t_Key = E->Key;
    std::cout << std::setw(16) << std::left << "Key"
              << std::setw(16) << std::left << "Data" << std::endl
              << std::setw(16) << std::left << "---------------"
              << std::setw(16) << std::left << "---------------" << std::endl
              << std::setw(16) << std::left << (int)E->Data
              << std::setw(16) << std::left << t_Key << std::endl;
}

int PutTable(Table *T, int E_Data, T_Key E_Key, cmpFunc cmp)
{
    return PutTable(T, &E_Data, E_Key, cmp);
}