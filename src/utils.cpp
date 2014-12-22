#include "utils.hpp"
#include "logger.hpp"

using namespace std;

string gBasePath;

string getBasePath() {
    return gBasePath;
}

void setBasePath(const string &path) {
    gBasePath = path;
}
