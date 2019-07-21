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

float degree_to_rad(int deg){
  return (3.14/180)*deg;
  
  }

ros::NodeHandle  nh;




sensor_msgs::JointState joint_state;

ros::Publisher joint_pub("joint_states", &joint_state);

Servo wrist,elbow,shoulder;
void setup(){
 
    Serial.begin(115200);

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  shoulder.attach(9);
  elbow.attach(10);
  wrist.attach(11);
  
  
  shoulder.write(90);
  elbow.write(90);
  wrist.write(90);
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
   int readshoulder=analogRead(A1);
   int readelbow=analogRead(A2);
   int readwrist=analogRead(A3);

   int sd = map(readshoulder,117,432,0,180);
   Serial.println(sd);
   int ed = map(readelbow,114,430,0,180);
   Serial.println(ed);
   int wd = map(readwrist,116,444,0,180);
   Serial.println(wd);

   float shoulder_angle = degree_to_rad(sd);
   float elbow_angle=degree_to_rad(ed);
   float wrist_angle=degree_to_rad(wd);
   
   
    joint_state.position[0] = shoulder_angle-1.57;
    joint_state.position[1] = elbow_angle-1.57;
    joint_state.position[2] = wrist_angle-1.57;
    
  
  
  
  
  
    joint_pub.publish(&joint_state);
    nh.spinOnce();
}
