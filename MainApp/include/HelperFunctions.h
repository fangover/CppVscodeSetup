#include <BasicStdLib.h>

template <typename T>
void testModuleSet()
{
    auto pModule = std::make_unique<T>();
    pModule->print();
    pModule->setValue(pModule->getValue() + (typeid(T) == typeid(ModuleOopTest::ChildA) ? 1 : 10));
    pModule->print();
}
#define COMPILE_TIME_MAX 10

void testFunction()
{
    LOG_ENTRY;
    LOG("LOG function try out");

    LOG_IF_FAILED(true, "LOG_IF_FAILED true, this log will never be display.");
    LOG_IF_FAILED(false, "LOG_IF_FAILED false, logging this error.");

    FATAL_CHECK(true, "This will nvr be shown, else it will exit the whole program.");

    TRY(true, "TRY true value, this log will never be display.");
    TRY(false, "TRY false value, logging this error.");
    LOG("This log will never display too!");
}

void testLogRotation()
{
    LOG_ENTRY;

    // Generate approximately 6MB of log data
    const int iIterations = 600;   // Number of log entries
    const int iPayloadSize = 1024; // 1KB per message

    for (int i = 1; i <= iIterations; ++i)
    {
        std::string payload(iPayloadSize, 'A' + (i % 26));
        LOG("Rotation test message %04d: %s", i, payload.c_str());
        if (i % 100 == 0)
        {
            printf("Generated %d/%d log messages (%.2fMB)\n",
                   i, iIterations, (i * iPayloadSize) / 1024.0f / 1024.0f);
        }
    }

    LOG("Log rotation test completed");
}

EResult testEResult(bool bTestPass)
{
    return bTestPass ? EResult::ok() : EResult::fail("testEResult Fail log");
}