/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Particle.h
 * Author: jelanilyles
 *
 * Created on June 5, 2018, 11:19 AM
 */


#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

using namespace std;


class Particle 
{
public:
    Particle();
    Particle(double vel, double std, int num, double k, double limit, double pw, double ph);    //Particle init
    Particle(double x, double y, int num, int std);                                             //Test particle init    
    void Update(bool f1, bool f2, bool f3, bool f4, vector<Particle> &parts, vector<GridPlane> planes, double mean, double stddv, int pw, int ph, int pd);                                                                      //updates position variables                                                                 //updates velocity variables                                                                    //updates theta
    void UpdateDR();                                                                            // updates dr
    void UpdateGridBox();
    double GGen(double mean, double stddv);
    
    int num;                                            //Identifier
    int panewidth;                                      //Space parameters
    int paneheight;
    int panedepth;
    double limitdistance;                               //limit of the distance for which the forces of interaction will take effect 
    double posx, posy, posz, posx0, posy0, posz0, dx, dy, dz;            //position variables, originals position variables, displacement variables
    int dxbox, dybox, dzbox;                                          //particle to box displacement variables
    double velocity, velx, vely, velz, vel0;                        //velocity variables   
    double theta, beta;                                       //angle variable
    double dr;                                          //random factor variable
    double stddev;                                      // standard deviation for random number generator
    double sd;                                          // squared displacement variable
    int xbox, ybox, zbox;                                     //grid position variable
    double k;                                           // the constant of the strength of the interacting forces
    vector<Particle> close;
};

#endif /* PARTICLE_H */

