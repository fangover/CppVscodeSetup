#include <BasicStdLib.h>

template <typename T>
void testModuleSet()
{
    auto module = std::make_unique<T>();
    module->print();
    module->setValue(module->getValue() + (typeid(T) == typeid(ModuleOopTest::ChildA) ? 1 : 10));
    module->print();
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

void test_log_rotation()
{
    LOG_ENTRY;

    // Generate approximately 6MB of log data
    const int iterations = 600;    // Number of log entries
    const int payload_size = 1024; // 1KB per message

    for (int i = 1; i <= iterations; ++i)
    {
        std::string payload(payload_size, 'A' + (i % 26));
        LOG("Rotation test message %04d: %s", i, payload.c_str());
        if (i % 100 == 0)
        {
            printf("Generated %d/%d log messages (%.2fMB)\n",
                   i, iterations, (i * payload_size) / 1024.0f / 1024.0f);
        }
    }

    LOG("Log rotation test completed");
}