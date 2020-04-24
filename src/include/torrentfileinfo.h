//
// Created by Linux Oid on 24.04.2020.
//

#ifndef COCKTORRENT_TORRENTFILEINFO_H
#define COCKTORRENT_TORRENTFILEINFO_H

#include "bencode.h"
#include <string>

class TorrentFileInfo {
public:
    using InfoDictionary = bencode::BencodeDictionary;
private:
    std::string announce;
    InfoDictionary info;
};


#endif //COCKTORRENT_TORRENTFILEINFO_H
