#include <iostream>
#include <memory>
#include <vector>
#include <tinyply.h>

int main()
{

    std::cout << "Hello " << std::endl;

    return 0;
}


// 导入点云
void load_cloud(std::string &path) 
{
    std::unique_ptr <std::istream> file_stream; // auto dim_pts = 3;
    std::vector <uint8_t> byte_buffer; // try to load with binary

    // 读取数据
    std::shared_ptr <tinyply::PlyData> point_data, label_data, normal_data, rgb_data, radius_data;
    bool bGoodRadius=true;
    // 读取坐标xyz
    try 
    {
        std::vector <std::string> propertyKeys = {"x", "y", "z"};
        point_data = file.request_properties_from_element("vertex", propertyKeys);
    } 
    catch (const std::exception &e) { 
        std::cerr << "tinyply exception: " << e.what() << std::endl; 
    }

    // 读取
    try {
        label_data = file.request_properties_from_element("vertex", {"label"});
    } 
    catch (const std::exception &e) { 
        std::cerr << "tinyply exception: " << e.what() << std::endl; 
    }

    // 读取法向nx ny nz
    try {
        std::vector <std::string> propertyKeys = {"nx", "ny", "nz"};
        normal_data = file.request_properties_from_element("vertex", propertyKeys);
    } 
    catch (const std::exception &e) { 
        std::cerr << "tinyply exception: " << e.what() << std::endl; 
    }

    // 读取rgb
    try {
        std::vector <std::string> propertyKeys = {"red", "green", "blue"};
        rgb_data = file.request_properties_from_element("vertex", propertyKeys);
    } 
    catch (const std::exception &e) { 
        std::cerr << "tinyply exception: " << e.what() << std::endl; 
    }

    try {
        radius_data = file.request_properties_from_element("vertex", {"radius"});
    } catch (const std::exception &e) {
        bGoodRadius = false;
        std::cerr << "tinyply exception: " << e.what() << std::endl; 
    }

    file.read(*file_stream);

    struct float3{ float x,y,z; };
    std::vector<float3> points;
    if (!point_data) return {};
    copyFromBuffer( point_data.get(), &points );

    std::vector<ushort> labels;
    copyFromBuffer(label_data.get(), &labels);

    std::vector<float3> normals;
    copyFromBuffer(normal_data.get(), &normals);

    struct uchar3{
        unsigned char x,y,z;
    };
    std::vector<uchar3> colors;
    copyFromBuffer(rgb_data.get(), &colors);

    std::vector<float> radius;
    if(bGoodRadius)copyFromBuffer(radius_data.get(), &radius);

    std::vector< std::shared_ptr<Surfel> > surfels(points.size());
    Eigen::Vector3f centroid = {0.f, 0.f, 0.f};
    for(size_t i=0; i<points.size(); ++i )
    {
        surfels[i].reset(new Surfel());
        auto& surfel = surfels[i];

        // position
        if (std::isnan(points[i].x) || std::isnan(points[i].y) || std::isnan(points[i].z) || std::isinf(points[i].x) || std::isinf(points[i].y) || std::isinf(points[i].z)) 
        {
            printf("has nan\n");
            surfel->pos.setZero();
            surfel->is_valid = false;
            surfel->is_stable = false;
        } 
        else 
        {
            surfel->pos.x() = points[i].x * 1e3;
            surfel->pos.y() = points[i].y * 1e3;
            surfel->pos.z() = points[i].z * 1e3;
            centroid += surfel->pos;
        }

        // color
        if(colors.size() == points.size())
        {
            surfel->color[2] = colors[i].x;
            surfel->color[1] = colors[i].y;
            surfel->color[0] = colors[i].z;
        }

        // normal
        if(normals.size() == points.size()) {
            surfel->normal.x() = normals[i].x;
            surfel->normal.y() = normals[i].y;
            surfel->normal.z() = normals[i].z;
        }

        // label
        if(labels.size() == points.size()){
            surfel->label = labels[i];
        }
        surfel->label_confidence = 100/*qulity[i]*/;

        // radius
        if(radius.size() == points.size()) 
        {
            surfel->radius = radius[i];
        } 
        else
        {
            surfel->radius = 10.f;
        }

        surfel->is_valid = true;
        surfel->is_stable = true;
    }
    // std::cout << centroid.transpose() << "\n";
    // centroid /= points.size();
    // for(size_t i=0;i<points.size();++i ){
    //     surfels[i]->pos -= centroid;
    // }

    return surfels;
}