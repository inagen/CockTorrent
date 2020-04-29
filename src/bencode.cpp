#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <variant>
#include <exception>
#include <charconv>
#include "logger.h"
#include "bencode.h"

#define PARSE_EXCEPTION_IF(CONDITION)\
    if (true) {\
        if ((CONDITION)) {\
            Logger::get_instance()->Error("Bencode parsing error occured");\
            throw ParseError("Bencode parsing error");\
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
        PARSE_EXCEPTION_IF(!expression.empty());
        return result;
    }

    BencodeElement ParseBencodeElement(std::string_view & expression) {
        BencodeElement result;
        char cur = expression.at(0);
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
        PARSE_EXCEPTION_IF(expression.empty() || expression.at(0) != 'i');
        expression.remove_prefix(1);

        BencodeInt res = ParseInt(expression);
        PARSE_EXCEPTION_IF(expression.empty() || expression.at(0) != 'e');

        expression.remove_prefix(1);
        return res;
    }

    BencodeString ParseBencodeString(std::string_view & expression) {
        PARSE_EXCEPTION_IF(expression.empty() || !std::isdigit(expression.at(0)));

        BencodeInt stringLen = ParseInt(expression);

        PARSE_EXCEPTION_IF( expression.empty() || expression.at(0) != ':');

        expression.remove_prefix(1);

        PARSE_EXCEPTION_IF(expression.size() < stringLen);

        BencodeString result = std::string(expression.substr(0, stringLen));
        expression.remove_prefix(stringLen);
        return result;
    }

    BencodeList ParseBencodeList(std::string_view & expression) {
        PARSE_EXCEPTION_IF(expression.empty() || expression.at(0) != 'l');
        expression.remove_prefix(1);
        BencodeList result;
        while (!expression.empty() && expression.at(0) != 'e') {
            result.push_back(ParseBencodeElement(expression));
        }
        expression.remove_prefix(1);
        return result;
    }

    BencodeDictionary ParseBencodeDictionary(std::string_view & expression) {
        PARSE_EXCEPTION_IF(expression.empty() || expression.at(0) != 'd');
        expression.remove_prefix(1);
        BencodeDictionary result;
        while (!expression.empty() && expression.at(0) != 'e') {
            BencodeString key = ParseBencodeString(expression);
            BencodeElement value = ParseBencodeElement(expression);
            result.insert({key, value});
        }
        expression.remove_prefix(1);
        return result;
    }


    std::string EncodeDictionary(const BencodeDictionary&);
    std::string EncodeList(const BencodeList&);
    std::string EncodeString(const BencodeString&);
    std::string EncodeInt(const BencodeInt&);

    std::string Encode(const BencodeElement& element) {
        if (std::holds_alternative<BencodeInt>(element.data)) {
            return EncodeInt(std::get<BencodeInt>(element.data));
        } else if (std::holds_alternative<BencodeString>(element.data)) {
            return EncodeString(std::get<BencodeString>(element.data));
        } else if (std::holds_alternative<BencodeList>(element.data)) {
            return EncodeList(std::get<BencodeList>(element.data));
        } else if (std::holds_alternative<BencodeDictionary>(element.data)) {
            return EncodeDictionary(std::get<BencodeDictionary>(element.data));
        } else {
            return "";
        }
    }

    std::string EncodeDictionary(const BencodeDictionary& dictionary) {
        std::string result = "d";
        for (auto& it : dictionary) {
            result += EncodeString(it.first);
            result += Encode(it.second);
        }
        result += "e";
        return result;
    }

    std::string EncodeList(const BencodeList& list) {
        std::string result = "l";
        for (auto& it : list) {
            result += Encode(it);
        }
        result += "e";
        return result;
    }

    std::string EncodeString(const BencodeString& string) {
        size_t len = string.size();
        return std::to_string(len) + ":" + string;
    }

    std::string EncodeInt(const BencodeInt& val) {
        return "i" + std::to_string(val) + "e";
    }

    std::string SerializeDictionary(const BencodeDictionary&);
    std::string SerializeList(const BencodeList&);
    std::string SerializeString(const BencodeString&);
    std::string SerializeInt(const BencodeInt&);

    std::string Serialize(const BencodeElement& element) {
        if (std::holds_alternative<BencodeInt>(element.data)) {
            return SerializeInt(std::get<BencodeInt>(element.data));
        } else if (std::holds_alternative<BencodeString>(element.data)) {
            return SerializeString(std::get<BencodeString>(element.data));
        } else if (std::holds_alternative<BencodeList>(element.data)) {
            return SerializeList(std::get<BencodeList>(element.data));
        } else if (std::holds_alternative<BencodeDictionary>(element.data)) {
            return SerializeDictionary(std::get<BencodeDictionary>(element.data));
        } else {
            return "";
        }
    }

    std::string SerializeDictionary(const BencodeDictionary& dictionary) {
        std::string result = "{\n";
        for (auto& it : dictionary) {
            result += "\'" + SerializeString(it.first) + "\':";
            result += Serialize(it.second) + ",\n";
        }
        result = result.substr(0, result.length() - 2);
        result += "\n}";
        return result;
    }

    std::string SerializeList(const BencodeList& list) {
        std::string result = "[";
        for (auto& it : list) {
            result += Serialize(it) + ", ";
        }
        result = result.substr(0, result.length() - 2);
        result += "]";
        return result;
    }

    std::string SerializeString(const BencodeString& string) {
        return string;
    }

    std::string SerializeInt(const BencodeInt& val) {
        return std::to_string(val);
    }

}