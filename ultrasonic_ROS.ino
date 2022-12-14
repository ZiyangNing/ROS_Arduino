#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <HCSR04.h>
//https://github.com/gamegine/HCSR04-ultrasonic-sensor-lib
#define USE_USBCON

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);

int trigPin = 7;  //trig
int echoPin = 8;  //echo
HCSR04 hc(trigPin, echoPin);  //initialisation class HCSR04 (trig pin , echo pin)
char frameid[] = "/ultrasound";


void setup() {
  nh.initNode();
  //Serial.begin(57600);    //this don't matter
  nh.advertise(pub_range);
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.5236;     //radian (according to data sheet)
  range_msg.min_range = 0.02;           //meters
  range_msg.max_range = 4;              //meters
}

void loop()
{
    range_msg.range = hc.dist()/100;  //hc.dist returns cm convert to m
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
    nh.spinOnce();
    delay(100);
}