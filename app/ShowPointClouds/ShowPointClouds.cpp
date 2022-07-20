#include <iostream>
#include <vector>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>

void ShowPCLPointsXYZRGB(pcl::PointCloud<pcl::PointXYZRGB>::Ptr color_cloud)
{
	cout << "point size:" << color_cloud->size() << endl;
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer1(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer1->addPointCloud<pcl::PointXYZRGB>(color_cloud);
	viewer1->setBackgroundColor(0, 0, 0); // 设置点云大小
	viewer1->addCoordinateSystem(0);
	while (!viewer1->wasStopped())
	{
		viewer1->spinOnce(100);
	}
}

#define Random(x) (rand() % x)
void ShowClusterPointsXYZRGB( std::vector<pcl::PointCloud<pcl::PointXYZ>>& cloud_clusters) 
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointXYZRBG(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointXYZRGB point;
	cout << "End show particle size:" << cloud_clusters.size() << endl;
	for (int i = 0; i < cloud_clusters.size(); i++) {
		int color_B = Random(255);
		int color_G = Random(255);
		int color_R = Random(255);
		for (int j = 0; j < cloud_clusters[i].size(); j++) {
			point.x = cloud_clusters[i].points[j].x;
			point.y = cloud_clusters[i].points[j].y;
			point.z = cloud_clusters[i].points[j].z;
			point.r = color_R;
			point.g = color_G;
			point.b = color_B;
			pointXYZRBG->push_back(point);
		}
	}
	ShowPCLPointsXYZRGB(pointXYZRBG);
}

int main()
{
    // pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointXYZRGB(new pcl::PointCloud<pcl::PointXYZRGB>);
    // pcl::PointXYZRGB point;

}