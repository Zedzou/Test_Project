#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include <pcl/io/ply_io.h>
#include <pcl/point_types.h>
 
int main ()
{
    // pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);


    // // Fill in the cloud data
    // pcl::PCDReader reader;
    // // Replace the path below with the path where you saved your file
    // reader.read<pcl::PointXYZ> ("table_scene_lms400.pcd", *cloud);
    // std::cerr << "Cloud before filtering: " << std::endl;
    // std::cerr << *cloud << std::endl;


    // read ply data
    const std::string PlyDataFile = "/home/zed/Project/pointcloud_Graph/data/frame_000000/frame_000000.pointcloud.ply";
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    if(pcl::io::loadPLYFile(PlyDataFile, *cloud)){
        PCL_ERROR("Cant't read file%s", PlyDataFile);
        return -1;
    }
    else{
        std::cout << "load the pointcloud: " << PlyDataFile << "successful " << std::endl;
        std::cout << "the size of pointcloud: " << cloud->size() << std::endl;
    }

    
    // Create the filtering object
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
    sor.setInputCloud (cloud);
    // sor.setMeanK (50);
    // sor.setStddevMulThresh (1.0);
    // sor.filter (*cloud_filtered);

    // std::cerr << "Cloud after filtering: " << std::endl;
    // std::cerr << *cloud_filtered << std::endl;

    // pcl::PCDWriter writer;
    // writer.write<pcl::PointXYZ> ("table_scene_lms400_inliers.pcd", *cloud_filtered, false);

    // sor.setNegative (true);
    // sor.filter (*cloud_filtered);
    // writer.write<pcl::PointXYZ> ("table_scene_lms400_outliers.pcd", *cloud_filtered, false);

    return (0);
}