#ifndef CPPEXAMPLES_MODULEEXAMPLE_INCLUDE_MODULECHILD_B_H
#define CPPEXAMPLES_MODULEEXAMPLE_INCLUDE_MODULECHILD_B_H

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
#endif // CPPEXAMPLES_MODULEEXAMPLE_INCLUDE_MODULECHILD_B_H