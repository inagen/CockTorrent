#include "logger.h"
#include <iostream>
#include "logger.h"
#include "bencode.h"
#include "bencodeelementadapter.h"

int main() {
    Logger::get_instance()->Debug("KEK");
    std::string_view expression = "d8:announce42:http://bt3.rutracker.org/ann?uk=bq6T1sFtyV13:"
                                  "announce-listll42:http://bt3.rutracker.org/ann?uk=bq6T1sFt"
                                  "yVel31:http://retracker.local/announceee7:comment50:http:/"
                                  "/rutracker.org/forum/viewtopic.php?t=299442910:created by1"
                                  "3:uTorrent/202013:creation datei1275579654e8:encoding5:UTF"
                                  "-84:infod6:lengthi346799104e4:name29:Installer-CityoftheDa"
                                  "leks.exe12:piece lengthi524288e6:pieces10:1234567890e";
    auto res = bencode::Decode(expression);
    BencodeElementAdapter adapter{&res};
    std::cout << adapter["announce"].string() << '\n' << adapter["announce-list"][0][0].string();
    return 0;
}
