#include <ros/ros.h>

#include <trajectory_msgs/JointTrajectoryPoint.h>
#define nJoints_ 7
/*
trajectory_msgs/JointTrajectoryPoint 
float64[] positions
float64[] velocities
float64[] accelerations
float64[] effort
duration time_from_start
*/

/*
TODO add all sine values to config file
TODO get number of joints nJoints_ from parameter server
*/
trajectory_msgs::JointTrajectoryPoint traj;

int main(int argc,char* argv[])
{
    ros::init(argc, argv, "joint_sines");
    ros::NodeHandle node;

    ros::Publisher pub_joint_ref=node.advertise<trajectory_msgs::JointTrajectoryPoint>("controller/command",1);

    //TODO make this controller independent
    // std::vector<std::string> joint_names;
    // if(!node.getParam("/computed_torque_controller/joints",joint_names))
    // {
    //     ROS_ERROR("No 'joints' in controller. (namespace: %s)", node.getNamespace().c_str());
	// 	return false;
	// }
    //int nJoints_ = joint_names.size();

    std::cout<<"nJoints: "<<nJoints_<<std::endl;
    std::cout<<"NameSpace: "<<node.getNamespace().c_str()<<std::endl;

    traj.positions.resize(nJoints_);
    traj.velocities.resize(nJoints_);
    traj.accelerations.resize(nJoints_);
    
    for(int i=0;i<nJoints_;i++)
    {
        traj.positions[i]=0.0;
        traj.velocities[i]=0.0;
        traj.accelerations[i]=0.0;
    }
    
    ros::Rate loop(100);
    while(ros::ok())
    {
        for(int i=0;i<nJoints_;i++)
        {
            traj.positions[i]=0.5*std::sin(ros::Time::now().toSec());
        }
        pub_joint_ref.publish(traj);

        ros::spinOnce();
        if(!loop.sleep()) ROS_WARN("Missed deadline!");
    }

    pub_joint_ref.shutdown();

    return 0;
}