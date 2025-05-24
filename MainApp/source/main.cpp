#include "../include/BasicStdLib.h"

#include "ExternalLib/ModuleExample/interface/iModule.h"
#include "ExternalLib/ModuleExample/include/ModuleChildA.h"
#include "ExternalLib/ModuleExample/include/ModuleChildB.h"
#include "ExternalLib/CopyElision/include/CopyElision.h"
#include "ExternalLib/FileStream/include/FileStreamUseCase.h"

template <typename T>
void testModuleSet()
{
    auto module = std::make_unique<T>();
    module->print();
    module->setValue(module->getValue() + (typeid(T) == typeid(ModuleOopTest::ChildA) ? 1 : 10));
    module->print();
}
#define COMPILE_TIME_MAX 10

int main()
{

    // Use an unnamed (anonymous) namespace for all internal/non-exported entities

    //------------------------------------------------------------------------------
    // std::Optional examples
    //------------------------------------------------------------------------------
    // auto fnOptionalExample1 = [](const bool b) -> std::optional<std::string> : shorter version.
    std::function<std::optional<std::string>(bool)> fnOptionalExample1 = [](const bool b) -> std::optional<std::string>
    {
        if (b)
            return "Optional Example 1";
        return {};
    };

    auto fnOptionalExample2 = [](const bool b)
    {
        return b ? std::optional<std::string>{"Optional Example 2"} : std::nullopt;
    };

    std::cout << "fnOptionalExample1(false) returned " << fnOptionalExample1(false).value_or("empty") << '\n'
              << "fnOptionalExample1(true) returned " << fnOptionalExample1(true).value_or("empty") << '\n';
    if (auto str = fnOptionalExample2(true))
    {
        std::cout << "fnOptionalExample2(true) returned " << *str << '\n'
                  << std::endl;
    }

    //------------------------------------------------------------------------------
    // FileStream examples
    //  - Using RAII framework
    //  - And operator << or variadic template examples.
    //------------------------------------------------------------------------------
    FileStream::FileHandle oFileStreamUseCase("out/FileStreamExample.txt");
    oFileStreamUseCase << "Hello world!" << FileStream::Tab << "Test Operator <<" << FileStream::Endl;
    oFileStreamUseCase.appendFile(
        "Hello world!", FileStream::Tab, "Test variadic template appendFile", FileStream::Endl);
    oFileStreamUseCase.readFile();
    oFileStreamUseCase.clearFile();
    oFileStreamUseCase.readFile();

    //------------------------------------------------------------------------------
    // Compile Time Static assert
    //  - good to use for integral division, sizeof variables,
    //    with fixed defined values
    //------------------------------------------------------------------------------
    static_assert(sizeof(int) >= 4);
    static_assert(COMPILE_TIME_MAX == 10); // COMPILE_TIME_MAX == 10

    //------------------------------------------------------------------------------
    // Copy Elision.
    //------------------------------------------------------------------------------
    CopyElision::Example obj = CopyElision::create();
    (void)obj;

    //------------------------------------------------------------------------------
    // OOP Inheritance Examples
    //------------------------------------------------------------------------------
    std::cout << "\nStart OOP inheritance examples" << std::endl;
    std::unique_ptr<ModuleOopTest::IModuleBase> pModule;

    testModuleSet<ModuleOopTest::ChildA>();
    testModuleSet<ModuleOopTest::ChildB>();

    //------------------------------------------------------------------------------
    // Lamda functions examples
    //------------------------------------------------------------------------------
    std::cout << "\nStart lamda functions examples" << std::endl;
    int a = 1;
    int b = 2;

    auto fnTestLamdaInt = [](const int a) -> int
    {
        return a + 1;
    };

    auto fnTestLamdaReferanceInt = [&](const int a) -> int
    {
        return a + b;
    };

    std::cout << "fnTestLamdaInt: " << fnTestLamdaInt(a) << "\n"
              << "fnTestLamdaReferanceInt: " << fnTestLamdaReferanceInt(a) << "\n"
              << std::endl;

    return 0;
}