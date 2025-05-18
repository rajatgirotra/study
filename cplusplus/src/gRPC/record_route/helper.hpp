#pragma once

#include <vector>
#include <string>
namespace routeguide {
    std::string GetDbFileContent();
    void ParseDb(const std::string& db, std::vector<Feature>* feature_list);
}