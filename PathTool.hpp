#ifndef PathTool_hpp
#define PathTool_hpp

#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

#ifdef WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#endif

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <sstream>
#include <unistd.h>
#include <stdexcept>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace tools 
{
    class PathTool
    {

    public:

        PathTool()= default;
        [[maybe_unused]] static std::string get_executable_path ();
        [[maybe_unused]] static std::string find_parent_folder(std::string input, int times=1);
        [[maybe_unused]] static int remove_directory(const char *path);
        [[maybe_unused]] static bool checkfileexist(const std::string& filename);
        [[maybe_unused]] static bool checkfolderexist(const std::string& output_db_name);
        [[maybe_unused]] static std::string find_parent_folder_name(const std::string& path);
        [[maybe_unused]] static std::string get_current_dir_name(std::string path);
        [[maybe_unused]] static void get_files_include_name(std::string path, const std::string &name, std::vector<std::string> &files_with_name, bool return_full, bool sort);
        [[maybe_unused]] static void get_files_include_name_recursively (const std::string& path, const std::string& name, std::vector<std::string>& files_with_name);
        [[maybe_unused]] static void get_folders_include_name_recursively (const std::string& path, const std::string& name, std::vector<std::string>& folders_with_name);
        [[maybe_unused]] static void get_targetFile_in_targetFolder_recursively (const std::string& path, const std::string& folderName, const std::string& fileName, std::vector<std::string>& folders_with_name);
        [[maybe_unused]] static std::vector<std::string> get_files_include_name (std::string path, const std::string& name);
        [[maybe_unused]] static void check_and_delete_folder (const std::string& path);
        [[maybe_unused]] static void check_and_create_folder (const std::string& path);
        [[maybe_unused]] static void create_folder(std::string name);
        [[maybe_unused]] static char* string2char(const std::string& string);
        [[maybe_unused]] static inline bool isdigit(const std::string &string);
        /**
         This function will search all the files with given type within path (including folder, if no type is given).
         @param path The path to the folder you want to search
         @param type The type you want to search
         @param return_full Set true to return full path
         @param sort Set true the sort the result
         @return Return a vector
         */
        [[maybe_unused]] static std::vector<std::string> get_files_in_folder (std::string path, const std::string& type = "", bool return_full = false, bool sort = true);

        [[maybe_unused]] static void erase_chracter(std::string& input, const std::string& charact);
        [[maybe_unused]] static void replace_chracter(std::string& input, const std::string& charact, const std::string& with_this);
        [[maybe_unused]] static std::string remove_file_type (std::string path, const std::string& type="");
        [[maybe_unused]] static std::string getFileType(std::string pathIn);
        [[maybe_unused]] static int GetTotalLines(const std::string& file_path);
        [[maybe_unused]] static std::vector<std::string> splitbychar(std::string line);
        [[maybe_unused]] static std::string getFileName(std::string pthIn);
        [[maybe_unused]] static std::string CheckEnd(std::string path);
        [[maybe_unused]] static std::vector<std::string> splitLine(const std::string& s, char delimiter);
        [[maybe_unused]] static std::string addWaterSerialNumber(const std::string& path);

        [[maybe_unused]] static bool isFolder(const std::string &path);
        [[maybe_unused]] static bool isNumber(const std::string &s);
        
    private:
        struct digit_sort
        {
            inline bool operator() (const std::string& struct1, const std::string& struct2)
            {
                auto getFileName = [](const std::string &path) ->std::string {
                    // get filename
                    auto lastDot = path.find_last_of('.');
                    auto lastRightSlash = path.find_last_of('/');
                    if(lastRightSlash == std::string::npos && lastDot == std::string::npos) // input is a name (100)
                        return path;
                    if(lastRightSlash == std::string::npos && lastDot != std::string::npos) // input is a name with type (100.cpp)
                        return path.substr(0, lastDot);
                    if(lastRightSlash != std::string::npos && lastDot == std::string::npos) // input is a path without type (something/100)
                        return path.substr(lastRightSlash+1, path.length());
                    if(lastDot == path.front() && lastRightSlash == path.front()+1) // input is ./100.cpp
                        return path.substr(lastRightSlash+1, path.length());

                    return path.substr(lastRightSlash+1, lastRightSlash-lastDot-1);
                };
                auto name1 = std::stoi(getFileName(struct1));
                auto name2 = std::stoi(getFileName(struct2));
                return (name1 < name2);
            }
        };
    };
    
} //End of namespace Tools
#endif /* Tools_hpp */
