#include "Engine.h"

#include <fstream>

namespace Util
{

std::string fileRead(std::string path_)
{
    assert(!path_.empty());

    std::ifstream file(path_);
    if (!file.is_open())
    {
        Log::error("Failed to open file: %s", path_.c_str());
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

    return content;
}

void fileWrite(std::string path_, std::string content_)
{
    std::ofstream file(path_);
    file << content_;
    file.close();
}

} // namespace Util