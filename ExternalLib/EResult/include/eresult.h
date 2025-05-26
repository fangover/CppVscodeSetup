#include <cassert>
#include <string>

class EResult
{
public:
    static EResult ok() { return EResult(true, ""); }
    static EResult fail(const std::string &error) { return EResult(false, error); }

    bool isOk() const { return m_isOk; }
    bool isFail() const { return !m_isOk; }

    const char *error() const
    {
        if (m_isOk)
            return "No error in successful result";
        return m_strError.c_str();
    }

private:
    EResult(bool isOk, const std::string &error)
        : m_isOk(isOk), m_strError(error) {}

    bool m_isOk;
    std::string m_strError;
};