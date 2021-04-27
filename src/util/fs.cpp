#include <cstring>
#include <string>
#include <fstream>
#include <sys/stat.h>

namespace fs {

    static struct stat info;

    int get_dir(char* str) {
        return std::string(str).find_last_of("\\/");
    }

    bool is_file(char* str) {
        std::ifstream test(str); 
        return !(!test);
    }

    bool is_directory(char* str) {
        if (stat(str, &info ) != 0)
            return false;
        
        return info.st_mode & S_IFDIR;
    }

    // void path(char* str) {
    //     p = str;
    // }

    // bool exists() {
    //     return (stat(p, &info ) == 0);
    // }

    // bool exists_file() {
    //     std::ifstream test(p); 
    //     return !!test;
    // }

    // bool exists_dir() {
    //     if (stat(p, &info ) != 0)
    //         return false;
        
    //     return info.st_mode & S_IFDIR;
    // }

    // void to_dir() {
    //     size_t pos = std::string(p).find_last_of("\\/");
    //     p[pos] = '\0';
    // }

    // void append_file(char* str) {
    //     strcat(p, str);
    // }

}
