#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
int main(int argc, char *argv[])
{
    std::vector<std::string> file_names;
    printf("%s\n", argv[1]);
    dirent *dir_pointer;
    DIR *dir = opendir(argv[1]);
    if (dir != NULL)
    {
        char *filename = new char[258];

        while ((dir_pointer = readdir(dir)) != NULL)
        {
            if (dir_pointer->d_name[0] != '.')
            {
                sprintf(filename, "%s/%s", argv[1], dir_pointer->d_name);
                std::string cpp_str(filename);
                file_names.push_back(cpp_str);
            }
            // printf("%s/%s\n", argv[1], dir_pointer->d_name);
        }
        for (std::string x : file_names)
        {
            std::cout << x << "\n";
        }
    }
    closedir(dir);
}