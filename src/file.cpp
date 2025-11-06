#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>
std::vector<std::string> file_names;
using namespace std::filesystem;
void getFiles(std::string path)
{
    if (exists(path) && is_directory(path))
    {
        for (const auto &entry :
             directory_iterator(path))
        {
            if (entry.path().filename().generic_string()[0] != '.')
            {
                std::cout << "File: " << entry.path() << std::endl;
                if (is_directory(entry.path()))
                {
                    getFiles(entry.path());
                }
                else
                {
                    file_names.push_back(entry.path());
                }
            }
        }
    }
}
std::vector<std::string> findAllAnchorTags(const std::string &filename)
{
    std::vector<std::string> results;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return results;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();
    std::regex anchorRegex(R"(<a\b[^>]*>.*?</a>)", std::regex::icase);
    std::sregex_iterator iter(content.begin(), content.end(), anchorRegex);
    std::sregex_iterator end;
    for (; iter != end; ++iter)
    {
        results.push_back(iter->str());
    }
    return results;
}
int main(int argc, char *argv[])
{
    std::vector<std::string> anchors;
    std::regex re(R"(<a([\s]+[^>]*)>(.*?)</a>)", std::regex_constants::icase);
    std::string myText;
    getFiles(argv[1]);
    std::cout << file_names.size();
    for (const std::string &filename : file_names)
    {
        std::ifstream MyReadFile(filename);
        std::cout << filename << std::endl;
        anchors = findAllAnchorTags(filename);
        for (std::string x : anchors)
        {
            std::cout << x << "\n";
        }
    }
}
