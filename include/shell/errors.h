#pragma once

#include <stdexcept>
#include <string>

#include <shell/fmt.h>

namespace shell
{

class Error : public std::exception
{
public:
    Error(const std::string& message)
        : message(message) {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }

private:
    std::string message;
};

class FormattedError : public Error
{
public:
    template<typename... Args>
    FormattedError(const std::string& format, Args&&... args)
        : Error(fmt::format(format, std::forward<Args>(args)...)) {}
};

class ParseError : public FormattedError
{
public:
    using FormattedError::FormattedError;
};

}  // namespace shell
