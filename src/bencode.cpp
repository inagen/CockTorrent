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

    BencodeElement ParseBencodeElement();

    BencodeInt ParseInt();

    BencodeInt ParseBencodeInt();

    BencodeString ParseBencodeString();

    BencodeList ParseBencodeList();

    BencodeDictionary ParseBencodeDictionary();

    std::string_view expression;
    uint64_t ind;

    BencodeElement Decode(const std::string_view &expr) {
        expression = expr;
        ind = 0;
        auto result = ParseBencodeElement();
        PARSE_EXCEPTION_IF(ind != expression.size());
        return result;
    }

    BencodeElement ParseBencodeElement() {
        BencodeElement result;
        char cur = expression.at(ind);
        if (cur == 'i') {
            result.data = ParseBencodeInt();
        } else if (cur == 'l') {
            result.data = ParseBencodeList();
        } else if (cur == 'd') {
            result.data = ParseBencodeDictionary();
        } else if (std::isdigit(cur)) {
            result.data = ParseBencodeString();
        } else {
            PARSE_EXCEPTION_IF(true);
        }
        return result;
    }

    BencodeInt ParseInt() {
        BencodeInt res;
        auto[p, ec] = std::from_chars(expression.data() + ind, expression.data() + expression.size(), res);

        PARSE_EXCEPTION_IF(ec != std::errc());

        ind = p - expression.data();
        return res;
    }

    BencodeInt ParseBencodeInt() {
        PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind) != 'i' || ++ind >= expression.size());

        BencodeInt res = ParseInt();

        PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind++) != 'e');

        return res;
    }

    BencodeString ParseBencodeString() {
        PARSE_EXCEPTION_IF(ind >= expression.size() || !std::isdigit(expression.at(ind)));

        BencodeInt stringLen = ParseInt();

        PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind) != ':');

        ind++;

        PARSE_EXCEPTION_IF(ind + stringLen >= expression.size());

        BencodeString result = std::string(expression.substr(ind, stringLen));
        ind += stringLen;
        return result;
    }

    BencodeList ParseBencodeList() {
        PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind) != 'l');
        ind++;
        BencodeList result;
        while (ind < expression.size() && expression.at(ind) != 'e') {
            result.push_back(ParseBencodeElement());
        }
        ind++;
        return result;
    }

    BencodeDictionary ParseBencodeDictionary() {
        PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind) != 'd');
        ind++;
        BencodeDictionary result;
        while (ind < expression.size() && expression.at(ind) != 'e') {
            BencodeString key = ParseBencodeString();
            BencodeElement value = ParseBencodeElement();
            result.insert({key, value});
        }
        ind++;
        return result;
    }
}