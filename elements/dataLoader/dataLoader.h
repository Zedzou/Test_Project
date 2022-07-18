#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <Eigen/Core>
#include <iomanip>


class dataLoader
{
    public:
        dataLoader();
        ~dataLoader();

        std::vector<std::string> rgb_path;
        std::vector<std::string> depth_path;
        std::map<std::string, Eigen::Matrix4f> poseMap; // 位姿字典

    private:
        void readPose(); // 读取位姿
        void readRGBpath(); // 读取RGB路径
        void readDepthpath(); // 读取深度图路径

        // 数据定义
        std::string dataPath = "/home/zed/Desktop/0a4b8ef6-a83a-21f2-8672-dce34dd0d7ca/sequence/";
        std::string prefix = "frame-";
        std::string rgb_suffix = ".color.jpg";
        std::string depth_suffix = ".depth.pgm";
        std::string pose_suffix = ".pose.txt";
        const int frameNum = 50;
};

