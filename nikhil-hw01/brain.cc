
#include <iostream>
#include <math.h>

#include "robot.hh"

using std::cout;
using std::endl;

const double goal_x = 20.0;
const double goal_y = 0.0;
bool done = false;

// Tweakable Parameters
const double normal_vel = 6;
const double turn_vel_scaling_factor = 0.5;

const double obstacle_avoidance_vel = 3;
const double obstacle_avoidance_turn = 0.7;

const double obstacle_detection_range = 2;
const double obstacle_detection_angle = 0.8;

void
callback(Robot* robot)
{

    double angle_to_goal = atan2(goal_y-robot->pos_y, goal_x-robot->pos_x);
    double turn_speed = robot->pos_t - angle_to_goal;

    cout << endl;
    cout << "Robot Position: (" << robot->pos_x << "," << robot->pos_y <<")" << endl;
    cout << "Robot Heading: " << robot->pos_t << endl;
    
    double dx = goal_x - robot->pos_x;
    double dy = goal_y - robot->pos_y;
    if (abs(dx) < 0.75 && abs(dy) < 0.75) {
        cout << "we win!" << endl;
        robot->set_vel(0.0);
        robot->set_turn(0.0);
        robot->done();
        return;
    }

    bool turn = false;

    for (LaserHit hit : robot->hits) {
        if (hit.range < obstacle_detection_range && hit.range > 0.3) {
            if (abs(hit.angle) < obstacle_detection_angle) {
                cout << hit.angle << " " << hit.range << endl;
                turn = true;
            }
        }
    }

    if (turn) {
        cout << "Obstacle detected!" << endl;
        robot->set_vel(obstacle_avoidance_vel);
        robot->set_turn(obstacle_avoidance_turn);
    }
    else {
        robot->set_vel(normal_vel);
        robot->set_turn(turn_speed*turn_vel_scaling_factor);
    }
}

int
main(int argc, char* argv[])
{
    cout << "making robot" << endl;
    Robot robot(argc, argv, callback);
    robot.do_stuff();

    return 0;
}
