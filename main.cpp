#include <zip.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include "stdio.h"
#include "PathTool.hpp"

// 获取所有扫描的文件名
std::vector<std::string> GetAllScanName(const std::string Path)
{
    std::vector<std::string> AllScansName = tools::PathTool::get_files_in_folder(Path);
    return AllScansName;
}

// 解压缩文件到当前路径
bool unzipFile(const char* FilePath)
{
    std::string str_RootPath = tools::PathTool::find_parent_folder(FilePath);
    std::string FileName = tools::PathTool::find_parent_folder_name(FilePath);
    char d = '.';
    std::vector<std::string> n = tools::PathTool::splitLine(FileName, d);
    str_RootPath = str_RootPath + "/" + n[0] + "/";
    if(!tools::PathTool::checkfolderexist(str_RootPath)){
        tools::PathTool::create_folder(str_RootPath);
    }

    printf("File path : %s\n",FilePath);
    int err = 0;
    struct zip_stat File_ZipStruct; 

    // open the zip file
    zip *z = zip_open(FilePath, 0, &err);
    if(z==NULL){
        printf("file open failed");
        return 0;
     }
     
    printf("Unzipping started .....\n");
    for (int i = 0; i < zip_get_num_entries(z, 0); i++) 
    {
        if (zip_stat_index(z, i, 0, &File_ZipStruct) == 0) 
        {
            //printing the file information
            int len = strlen(File_ZipStruct.name);
            // printf("\n Name: [%s], ", File_ZipStruct.name);
            // printf("Size: [%llu], ",(long long unsigned int) File_ZipStruct.size);
            // printf("mtime: [%u] \n", (unsigned int)File_ZipStruct.mtime);

            if(File_ZipStruct.name[len-1]=='/')
            {
                std::string str_Namepath = File_ZipStruct.name;
                std::string str_Path = str_RootPath + str_Namepath;
                mkdir(str_Path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // creating the folder when the file type is folder
            }
            else
            {
                char contents[1025];
                zip_file *f = zip_fopen(z, File_ZipStruct.name, 0);  
                int readByte = 0;
                std::string str_Namepath = File_ZipStruct.name;
                std::string str_Path_2 = str_RootPath + str_Namepath;
                FILE * DestFile = fopen(str_Path_2.c_str(), "w");
                while(readByte < File_ZipStruct.size)
                {
                    int dataread = zip_fread(f, contents, 1024);
                    fwrite(contents, sizeof(char), dataread, DestFile);
                    readByte += 1024;
                }
                zip_fclose(f);  //close the source handle
                fclose(DestFile); //close destination file handle
            }
        }
    }
    printf("Unzipping Completed .....\n");
    zip_close(z); //closing the file handle
}

int main(int argc, char **argv){
    // if (argc<0){
    //     throw std::runtime_error("please input file path!");
    // }

    const std::string Scan3RPath = "/home/zed/Project/dataset/3RScan";
    std::vector<std::string> AllScanName = GetAllScanName(Scan3RPath);
    for (int i=0; i<AllScanName.size(); ++i){
        std::string ZipFileName = Scan3RPath + "/" + AllScanName[i] + "/" + "sequence.zip";
        const char *FilePath = ZipFileName.data();
        unzipFile(FilePath);
    }
    return 0;


    // const std::string name = "/home/zed/Project/Projects/3DSceneGraph/3RScan/data/3RScan.v2.zip";
    // char d = '.';
    // std::vector<std::string> t = tools::PathTool::splitLine(name, d);
    // for (int i=0; i<t.size(); ++i){
    //     std::cout << t[i] << std::endl;
    // }

    // return 0;
}