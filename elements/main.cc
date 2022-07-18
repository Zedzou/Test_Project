#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osg/LineWidth>
#include <osgDB/ReadFile>

#include "CoordinateAxis.h"
#include "Models.h"
#include "Light.h"
#include "Camera.h"
#include "dataLoader/dataLoader.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

int main(int argc, char **argv)
{
	// 主节点
	osg::ref_ptr<osg::Group> root = new osg::Group;
	CoordinateAxis* DrawCoordinate = new CoordinateAxis();
	LoadModel* loadModel = new LoadModel();
	Light* light = new Light();

	// 导入相机姿态
	dataLoader* datasetLoader = new dataLoader();
	std::map<std::string, Eigen::Matrix4f> poseMap = datasetLoader->poseMap;
	for(auto &s:poseMap)
	{
		Eigen::Matrix4f m_poseTransform;
		m_poseTransform <<  0.0406125, -0.999172,  0.00263255, -940.349,
							0.999174,   0.0406159, 0.0012665,   1290.38,
							-0.00137238,  0.00257894, 0.999996, -154.145,
							0,           0,           0,           1;

		Eigen::Matrix4f transformer = s.second;
		transformer.block<3, 1>(0, 3) *= 1000.0f;
		transformer = m_poseTransform * transformer;
		transformer.block<3, 1>(0, 3) /= 1000.0f;

		CameraDraw* cameraDraw = new CameraDraw(transformer);
		cameraDraw->addSubGroup(root);
	}

	DrawCoordinate->addSubGroup(root);
	loadModel->addSubGroup(root);
	light->addSubGroup(root);

	// viewer
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	viewer->addEventHandler(new osgViewer::WindowSizeHandler());
	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

}