#ifndef CPPEXAMPLES_COPYELISION_INCLUDE_COPYELISION_H
#define CPPEXAMPLES_COPYELISION_INCLUDE_COPYELISION_H
namespace CopyElision
{
    struct Example
    {
        Example() = default;
        Example(const Example &) = delete;
    };
    Example create() { return Example{}; } // avoids copy even if copy ctor is deleted

}
#endif // EXTERNAL_COPYELISION_INCLUDE_COPYELISION_H