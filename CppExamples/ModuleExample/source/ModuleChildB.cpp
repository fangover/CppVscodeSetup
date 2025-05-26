#include "../include/ModuleChildB.h"
#include <iostream>

using namespace ModuleOopTest;

void ChildB::print() const
{
    std::cout << typeid(this).name() << " Value: " << m_iValue << std::endl;
}

void ChildB::setValue(const int iValue)
{
    m_iValue = iValue;
};

int ChildB::getValue() const
{
    return m_iValue;
};