//
// Created by Linux Oid on 28.04.2020.
//

#include "torrentbasefileinfo.h"

TorrentBaseFileInfo::TorrentBaseFileInfo(const TorrentBaseFileInfo::BencodeElement &el) :
        announce_(adapt(&el)["announce"].string()), name_(adapt(&el)["info"]["name"].string()),
        piece_length_(adapt(&el)["info"]["piece length"].integer()), pieces_(adapt(&el)["info"]["pieces"].string()) {

}

const TorrentBaseFileInfo::String &TorrentBaseFileInfo::announce() const {
    return announce_;
}

const TorrentBaseFileInfo::String &TorrentBaseFileInfo::pieces() const {
    return pieces_;
}

const TorrentBaseFileInfo::String &TorrentBaseFileInfo::name() const {
    return name_;
}

TorrentBaseFileInfo::Integer TorrentBaseFileInfo::piece_length() const {
    return piece_length_;
}
