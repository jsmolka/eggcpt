#pragma once

#include <algorithm>
#include <vector>

#include <shell/locale.h>
#include <shell/traits.h>
#include <shell/utility.h>

namespace shell
{

namespace detail
{

template<typename String>
std::size_t sizeExcludingTerminator(const String& str)
{
    if constexpr (std::is_array_v<String>)
        return sizeof(str) - 1;
    else
        return str.size();
}

}  // namespace detail

template<typename String, typename Predicate>
void trimLeftIf(String& str, Predicate pred)
{
    str.erase(
        std::begin(str),
        std::find_if_not(
            std::begin(str),
            std::end(str),
            pred));
}

template<typename String>
void trimLeft(String& str, const std::locale& locale = std::locale())
{
    trimLeftIf(str, IsSpace<range_value_t<String>>(locale));
}

template<typename String, typename Predicate>
String trimLeftCopyIf(const String& str, Predicate pred)
{
    return String(
        std::find_if_not(
            std::begin(str),
            std::end(str),
            pred),
        std::end(str));
}

template<typename String>
String trimLeftCopy(const String& str, const std::locale& locale = std::locale())
{
    return trimLeftCopyIf(str, IsSpace<range_value_t<String>>(locale));
}

template<typename String, typename Predicate>
void trimRightIf(String& str, Predicate pred)
{
    str.erase(
        std::find_if_not(
            std::rbegin(str),
            std::rend(str),
            pred).base(),
        std::end(str));
}

template<typename String>
void trimRight(String& str, const std::locale& locale = std::locale())
{
    trimRightIf(str, IsSpace<range_value_t<String>>(locale));
}

template<typename String, typename Predicate>
String trimRightCopyIf(const String& str, Predicate pred)
{
    return String(
        std::begin(str),
        std::find_if_not(
            std::rbegin(str),
            std::rend(str),
            pred).base());
}

template<typename String>
String trimRightCopy(const String& str, const std::locale& locale = std::locale())
{
    return trimRightCopyIf(str, IsSpace<range_value_t<String>>(locale));
}

template<typename String, typename Predicate>
void trimIf(String& str, Predicate pred)
{
    trimLeftIf(str, pred);
    trimRightIf(str, pred);
}

template<typename String>
void trim(String& str, const std::locale& locale = std::locale())
{
    trimIf(str, IsSpace<range_value_t<String>>(locale));
}

template<typename String, typename Predicate>
String trimCopyIf(const String& str, Predicate pred)
{
    return String(
        std::find_if_not(
            std::begin(str),
            std::end(str),
            pred),
        std::find_if_not(
            std::rbegin(str),
            std::rend(str),
            pred).base());
}

template<typename String>
String trimCopy(const String& seq, const std::locale& locale = std::locale())
{
    return trimCopyIf(seq, IsSpace<range_value_t<String>>(locale));
}

template<typename String>
void toLower(String& str, const std::locale& locale = std::locale())
{
    std::transform(
        std::begin(str),
        std::end(str),
        std::begin(str),
        ToLower<range_value_t<String>>(locale));
}

template<typename String>
String toLowerCopy(const String& str, const std::locale& locale = std::locale())
{
    String res{};
    res.reserve(detail::sizeExcludingTerminator(str));

    std::transform(
        std::begin(str),
        std::end(str),
        std::back_inserter(res),
        ToLower<range_value_t<String>>(locale));

    return res;
}

template<typename String>
void toUpper(String& str, const std::locale& locale = std::locale())
{
    std::transform(
        std::begin(str),
        std::end(str),
        std::begin(str),
        ToUpper<range_value_t<String>>(locale));
}

template<typename String>
String toUpperCopy(const String& str, const std::locale& locale = std::locale())
{
    String res{};
    res.reserve(detail::sizeExcludingTerminator(str));

    std::transform(
        std::begin(str),
        std::end(str),
        std::back_inserter(res),
        ToUpper<range_value_t<String>>(locale));

    return res;
}

template<typename String, typename StringFrom, typename StringTo>
void replaceFirst(String& str, const StringFrom& from, const StringTo& to)
{
    typename String::size_type pos = str.find(from);

    if (pos != String::npos)
        str.replace(pos, detail::sizeExcludingTerminator(from), to);
}

template<typename String, typename StringFrom, typename StringTo>
String replaceFirstCopy(const String& str, const StringFrom& from, const StringTo& to)
{
    String res(str);
    replaceFirst(res, from, to);

    return res;
}

template<typename String, typename StringFrom, typename StringTo>
void replaceLast(String& str, const StringFrom& from, const StringTo& to)
{
    typename String::size_type pos = str.rfind(from);

    if (pos != String::npos)
        str.replace(pos, detail::sizeExcludingTerminator(from), to);
}

template<typename String, typename StringFrom, typename StringTo>
String replaceLastCopy(const String& str, const StringFrom& from, const StringTo& to)
{
    String res(str);
    replaceLast(res, from, to);

    return res;
}

template<typename String, typename StringFrom, typename StringTo>
void replaceAll(String& str, const StringFrom& from, const StringTo& to)
{
    typename String::size_type pos = 0;

    while ((pos = str.find(from, pos)) != String::npos)
    {
        str.replace(pos, detail::sizeExcludingTerminator(from), to);
        pos += detail::sizeExcludingTerminator(to);
    }
}

template<typename String, typename StringFrom, typename StringTo>
String replaceAllCopy(const String& str, const StringFrom& from, const StringTo& to)
{
    String res(str);
    replaceAll(res, from, to);

    return res;
}

template<typename OutputIterator, typename String, typename StringDelimiter>
OutputIterator split(OutputIterator out, const String& str, const StringDelimiter& del)
{
    auto end = str.find(del);
    auto pos = static_cast<typename String::size_type>(0);

    while (end != String::npos)
    {
        *out = str.substr(pos, end - pos);
         pos = end + detail::sizeExcludingTerminator(del);
         end = str.find(del, pos);
    }
    *out = str.substr(pos, end);

    return out;
}

template<typename String, typename StringDelimiter>
std::vector<String> split(const String& str, const StringDelimiter& del)
{
    std::vector<String> res;
    split(std::back_inserter(res), str, del);

    return res;
}

template<typename Range, typename StringDelimiter>
range_value_t<Range> join(const Range& range, const StringDelimiter& del)
{
    range_value_t<Range> res{};

    for (auto [pos, str] : enumerate(range))
    {
        if (pos != 0)
            res.append(del);

        res.append(str);
    }
    return res;
}

}  // namespace shell
