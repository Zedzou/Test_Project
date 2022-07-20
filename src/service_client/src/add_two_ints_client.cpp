#include "ros/ros.h"
#include "service_client/AddTwoInts.h"
#include <cstdlib>

int main(int argc, char **argv)
{
    ros::init (argc, argv, "add_two_ints_client");
    if (argc!=3){
        ROS_INFO("usage: add_two_ints_client X Y");
        return 1;
    }

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<service_client::AddTwoInts>("add_two_ints");

    service_client::AddTwoInts srv;
    srv.request.a = atoi(argv[1]);
    srv.request.b = atoi(argv[2]);
    if (client.call(srv)){
        ROS_INFO("Sum: %1d", (long int)srv.response.sum);
    }else{
        ROS_ERROR("Failed to call service add_two_ints");
        return 1;
    }

    return 0;
}