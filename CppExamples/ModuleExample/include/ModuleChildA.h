#ifndef CPPEXAMPLES_MODULEEXAMPLE_INCLUDE_MODULECHILD_A_H
#define CPPEXAMPLES_MODULEEXAMPLE_INCLUDE_MODULECHILD_A_H

#include "../interface/iModule.h"

namespace ModuleOopTest
{
    class ChildA : public IModuleBase
    {
    public:
        ChildA() = default;
        ~ChildA() = default;
        void print() const override;
        void setValue(const int iValue) override;
        int getValue() const override;

    private:
        void privatePrint() const;

        int m_iValue = 0;
    };

}
#endif // CPPEXAMPLES_MODULEEXAMPLE_INCLUDE_MODULECHILD_A_H