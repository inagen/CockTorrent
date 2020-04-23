#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <variant>
#include <charconv>
#include "logger.h"
#include "bencode.h"

#define PARSE_EXCEPTION_IF(CONDITION)\
    if (true) {\
        if ((CONDITION)) {\
        }\
    }

namespace bencode {

    BencodeElement      ParseBencodeElement(std::string_view &);
    BencodeInt          ParseInt(std::string_view &);
    BencodeInt          ParseBencodeInt(std::string_view &);
    BencodeString       ParseBencodeString(std::string_view &);
    BencodeList         ParseBencodeList(std::string_view &);
    BencodeDictionary   ParseBencodeDictionary(std::string_view &);

    BencodeElement Decode(std::string_view expression) {
        auto result = ParseBencodeElement(expression);
        PARSE_EXCEPTION_IF(expression.size() != 0);
        return result;
    }

    BencodeElement ParseBencodeElement(std::string_view & expression) {
        BencodeElement result;
        char cur = expression.at(0);
        expression.remove_prefix(1);
        if (cur == 'i') {
            result.data = ParseBencodeInt(expression);
        } else if (cur == 'l') {
            result.data = ParseBencodeList(expression);
        } else if (cur == 'd') {
            result.data = ParseBencodeDictionary(expression);
        } else if (std::isdigit(cur)) {
            result.data = ParseBencodeString(expression);
        } else {
            PARSE_EXCEPTION_IF(true);
        }
        return result;
    }

    BencodeInt ParseInt(std::string_view & expression) {
        BencodeInt res;
        auto[p, ec] = std::from_chars(expression.data(), expression.data() + expression.size(), res);

        PARSE_EXCEPTION_IF(ec != std::errc());

        expression.remove_prefix(p - expression.data());
        return res;
    }

    BencodeInt ParseBencodeInt(std::string_view & expression) {
        PARSE_EXCEPTION_IF(expression.size() < 3|| expression.at(0) != 'i');
        expression.remove_prefix(1);

        BencodeInt res = ParseInt(expression);
        PARSE_EXCEPTION_IF(expression.size() < 1 || expression.at(0) != 'e');

        expression.remove_prefix(1);
        return res;
    }

    BencodeString ParseBencodeString(std::string_view & expression) {
        PARSE_EXCEPTION_IF(expression.size() < 1 || !std::isdigit(expression.at(0)));

        BencodeInt stringLen = ParseInt(expression);

        PARSE_EXCEPTION_IF( expression.size() < 1 || expression.at(0) != ':');

        expression.remove_prefix(1);

        PARSE_EXCEPTION_IF(expression.size() < stringLen);

        BencodeString result = std::string(expression.substr(0, stringLen));
        expression.remove_prefix(stringLen);
        return result;
    }

    BencodeList ParseBencodeList(std::string_view & expression) {
        PARSE_EXCEPTION_IF(expression.size() < 1|| expression.at(0) != 'l');
        expression.remove_prefix(1);
        BencodeList result;
        while (expression.size() > 0 && expression.at(0) != 'e') {
            result.push_back(ParseBencodeElement(expression));
        }
       expression.remove_prefix(1);
        return result;
    }

    BencodeDictionary ParseBencodeDictionary(std::string_view & expression) {
        PARSE_EXCEPTION_IF(expression.size() < 1 || expression.at(0) != 'd');
        expression.remove_prefix(1);
        BencodeDictionary result;
        while (expression.size() > 0 && expression.at(0) != 'e') {
            BencodeString key = ParseBencodeString(expression);
            BencodeElement value = ParseBencodeElement(expression);
            result.insert({key, value});
        }
        expression.remove_prefix(1);
        return result;
    }
}