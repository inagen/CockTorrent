#ifndef BENCODE_H
#define BENCODE_H

#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <variant>
#include "logger.h"

namespace bencode {

    struct  BencodeElement;
    using   BencodeInt = long long;
    using   BencodeString = std::string;
    using   BencodeDictionary = std::map<BencodeString, BencodeElement>;
    using   BencodeList = std::vector<BencodeElement>;

    struct BencodeElement {
        std::variant<BencodeInt, BencodeString, BencodeDictionary, BencodeList> data;
    };

    BencodeElement  Decode(const std::string_view&);
    std::string     Encode(const BencodeElement&);

} // namespace bencode

#endif // BENCODE_H