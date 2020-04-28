//
// Created by Linux Oid on 28.04.2020.
//

#ifndef COCKTORRENT_TORRENTMULTIPLEFILEINFO_H
#define COCKTORRENT_TORRENTMULTIPLEFILEINFO_H

#include "bencode.h"
#include "bencodeelementadapter.h"
#include "torrentbasefileinfo.h"
#include <vector>

/**
 * @class TorrentMultipleFileInfo
 * @brief Класс для хранения инфы в случае нескольких файлов
 * @author https://github.com/s3ponia
 */
class TorrentMultipleFileInfo : public TorrentBaseFileInfo {
public:
    struct File;
    using InfoDictionary = TorrentBaseFileInfo::Dictionary;
    using String = TorrentBaseFileInfo::String;
    using Integer = TorrentBaseFileInfo::Integer;
    using List = std::vector<File>;
    using BencodeElement = TorrentBaseFileInfo::BencodeElement;
    using BencodeAdapter = TorrentBaseFileInfo::BencodeAdapter;

    struct File  {
        File(BencodeElement const &dict);
        Integer length;
        String path;
    };

    explicit TorrentMultipleFileInfo(BencodeElement const &el);

    const List &files() const;

private:
    List files_;
};


#endif //COCKTORRENT_TORRENTMULTIPLEFILEINFO_H
