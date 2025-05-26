#ifndef EXTERNAL_LIB_MODULEEXAMPLE_INCLUDE_MODULECHILD_B_H
#define EXTERNAL_LIB_MODULEEXAMPLE_INCLUDE_MODULECHILD_B_H
#include <iostream>
#include "../interface/iModule.h"

namespace ModuleOopTest
{
    class ChildB : public IModuleBase
    {
    public:
        ChildB() = default;
        ~ChildB() = default;
        void print() const override;
        void setValue(const int iValue) override;
        int getValue() const override;

    private:
        int m_iValue = 2;
    };

}
#endif // EXTERNAL_LIB_MODULEEXAMPLE_INCLUDE_MODULECHILD_B_H