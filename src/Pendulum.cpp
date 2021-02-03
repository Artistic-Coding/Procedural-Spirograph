#include "Pendulum.hpp"

Pendulum_Point::Pendulum_Point(vec2 position, float rotation_speed, float length) {
    pos = position;
    speed = rotation_speed;
    len = length;
    angle = 0;

    //Start at 0
    float angle_rads = len*PI/180;
    new_end = vec2(pos.x + cos(angle_rads) * len, pos.y + sin(angle_rads) * len);
    old_end = new_end;
}

void Pendulum_Point::update() {
    angle += speed;
    float angle_rads = angle*PI/180;
    old_end = new_end;
    new_end = vec2(pos.x + cos(angle_rads) * len, pos.y + sin(angle_rads) * len);
}

Pendulum::Pendulum() { }

Pendulum::Pendulum(vec2 position, float rotation_speed, float length) {
    this->init(position, rotation_speed, length);
}

void Pendulum::init(vec2 position, float rotation_speed, float length) {
    Pendulum_Point p(position, rotation_speed, length);
    points.push_back(p);
}

void Pendulum::push_back(float rotation_speed, float length) {
    Pendulum_Point p(points[points.size() - 1].new_end, rotation_speed, length);
    points.push_back(p);
}

std::vector<std::vector<vec2>> Pendulum::get_next() {
    std::vector<std::vector<vec2>> movement;
    for (int i = 0; i < points.size(); i++) {
        if (i > 0) {
            // Update current pendulums position
            points[i].pos = points[i-1].new_end;
        } else {
            //Adds the origin point
            movement.push_back({points[i].pos});
        }

        points[i].update();
        movement.push_back({points[i].old_end, points[i].new_end});
    }
    return movement;
}