#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif
#include <Servo.h> 
#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/ChannelFloat32.h>
#include <sensor_msgs/JointState.h>


ros::NodeHandle  nh;




sensor_msgs::JointState joint_state;

ros::Publisher joint_pub("joint_states", &joint_state);

Servo wrist,elbow,shoulder;
void setup(){
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  shoulder.attach(9);
  elbow.attach(10);
  wrist.attach(11);
  
  
  shoulder.write(0);
  elbow.write(0);
  wrist.write(0);
 // char robot_id = "/arm_mesh";
  char *joint_names[] ={"link1_link2","link2_link3","link3_link4"}; 
  float pos[3]; /// stores arduino time
  float vel[3];
  float eff[3];
  joint_state.name_length = 3;
  joint_state.position_length = 3;
  joint_state.name = joint_names;
  joint_state.header.frame_id = "link1";
  
  
  

   
    joint_state.position = pos;
    
  
  nh.advertise(joint_pub);
  
  
}

void loop(){
   joint_state.header.stamp = nh.now();
    joint_state.position[0] = 0;
    joint_state.position[1] = 0;
    joint_state.position[2] = 0;
    //joint_state.header.stamp = ros::Time::now();
    joint_pub.publish(&joint_state);
    nh.spinOnce();
}
