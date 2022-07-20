#include <iostream>
#include <fstream>
#include <sstream>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>

void SaveSurfelsToPLY(const std::string &output_folder,  const std::string &output_name,  pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudData, bool binary) 
{
    // 计算点的数量
    size_t counter = CloudData->size();

    // 保存文件夹
    std::fstream file;
    if(!binary){
        file.open(output_folder + "/" + output_name, std::ios::out);
    }
    else{
        file.open(output_folder + "/" + output_name, std::ios::out | std::ios::binary);
    }
    assert(file.is_open());

    file << "ply\n";
    if(!binary){
        file << "format ascii 1.0\n";
    }
    else{
        file << "format binary_little_endian 1.0\n";
    }
        
    file << "element vertex " + std::to_string(counter) + "\n"
                                                          "property float x\n"
                                                          "property float y\n"
                                                          "property float z\n"
                                                          "end_header\n";

    for (int i=0; i<CloudData->size(); ++i)
    {
        // pos
        if(!binary){
            file << CloudData->points[i].x << " ";
            file << CloudData->points[i].y << " ";
            file << CloudData->points[i].z << "\n";
        }
    }

    file.close();
}

int main (int argc, char** argv)
{
    // read ply data
    const std::string PlyDataFile = "/home/zed/Project/pointcloud_Graph/data/frame_000000/frame_000000.pointcloud.ply";
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr CloudData(new pcl::PointCloud<pcl::PointXYZRGB>);
    if(pcl::io::loadPLYFile(PlyDataFile, *CloudData)){
        PCL_ERROR("Cant't read file%s", PlyDataFile);
        return -1;
    }
    else{
        std::cout << "load the pointcloud: " << PlyDataFile << "successful " << std::endl;
        std::cout << "the size of pointcloud: " << CloudData->size() << std::endl;
    }

    // save .ply data
    const std::string outout_folder = "../data";
    const std::string output_name = "SaveTestPly.ply";
    SaveSurfelsToPLY(outout_folder, output_name, CloudData, false);

    return 0;
}