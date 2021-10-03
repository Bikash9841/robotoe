#pragma once

#include <math.h>

class Kinematics
{

private:
    float len_hum;
    float len_rad;

public:
    float q1, q2;

    Kinematics(){};

    void init(float len_hum_, float len_rad_)
    {
        len_hum = len_hum_;
        len_rad = len_rad_;
    }

    // Kinematics implementation
    void update(float x, float y)
    {
        float len_temp;
        float q1_temp, q2_temp, q3;

        len_temp = sqrt((x * x) + (y * y));
        q1 = atan(y / x);
        q2 = acos(((len_hum * len_hum) + (len_temp * len_temp) - (len_rad * len_rad)) / (2 * len_hum * len_temp));
        q3 = acos(((len_hum * len_hum) + (len_rad * len_rad) - (len_temp * len_temp)) / (2 * len_hum * len_rad));

        q1_temp = q1 + q2;
        q2_temp = q3;

        if (x < 0)
        {
            q1 = 180 + (q1_temp * 180.0 / M_PI);
            q2 = ((q2_temp * 180.0 / M_PI) - 180);
        }
        else
        {
            q1 = q1_temp * 180.0 / M_PI;
            q2 = (q2_temp * 180.0 / M_PI) - 180;
        }
    }
};
