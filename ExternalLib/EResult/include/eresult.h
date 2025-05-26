#include <cassert>
#include <string>

class EResult
{
public:
    static EResult ok() { return EResult(true, ""); }
    static EResult fail(const std::string &cstrError) { return EResult(false, cstrError); }

    bool isOk() const { return m_isOk; }
    bool isFail() const { return !m_isOk; }

    const char *error() const
    {
        if (m_isOk)
            return "No error in successful result";
        return m_strError.c_str();
    }

private:
    EResult(bool isOk, const std::string &cstrError)
        : m_isOk(isOk), m_strError(cstrError) {}

    bool m_isOk;
    std::string m_strError;
};