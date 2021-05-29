#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <set>
#include <functional>
#include <unordered_map>

#define LOG_LINE(msg) std::cout << msg << std::endl;

class LRScoer {
    typedef float (LRScoer::*ScorerFunc_t)(const std::string &feature_name, const std::string &field_name, float weight);
    struct Params {
        ScorerFunc_t scorer_func;
        std::string field_name;
    };
    static const std::unordered_map<std::string, Params> feature_name_to_params_map;
public:
    void test(const std::string &feature_name) {
        const auto it = feature_name_to_params_map.find(feature_name);
        if (it != feature_name_to_params_map.end()) {
            const auto & params = it->second;
            (this->*params.scorer_func)(feature_name, params.field_name, 1);
        }
    }

    float BuildSingleDocPlugV4(const std::string &feature_name, const std::string &field_name, float weight) {
        float score = 0.5;
        LOG_LINE(__FUNCTION__ <<  ", feature_name:" << feature_name << ", field_name:" << field_name << ", weight:" << weight << ", score:" << score);
        return score;
    }

    float BuildCommonDistPlugV4(const std::string &feature_name, const std::string &field_name, float weight) {
        float score = 0.7;
        LOG_LINE(__FUNCTION__ <<  ", feature_name:" << feature_name << ", field_name:" << field_name << ", weight:" << weight << ", score:" << score);
        return score;
    }
};

const std::unordered_map<std::string, LRScoer::Params> LRScoer::feature_name_to_params_map {
        {"priority", {&LRScoer::BuildSingleDocPlugV4, "rec_reason_priority"}},
        {"M_c3shop_innerproduct", {&LRScoer::BuildCommonDistPlugV4, "c3shop"}},
        {"M_c1pw_innerproduct", {&LRScoer::BuildCommonDistPlugV4, "c1pw"}}

};

int main() {
    LRScoer lrScoer;
    lrScoer.test("M_c3shop_innerproduct");
    lrScoer.test("M_c1pw_innerproduct");
    lrScoer.test("priority");
}
