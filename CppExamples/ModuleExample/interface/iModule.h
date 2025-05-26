#ifndef CPPEXAMPLES_MODULEEXAMPLE_INTERFACE_IMODULE_H
#define CPPEXAMPLES_MODULEEXAMPLE_INTERFACE_IMODULE_H
namespace ModuleOopTest
{
    class IModuleBase
    {
    public:
        virtual ~IModuleBase() = default;
        virtual void print() const = 0;
        virtual void setValue(const int) = 0;
        virtual int getValue() const = 0;
    };
}
#endif // CPPEXAMPLES_MODULEEXAMPLE_INTERFACE_IMODULE_H