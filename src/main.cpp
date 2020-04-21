#include "logger.h"
#include <iostream>
#include "logger.h"
#include "bencode.h"

int main() {
    Logger::get_instance()->Debug("KEK");
    bencode::BencodeParser parser("d3:bar4:spam3:fooi42ee");
    parser.Parse();
    return 0;
}
