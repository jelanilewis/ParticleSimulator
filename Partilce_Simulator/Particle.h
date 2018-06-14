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
#include <vector>
#ifndef PARTICLE_H
#define PARTICLE_H
using namespace std;


class Particle 
{
public:
    Particle();
    Particle(double vel, double std, int num, double k, double limit, double pw, double ph);
    Particle(double x, double y, int num, int std);
    void UpdatePosition();
    void UpdateVelocity(int c);
    void UpdateTheta(int c);
    void UpdateDR();
    void UpdateGridBox();
    void CheckClose(vector<Particle> &parts);
    double CheckEnergy(Particle p);
    double Radius(Particle p);
    double FindTheta(Particle p);
    bool RadiusCheck(Particle p);
    double CalcRepulsionX();
    double CalcRepulsionY();
    double FindXForce(Particle p);
    double FindYForce(Particle p);
    double FindAlignmentForce(Particle p);
    double CalcAlignment();
    double FindNetXForce(vector<Particle> &parts);
    double FindNetYForce(vector<Particle> &parts);
    void UpdateClose(vector<Particle> &parts);
    double GGen(double mean, double stddv);
    
    int num;
    int panewidth;
    int paneheight;
    double limitdistance;
    double posx, posy, posx0, posy0, dx, dy;
    int dxbox;
    int dybox;
    double velocity, velx, vely;
    double theta;
    double dr;
    double stddev;
    double sd;
    int xbox, ybox;
    double k;
    vector<Particle> close;
};

#endif /* PARTICLE_H */

