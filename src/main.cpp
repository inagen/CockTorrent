#include "logger.h"
#include <iostream>
#include <ios>
#include "torrentmultiplefileInfo.h"
#include "torrentsinglefileinfo.h"
#include "logger.h"
#include "bencode.h"
#include "bencodeelementadapter.h"

int main() {
    Logger::get_instance()->Debug("KEK");
    std::ifstream input_file{"../test-torrent-files/doctor-who-single-file.torrent"};
    std::string expression{std::istreambuf_iterator<char>{input_file}, std::istreambuf_iterator<char>{}};
    auto res = bencode::Decode(expression);
    TorrentSingleFileInfo s_file_s_info{res};
    std::cout << s_file_s_info.announce() << '\n';

    input_file.close();
    input_file.open("../test-torrent-files/Gravity-Falls-Season-1.torrent", std::ios_base::in);
    expression = std::string{std::istreambuf_iterator<char>{input_file}, std::istreambuf_iterator<char>{}};
    res = bencode::Decode(expression);

    TorrentMultipleFileInfo s_file_m_info{res};
    std::cout << s_file_m_info.announce();

    return 0;
}
