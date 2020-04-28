//
// Created by Linux Oid on 28.04.2020.
//

#include "torrentmultiplefileInfo.h"

TorrentMultipleFileInfo::TorrentMultipleFileInfo(const TorrentMultipleFileInfo::BencodeElement &el)
        : TorrentBaseFileInfo(el),
          files_{adapt(&el)["files"].list().cbegin(), adapt(&el)["files"].list().cend()} {

}

const TorrentMultipleFileInfo::List &TorrentMultipleFileInfo::files() const {
    return files_;
}

TorrentMultipleFileInfo::File::File(const TorrentMultipleFileInfo::BencodeElement &dict) :
        length(adapt(&dict)["length"].integer()), path(adapt(&dict)["path"].string()) {

}
