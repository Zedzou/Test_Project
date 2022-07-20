#include <memory>
#include <vector>
#include <tinyply.h>
#include <cmath>
#include "Vector.h"
#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cassert>

#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>

// // 内存复制
// template<typename T>
// void copyFromBuffer(tinyply::PlyData *buffer, std::vector<T> *container);

// // 打印.ply文件的header
// void print_headers(tinyply::PlyFile &file)
// {
//     for (const auto &e : file.get_elements()) 
//     {
//         std::cout << "\t[ply_header] element: " << e.name << " (" << e.size << ")" << std::endl;
//         for (const auto &p : e.properties) {
//             std::cout << "\t[ply_header] \tproperty: " << p.name << " (type=" << tinyply::PropertyTable[p.propertyType].str << ")";
//             if (p.isList) std::cout << " (list_type=" << tinyply::PropertyTable[p.listType].str << ")";
//             std::cout << std::endl;
//         }
//     }
// }

// // 导入点云
// bool load_cloud(const std::string &path) 
// {
//     std::unique_ptr <std::istream> file_stream; // auto dim_pts = 3;
//     std::vector <uint8_t> byte_buffer; // try to load with binary

//     std::shared_ptr <tinyply::PlyData> point_data, label_data, normal_data, rgb_data, radius_data;
//     bool bGoodRadius=true;   
//     tinyply::PlyFile file;
//     file.parse_header(*file_stream);
//     print_headers(file);

//     // 读取坐标xyz
//     try{
//         std::vector <std::string> propertyKeys = {"x", "y", "z"};
//         point_data = file.request_properties_from_element("vertex", propertyKeys);
//     } 
//     catch(const std::exception &e){ 
//         std::cerr << "tinyply exception: " << e.what() << std::endl; 
//     }

//     // 读取标签
//     try{
//         label_data = file.request_properties_from_element("vertex", {"label"});
//     } 
//     catch(const std::exception &e){ 
//         std::cerr << "tinyply exception: " << e.what() << std::endl; 
//     }

//     // 读取法向nx ny nz
//     try {
//         std::vector <std::string> propertyKeys = {"nx", "ny", "nz"};
//         normal_data = file.request_properties_from_element("vertex", propertyKeys);
//     } 
//     catch (const std::exception &e){ 
//         std::cerr << "tinyply exception: " << e.what() << std::endl; 
//     }

    // // 读取rgb
    // try {
    //     std::vector <std::string> propertyKeys = {"red", "green", "blue"};
    //     rgb_data = file.request_properties_from_element("vertex", propertyKeys);
    // } 
    // catch(const std::exception &e){ 
    //     std::cerr << "tinyply exception: " << e.what() << std::endl; 
    // }
    // file.read(*file_stream);

    // struct float3{ float x, y, z; };
    // std::vector<float3> points;
    // if (!point_data){
    //     return false;
    // }
    // copyFromBuffer(point_data.get(), &points );

    // std::vector<ushort> labels;
    // copyFromBuffer(label_data.get(), &labels);

    // std::vector<float3> normals;
    // copyFromBuffer(normal_data.get(), &normals);

    // struct uchar3{unsigned char x,y,z;};
    // std::vector<uchar3> colors;
    // copyFromBuffer(rgb_data.get(), &colors);

    // // 输出保存点云
    // const std::string filename = "./1.ply";
    // std::ofstream stream(filename.c_str());
    // if (!stream) {
    //     return false;
    // }

    // size_t num_points = points.size();
    // stream << "ply" << std::endl;
    // stream << "format ascii 1.0" << std::endl;
    // stream << "element vertex " << num_points << std::endl;
    // stream << "property float x" << std::endl;
    // stream << "property float y" << std::endl;
    // stream << "property float z" << std::endl;

    // stream << "property float nx" << std::endl;
    // stream << "property float ny" << std::endl;
    // stream << "property float nz" << std::endl;

    // stream << "property uchar red" << std::endl;
    // stream << "property uchar green" << std::endl;
    // stream << "property uchar blue" << std::endl;
    // stream << "property uchar alpha" << std::endl;

    // // instance ID
    // stream << "property ushort label" << std::endl;
    // stream << "end_header" << std::endl;
        
    // // 计算标签
    // std::map<ORUtils::Vector3<int>, int> InstanceIDMap;
    // InstanceIDMap.clear();        

    // // x y z r g b a
    // size_t vert_idx = 0;
    // for (const float3& vert : points) 
    // {
    //     // 位置坐标
    //     stream << vert.x << " " << vert.y << " " << vert.z;
    
    //     // 发向坐标
    //     const float3& normal = points[vert_idx];
    //     stream << " " << normal.x << " " << normal.y << " " << normal.z;

    //     // RGB
    //     const uchar3& color = colors[vert_idx];
    //     int r = static_cast<int>(color.x);
    //     int g = static_cast<int>(color.y);
    //     int b = static_cast<int>(color.z);
    //     stream << " " << r << " " << g << " " << b;

    //     // instance ID
    //     ORUtils::Vector3<int> CloudColor_(r, g, b);
    //     auto iter = InstanceIDMap.find(CloudColor_);
    //     if ( iter == InstanceIDMap.end() )
    //     { 
    //         stream << " " << InstanceIDMap.size();
    //         InstanceIDMap.insert(std::pair<ORUtils::Vector3<int>, int>(CloudColor_, (InstanceIDMap.size())));
    //     } 
    //     else
    //     { 
    //         int InstanceIDColor = InstanceIDMap.at(CloudColor_);
    //         stream << " " << InstanceIDColor;
    //     }
    //     stream << std::endl;
    //     vert_idx++;
    // }
    
// }

bool OutPointCloudPLY(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr CloudData, const std::string &filename)
{
    std::ofstream stream(filename.c_str());
    if (!stream) {
        return false;
    }

    size_t num_points = CloudData->size();
    stream << "ply" << std::endl;
    stream << "format ascii 1.0" << std::endl;
    stream << "element vertex " << num_points << std::endl;
    stream << "property float x" << std::endl;
    stream << "property float y" << std::endl;
    stream << "property float z" << std::endl;

    stream << "property float nx" << std::endl;
    stream << "property float ny" << std::endl;
    stream << "property float nz" << std::endl;

    stream << "property uchar red" << std::endl;
    stream << "property uchar green" << std::endl;
    stream << "property uchar blue" << std::endl;

    // instance ID
    stream << "property ushort label" << std::endl;
    stream << "end_header" << std::endl;
        
    // 计算标签
    std::map<ORUtils::Vector3<int>, int> InstanceIDMap;
    InstanceIDMap.clear();        

    // x y z r g b a
    size_t vert_idx = 0;
    for (int i=0; i<CloudData->size(); ++i) 
    {
        // 位置坐标
        stream << CloudData->points.at(i).x << " " << CloudData->points.at(i).y << " " << CloudData->points.at(i).z;
    
        // 发向坐标
        stream << " " <<CloudData->points.at(i).normal_x << " " << CloudData->points.at(i).normal_y << " " << CloudData->points.at(i).normal_z;

        // RGB
        int r = CloudData->points.at(i).r;
        int g = CloudData->points.at(i).g;
        int b = CloudData->points.at(i).b;
        stream << " " << r << " " << g << " " << b;

        // instance ID
        ORUtils::Vector3<int> CloudColor_(r, g, b);
        auto iter = InstanceIDMap.find(CloudColor_);
        if ( iter == InstanceIDMap.end() )
        { 
            stream << " " << InstanceIDMap.size();
            InstanceIDMap.insert(std::pair<ORUtils::Vector3<int>, int>(CloudColor_, (InstanceIDMap.size())));
        } 
        else
        { 
            int InstanceIDColor = InstanceIDMap.at(CloudColor_);
            stream << " " << InstanceIDColor;
        }
        stream << std::endl;
        vert_idx++;
    }
}

int main()
{
    // read ply data
    const std::string PlyDataFile = "/home/zed/Desktop/test/radius_4.0/frame_000009 - Cloud.ply";
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr CloudData(new pcl::PointCloud<pcl::PointXYZRGBNormal>);
    if(pcl::io::loadPLYFile(PlyDataFile, *CloudData)){
        PCL_ERROR("Cant't read file%s", PlyDataFile);
        return -1;
    }
    else{
        std::cout << "load the pointcloud: " << PlyDataFile << "successful " << std::endl;
        std::cout << "the size of pointcloud: " << CloudData->size() << std::endl;
    }

    // 计算实例ID并保存为.ply点云
    const std::string filename = "/home/zed/Desktop/test/radius_4.0/add_instanceID/frame_000009.pointcloud.ply";
    OutPointCloudPLY(CloudData, filename);

    return 0;
}

// template<typename T>
// void copyFromBuffer(tinyply::PlyData *buffer, std::vector<T> *container) 
// {
//     if (std::is_same<T, int8_t>::value) assert(buffer->t == tinyply::Type::INT8);
//     if (std::is_same<T, uint8_t>::value) assert(buffer->t == tinyply::Type::UINT8);
//     if (std::is_same<T, int16_t>::value) assert(buffer->t == tinyply::Type::INT16);
//     if (std::is_same<T, uint16_t>::value) assert(buffer->t == tinyply::Type::UINT16);
//     if (std::is_same<T, int32_t>::value) assert(buffer->t == tinyply::Type::INT32);
//     if (std::is_same<T, uint32_t>::value) assert(buffer->t == tinyply::Type::UINT32);
//     if (std::is_same<T, float>::value) {
//         assert(buffer->t == tinyply::Type::FLOAT32);
//     }
//     if (std::is_same<T, double>::value) assert(buffer->t == tinyply::Type::FLOAT64);
//     container->resize(buffer->count);
//     const size_t numVerticesBytes = buffer->buffer.size_bytes();
//     std::memcpy(container->data(), buffer->buffer.get(), numVerticesBytes);
// }