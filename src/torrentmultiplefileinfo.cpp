//
// Created by Linux Oid on 28.04.2020.
//

#include "torrentmultiplefileInfo.h"

TorrentMultipleFileInfo::TorrentMultipleFileInfo(const TorrentMultipleFileInfo::BencodeElement &el)
        : TorrentBaseFileInfo(el),
          files_{adapt(&el)["info"]["files"].list().cbegin(), adapt(&el)["info"]["files"].list().cend()} {

}

const TorrentMultipleFileInfo::List &TorrentMultipleFileInfo::files() const {
    return files_;
}

TorrentMultipleFileInfo::File::File(const TorrentMultipleFileInfo::BencodeElement &dict) :
        length(adapt(&dict)["length"].integer()), path(ListFromBencode(adapt(&dict)["path"].list())) {

}

TorrentMultipleFileInfo::File::List
TorrentMultipleFileInfo::File::ListFromBencode(const BencodeAdapter::ListType &el) {
    class LasyIterator {
    public:
        using difference_type = ptrdiff_t;
        using value_type = const String;
        using pointer = value_type *;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        explicit LasyIterator(
                const BencodeAdapter::ListType::const_iterator &iterator)
                : iterator_(
                iterator) {}

        LasyIterator &operator++() {
            ++iterator_;
            return *this;
        }

        LasyIterator operator++(int) {
            auto save = *this;
            ++iterator_;
            return save;
        }

        reference operator*() const {
            return adapt(&*iterator_).string();
        }

        bool operator==(const LasyIterator &rhs) const {
            return iterator_ == rhs.iterator_;
        }

        bool operator!=(const LasyIterator &rhs) const {
            return !(rhs == *this);
        }

    private:
        BencodeAdapter::ListType::const_iterator iterator_;
    };
    return TorrentMultipleFileInfo::File::List{LasyIterator{el.cbegin()}, LasyIterator{el.cend()}};
}
