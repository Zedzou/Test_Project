#include <zip.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include "stdio.h"

int main()
{
    const char *FilePath = "/media/zed/46BCAB97BCAB8053/ScanNet/ScanNet/scans/scene0002_00/scene0002_00_2d-instance.zip";
    std::string str_RootPath = "/media/zed/46BCAB97BCAB8053/ScanNet/ScanNet/scans/scene0002_00/";
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
            printf("\n Name: [%s], ", File_ZipStruct.name);
            printf("Size: [%llu], ",(long long unsigned int) File_ZipStruct.size);
            printf("mtime: [%u] \n", (unsigned int)File_ZipStruct.mtime);

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

    return 0;
   
}