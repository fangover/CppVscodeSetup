#ifndef MAINAPP_INCLUDE_MODULECHILD_B_H
#define MAINAPP_INCLUDE_MODULECHILD_B_H
#include <iostream>
#include "../interface/iModule.h"

namespace ModuleOopTest
{
    class ChildB : public IModuleBase
    {
    public:
        ChildB() = default;
        ~ChildB() = default;
        void print() const override { std::cout << typeid(this).name() << " Value: " << m_iValue << std::endl; };
        void setValue(const int iValue) override { m_iValue = iValue; };
        int getValue() const override { return m_iValue; };

    private:
        int m_iValue = 2;
    };

}
#endif // MAINAPP_INCLUDE_MODULECHILD_B_H