#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>

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

void ShowPCLPointsXYZRGB(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr color_cloud)
{
	cout << "point size:" << color_cloud->size() << endl;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer1(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer1->addPointCloud<pcl::PointXYZRGBNormal>(color_cloud);
	viewer1->setBackgroundColor(0, 0, 0); // 设置点云大小
	viewer1->addCoordinateSystem(0);
	while (!viewer1->wasStopped()){
		viewer1->spinOnce(100);
	}
}


int main (int argc, char** argv)
{
    // read ply data
    const std::string PlyDataFile = "/home/zed/Project/pointcloud_Graph/data_online_panoptic_3d/frame_000001.pointcloud.ply";
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr CloudData(new pcl::PointCloud<pcl::PointXYZRGBNormal>);
    if(pcl::io::loadPLYFile(PlyDataFile, *CloudData)){
        PCL_ERROR("Cant't read file%s", PlyDataFile);
        return -1;
    }
    else{
        std::cout << "load the pointcloud: " << PlyDataFile << "successful " << std::endl;
        std::cout << "the size of pointcloud: " << CloudData->size() << std::endl;
    }

    std::vector<std::string> FilterFieldName;
    FilterFieldName.push_back("x");
    FilterFieldName.push_back("y");
    FilterFieldName.push_back("z");
    FilterFieldName.push_back("xy");
    FilterFieldName.push_back("xz");
    FilterFieldName.push_back("yz");
    // for (int i=0; i<)
    

    // 直通滤波
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGBNormal>);
    pcl::PassThrough<pcl::PointXYZRGBNormal> pass;
    pass.setInputCloud (CloudData);
    pass.setFilterFieldName ("xz");
    pass.setFilterLimits (0.0, 10.0);
    pass.filter (*cloud_filtered);

    ShowPCLPointsXYZRGB(cloud_filtered);

    // // save .ply data
    // const std::string outout_folder = "../data";
    // const std::string output_name = "SaveTestPly.ply";
    // SaveSurfelsToPLY(outout_folder, output_name, CloudData, false);

    return 0;
}