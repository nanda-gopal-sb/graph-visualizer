#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
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
                // std::cout << "File: " << entry.path() << std::endl;
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

int main(int argc, char *argv[])
{
    getFiles(argv[1]);
    for (const std::string &filename : file_names)
    {
        std::cout << filename << std::endl;
    }
}
