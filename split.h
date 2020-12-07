#include <vector>
#include <string>

std::vector<std::string> Split(const std::string& line) {
    std::vector<std::string> answer;
    std::string substr;
    for (auto& el : line) {
        if (el == ' ') {
            if (!substr.empty()) {
                answer.push_back(substr);
                substr.clear();
            }
        } else {
            substr.push_back(el);
        }
    }
    if (!substr.empty()) {
        answer.push_back(substr);
        substr.clear();
    }
    return answer;
}