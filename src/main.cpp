#include "logger.h"
#include <iostream>
#include "torrentsinglefileinfo.h"
#include "logger.h"
#include "bencode.h"
#include "bencodeelementadapter.h"

int main() {
    Logger::get_instance()->Debug("KEK");
    std::ifstream input_file{"../test-torrent-files/doctor-who-single-file.torrent"};
    std::string expression{std::istream_iterator<char>{input_file}, std::istream_iterator<char>{}};
    std::cout << expression;
    const auto res = bencode::Decode(expression);
    TorrentSingleFileInfo s_file_info{res};

    return 0;
}
