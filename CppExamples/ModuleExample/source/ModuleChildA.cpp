#include "../include/ModuleChildA.h"
#include <iostream>

using namespace ModuleOopTest;

void ChildA::print() const
{
    std::cout << typeid(this).name() << " Value: " << m_iValue << std::endl;
}

void ChildA::setValue(const int iValue)
{
    m_iValue = iValue;
};

int ChildA::getValue() const
{
    return m_iValue;
};

void ChildA::privatePrint() const
{
    std::cout << typeid(this).name() << "private Value: " << m_iValue << std::endl;
}
