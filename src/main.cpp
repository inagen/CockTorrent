#include "logger.h"
#include <iostream>
#include "logger.h"
#include "bencode.h"

int main() {
    Logger::get_instance()->Debug("KEK");
    auto res = bencode::Decode("d8:announce42:http://bt3.rutracker.org/ann?uk=bq6T1sFtyV13:"
                               "announce-listll42:http://bt3.rutracker.org/ann?uk=bq6T1sFt"
                               "yVel31:http://retracker.local/announceee7:comment50:http:/"
                               "/rutracker.org/forum/viewtopic.php?t=299442910:created by1"
                               "3:uTorrent/202013:creation datei1275579654e8:encoding5:UTF"
                               "-84:infod6:lengthi346799104e4:name29:Installer-CityoftheDa"
                               "leks.exe12:piece lengthi524288e6:pieces13240:���R)�ˬ�h�g"
                               "�YQTX\u001B�\u000B�\f���e�8�{CZ\u0011�:\u001C��"
                               "�z�3�scx�6�;SY���o��\u0006��=<�]J��_��x�'=�#�B");
    return 0;
}
