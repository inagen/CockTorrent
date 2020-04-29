//
// Created by Timur Bairamukov
//

#ifndef BENCODE_H
#define BENCODE_H

#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <variant>
#include "logger.h"

namespace bencode {
    struct ParseError : std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    struct  BencodeElement;
    using   BencodeInt = long long;
    using   BencodeString = std::string;
    using   BencodeDictionary = std::map<BencodeString, BencodeElement>;
    using   BencodeList = std::vector<BencodeElement>;

    struct BencodeElement {
        std::variant<BencodeInt, BencodeString, BencodeDictionary, BencodeList> data;
    };

    BencodeElement  Decode(std::string_view);
    std::string     Encode(const BencodeElement&);
    std::string     Serialize(const BencodeElement&);

} // namespace bencode

#endif // BENCODE_H