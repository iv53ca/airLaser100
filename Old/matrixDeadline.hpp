#ifndef MATRIXDEADLINE_H_INCLUDED
#define MATRIXDEADLINE_H_INCLUDED

#include <cmath>

#define pi 3.14159265

void getRoll(double mat[][3], double roll)
{
    roll = roll * pi / 180.;
    mat[0][0] = cos(roll);
    mat[0][1] = 0;
    mat[0][2] = - sin(roll);
    mat[1][0] = 0;
    mat[1][1] = 1;
    mat[1][2] = 0;
    mat[2][0] = sin(roll);
    mat[2][1] = 0;
    mat[2][2] = cos(roll);
}

void getPitch(double mat[][3], double pitch)
{
    pitch = pitch * pi / 180.;
    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[1][0] = 0;
    mat[1][1] = cos(pitch);
    mat[1][2] = sin(pitch);
    mat[2][0] = 0;
    mat[2][1] = - sin(pitch);
    mat[2][2] = cos(pitch);
}

void getYaw(double mat[][3], double yaw)
{
    yaw = yaw * pi / 180.;
    mat[0][0] = cos(yaw);
    mat[0][1] = -sin(yaw);
    mat[0][2] = 0;
    mat[1][0] = sin(yaw);
    mat[1][1] = cos(yaw);
    mat[1][2] = 0;
    mat[2][0] = 0;
    mat[2][1] = 0;
    mat[2][2] = 1;
}

void multiply(double m1[][3], double m2[][3], double m3[][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m3[i][j] = 0;
            for(int k = 0; k < 3; k++)
                m3[i][j] += m1[i][k] * m2[k][j];
        }
    }
}

void transpose(double m1[][3], double m2[][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            m2[i][j] = m1[j][i];
        }
    }
}

void finalMultiply(double mat[][3], double locX, double locY, double locZ, double &globX, double &globY, double &globZ)
{
    globX = mat[0][0] * locX + mat[0][1] * locY + mat[0][2] * locZ;
    globY = mat[1][0] * locX + mat[1][1] * locY + mat[1][2] * locZ;
    globZ = mat[2][0] * locX + mat[2][1] * locY + mat[2][2] * locZ;
}













#endif // MATRIXDEADLINE_H_INCLUDED
