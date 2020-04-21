#ifndef BENCODE_H
#define BENCODE_H

#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <variant>
#include "logger.h"

namespace bencode {

struct BencodeElement;
using BencodeInt = long long;
using BencodeString = std::string;
using BencodeDictionary = std::map<BencodeString, BencodeElement>;
using BencodeList = std::vector<BencodeElement>;

struct BencodeElement {
    std::variant<BencodeInt, BencodeString, BencodeDictionary, BencodeList> data;
};

class BencodeParser {
    std::string expression;
    size_t ind;

public:
    BencodeParser(const std::string &);
    BencodeParser(const BencodeParser &) = delete;
    BencodeParser() = delete;
    const BencodeParser &operator=(const BencodeParser &) = delete;
    BencodeElement Parse(const std::string& expression);
    BencodeElement Parse();

private:
    BencodeInt ParseInt();
    BencodeElement ParseBencodeElement();
    BencodeInt ParseBencodeInt();
    BencodeString ParseBencodeString();
    BencodeDictionary ParseBencodeDictionary();
    BencodeList ParseBencodeList();
};


} // namespace bencode

#endif // BENCODE_H