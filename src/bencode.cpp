#include "bencode.h"
#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <variant>
#include <charconv>
#include "logger.h"

#define PARSE_EXCEPTION_IF(CONDITION)\
    if (true) {\
        if ((CONDITION)) {\
        }\
    }

using namespace bencode;

BencodeParser::BencodeParser(const std::string& expr) {
    expression = expr;
    ind = 0;
}

BencodeElement BencodeParser::Parse() {
    auto result = ParseBencodeElement();
    PARSE_EXCEPTION_IF(ind != expression.size());
    return result;
}

BencodeElement BencodeParser::Parse(const std::string& expr) {
    expression = expr;
    ind = 0;
    auto result = ParseBencodeElement();
    PARSE_EXCEPTION_IF(ind != expression.size());
    return result;
}

BencodeElement BencodeParser::ParseBencodeElement() {
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

BencodeInt BencodeParser::ParseInt() {
    BencodeInt res;
    auto [p, ec] = std::from_chars(expression.data() + ind, expression.data() + expression.size(), res);
    
    PARSE_EXCEPTION_IF(ec != std::errc());
    
    ind = p - expression.data();
    return res;
}

BencodeInt BencodeParser::ParseBencodeInt() {
    PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind) != 'i' || ++ind >= expression.size());
    
    BencodeInt res = ParseInt();

    PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind++) != 'e');

    return res;
}

BencodeString BencodeParser::ParseBencodeString() {
    PARSE_EXCEPTION_IF(ind >= expression.size() || !std::isdigit(expression.at(ind)));

    BencodeInt stringLen = ParseInt();

    PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind) != ':');
    
    ind++;

    PARSE_EXCEPTION_IF(ind + stringLen >= expression.size());

    BencodeString result = expression.substr(ind, stringLen);
    ind += stringLen;
    return result;
}

BencodeList BencodeParser::ParseBencodeList() {
    PARSE_EXCEPTION_IF(ind >= expression.size() || expression.at(ind) != 'l');
    ind++;
    BencodeList result;
    while (ind < expression.size() && expression.at(ind) != 'e') {
        result.push_back(ParseBencodeElement());
        ind++;
    }
    ind++;
    return result;
}

BencodeDictionary BencodeParser::ParseBencodeDictionary() {
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