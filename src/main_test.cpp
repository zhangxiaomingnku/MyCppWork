#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <map>
#define LOG_LINE(msg) std::cout << msg << std::endl;


//void parseStrToInt64Vec(const std::string &data, std::vector<int64_t > *res) {
//    std::vector<std::string> res_str;
//    boost::algorithm::split(res_str, data, boost::is_any_of(","), boost::token_compress_on);
//    if (res_str.size() == 0) {
//        return;
//    }
//    for (std::string str : res_str) {
//        try {
//            res->push_back(atoll(str.c_str()));
//        } catch (std::exception & e) {
//            LOG(ERROR) << "error parseStrToInt64Vec " << e.what();
//        }
//    }
//}


int main(int argc, char* argv[])
{

    std::unique_ptr<std::map<std::string,std::string>> common_kv_map_ptr;
    if (common_kv_map_ptr == nullptr) {
        LOG_LINE("yes");
    }
    std::shared_ptr<std::vector<int64_t>> author_ids = std::make_shared<std::vector<int64_t>>();
    auto ptr= author_ids.get();
    ptr->push_back(1);
    ptr->push_back(2);

    for (auto id : *author_ids) {
        LOG_LINE(id);
    }

    int x = 100;
    int res = x / 1000;
    LOG_LINE(res);
    return 0;
}
