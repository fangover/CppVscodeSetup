#ifndef EXTERNAL_LIB_COPYELISION_INCLUDE_H
#define EXTERNAL_LIB_COPYELISION_INCLUDE_H
namespace CopyElision
{
    struct Example
    {
        Example() = default;
        Example(const Example &) = delete;
    };
    Example create() { return Example{}; } // avoids copy even if copy ctor is deleted

}
#endif // EXTERNAL_LIB_COPYELISION_INCLUDE_H