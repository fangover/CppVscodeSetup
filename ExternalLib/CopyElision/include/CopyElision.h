#ifndef MAINAPP_INCLUDE_COPYELISION_H
#define MAINAPP_INCLUDE_COPYELISION_H
namespace CopyElision
{
    struct Example
    {
        Example() = default;
        Example(const Example &) = delete;
    };
    Example create() { return Example{}; } // avoids copy even if copy ctor is deleted

}
#endif // MAINAPP_INCLUDE_COPYELISION_H