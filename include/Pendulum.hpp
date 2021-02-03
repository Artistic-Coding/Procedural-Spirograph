#ifndef __PENDULUM__
#define __PENDULUM__
#include "cinder/gl/gl.h"

using namespace ci;

#define PI 3.14159265

/***
 * Accounts for a current point
 */
class Pendulum_Point {
    public:
        vec2 pos;
        vec2 old_end;
        vec2 new_end;
        float speed;
        float len;
        float angle;
        /***
         * A point in the pendulum
         *
         * @param position Its current position
         * @param rotation_speed The points rotational speed
         * @param length The points line length
         */
        Pendulum_Point(vec2 position, float rotation_speed, float length);
        /**
         * Update its current positions
         */
        void update();
};

class Pendulum {
    public:
        std::vector<Pendulum_Point> points;
        /**
         * Initialize a linear pendulum
         */
        Pendulum();
        /**
         * Initialize a linear pendulum
         *
         * @param position Position of the center
         * @param rotation_speed Rotation of the root pendulum
         * @param length Length of initial pendulum
         */
        Pendulum(vec2 position, float rotation_speed, float length);
        /**
         * Non constructor type initializer
         *
         * @param position Position of the center
         * @param rotation_speed Rotation of the root pendulum
         * @param length Length of initial pendulum
         */
        void init(vec2 position, float rotation_speed, float length);
        /**
         * Add a new pendulum line, will extend the last added point
         *
         * @param rotation_speed Rotation of said pendulum
         * @param length Length of said pendulum
         */
        void push_back(float rotation_speed, float length);
        /**
         * Update all point positions
         *
         * @return Returns an array of arrays [old_pos, new_pos]
         */
        std::vector<std::vector<vec2>> get_next(); //[[old, new],[old, new]]
};
#endif