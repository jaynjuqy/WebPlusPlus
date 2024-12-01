#pragma once

#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> model_renames;
std::unordered_map<std::string, std::unordered_map<std::string, std::string>> column_renames;

int main(){
    //insert any renames into the above maps
    // column_renames["User"] = {"age", "dob"};
    return 0;
}

