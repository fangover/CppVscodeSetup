#ifndef MAINAPP_INCLUDE_MODULECHILD_A_H
#define MAINAPP_INCLUDE_MODULECHILD_A_H
#include <iostream>
#include "../interface/iModule.h"

namespace ModuleOopTest
{
    class ChildA : public IModuleBase
    {
    public:
        ChildA() = default;
        ~ChildA() = default;
        void print() const override { std::cout << typeid(this).name() << " Value: " << m_iValue << std::endl; };
        void setValue(const int iValue) override { m_iValue = iValue; };
        int getValue() const override { return m_iValue; };

    private:
        void privatePrint() { std::cout << typeid(this).name() << "private Value: " << m_iValue << std::endl; }
        int m_iValue = 0;
    };

}
#endif // MAINAPP_INCLUDE_MODULECHILD_A_H