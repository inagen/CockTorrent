#include "logger.h"
#include <iostream>
#include "logger.h"
#include "bencode.h"

int main() {
    Logger::get_instance()->Debug("KEK");
    std::string_view expression = "d8:announce42:http://bt3.rutracker.org/ann?uk=bq6T1sFtyV13:announce-l"
                                  "istll42:http://bt3.rutracker.org/ann?uk=bq6T1sFtyVel31:http://retrac"
                                  "ker.local/announceee7:comment50:http://rutracker.org/forum/viewtopi"
                                  "c.php?t=299442910:created by13:uTorrent/202013:creation datei127557"
                                  "9654e8:encoding5:UTF-84:infod6:lengthi346799104e4:name29:Installer-C"
                                  "ityoftheDaleks.exe12:piece lengthi524288e6:pieces2:abee";
    //std::string_view expression = "8:abacabad";
    auto res = bencode::Decode(expression);
    auto encoded = bencode::Encode(res);
    std::cout << encoded << std::endl;
    std::cout << expression << std::endl;
    std::cout << expression.compare(encoded) << std::endl;
    std::cout << bencode::Serialize(res) << std::endl;
    return 0;
}
