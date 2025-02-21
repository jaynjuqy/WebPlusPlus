#pragma once

#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> model_renames;
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> column_renames;

//TODO we could pass a nlohmann::json object inside make_migrations fn so that we could avoid this stuff...
//so that we could save on space and also avoid all the warnings of defining stuff in header files...
