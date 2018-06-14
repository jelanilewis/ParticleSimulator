/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Particle.h"
#include <iostream>
#include <vector>
#include "math.h"
#define PI 3.1415926535

using namespace std;

Particle::Particle() {
    
}
Particle::Particle(double vel, double std, int num, double k, double limit, double pw, double ph) {
    panewidth = pw;
    paneheight = ph;
    posx = rand()%panewidth;
    posy = rand()%paneheight;
    posx0 = posx;
    posy0 = posy;
    dx = 0;
    dy = 0;
    dxbox = 0;
    dybox = 0;
    velocity = vel;
    theta = (double)(rand()%360 * (3.1415926535) / 180);
    velx = vel * cos(theta);
    vely = vel * sin(theta);
    dr = GGen(0, std);
    stddev = std;
    sd = dx*dx + dy*dy;
    UpdateGridBox();
    this->num = num;
    this->k = k;
    limitdistance = limit;
}

Particle::Particle(double x, double y, int num, int std) {
    panewidth = 500;
    paneheight = 500;
    posx = x*10 - 5;
    posy = y*10 - 5;
    velocity = 0;
    theta = 0;
    stddev = std;
    UpdateGridBox();
    this->num = num;
}

double Particle::CalcRepulsionX() {
    double add;    
    for(int i = 0; i < close.size(); i++) {
        if(RadiusCheck(close[i])) {
            add += FindXForce(close[i]);
        }
    }
    return add;    
}

double Particle::CalcRepulsionY() {
    double add;
    for(int i = 0; i < close.size(); i++) {
        if(RadiusCheck(close[i])) {
            add += FindYForce(close[i]);
        }       
    }
    return add;
}

double Particle::CheckEnergy(Particle p) {
    double r = Radius(p);
    double a = limitdistance - r;
    double energy = k * a*a / 2;
    return energy;
}

bool Particle::RadiusCheck(Particle p) {
    
    bool one = false;
    bool two = false;
        
    double x;
    double y;
    
        if(abs(p.posx - posx) <= panewidth/10.0) {
            one = true;
        }
            
        if(abs(p.posy - posy) <= paneheight/10.0) {
            two = true;
        }
    
        if(one) { 
            x = abs(p.posx - posx);
        }else{
            x = panewidth - abs(p.posx - posx);
        }        
    
        if(two) {
            y = abs(p.posy - posy);
        }else{
            y = paneheight - abs(p.posy - posy);
        }
    
    double r = sqrt(x*x + y*y);
    
    if(r < limitdistance) {
        return true;
    }else{
        return false;
    }
}

double Particle::Radius(Particle p) {
    
    bool one = false;
    bool two = false;
        
    double x;
    double y;
    
        if(abs(p.posx - posx) <= panewidth/10.0) {
            one = true;
        }
            
        if(abs(p.posy - posy) <= paneheight/10.0) {
            two = true;
        }
    
        if(one) { 
            x = abs(p.posx - posx);
        }else{
            x = panewidth - abs(p.posx - posx);
        }        
    
        if(two) {
            y = abs(p.posy - posy);
        }else{
            y = paneheight - abs(p.posy - posy);
        }
    
    double r = sqrt(x*x + y*y);
    return r;
}

double Particle::FindAlignmentForce(Particle p) {
    double r = Radius(p);
    double a = limitdistance - r;
    double angle = p.theta - theta;
    double da = (a / limitdistance) * (angle / 2);
    return da;
}

double Particle::CalcAlignment() {
    double add;
    for(int i = 0; i < close.size(); i++) {
        if(RadiusCheck(close[i])) {
            add += FindAlignmentForce(close[i]);
        }
    }
    return add;
}

double Particle::FindXForce(Particle p) {
    double r = Radius(p);
    double a = limitdistance - r;
    
    double force = a * k * cos(FindTheta(p));
    return force;
}

double Particle::FindTheta(Particle p) {
    bool one = false;
    bool two = false;
        
    double x;
    double y;
    
        if(abs(p.posx - posx) <= panewidth/10.0) {
            one = true;
        }
            
        if(abs(p.posy - posy) <= paneheight/10.0) {
            two = true;
        }
    
        if(one) { 
            x = p.posx - posx;
        }else{
            x = panewidth - p.posx + posx;
        }        
    
        if(two) {
            y = p.posy - posy;
        }else{
            y = paneheight - p.posy + posy;
        }
    double a;
    double b;
    
    double theta = atan(y/x);
    if(x == 0 || y == 0) {
        theta += 0;
    }else if(x < 0 && y < 0) {
        theta += PI;
    }else if(x < 0 && y > 0) {
        theta += PI;
    }else if(x > 0 && y < 0) {
        theta += 0;
    }else if(x > 0 && y > 0) {
        theta += 0;
    }
    
    return theta;
}

double Particle::FindYForce(Particle p) {
    double r = Radius(p);
    double a = limitdistance - r;
    double force = a * k * sin(FindTheta(p)); 
    return force;
}

void Particle::CheckClose(vector<Particle> &parts) {
    
    Particle p;
    close.clear();
    
    for(int i = 0; i < parts.size(); i++) {
        p = parts[i];
        bool one = false;
        bool two = false;
        bool three = false;
        bool four = false;
        
        if(abs(p.posx - posx) <= panewidth/10.0) {
            one = true;
        }
            
        if(abs(p.posy - posy) <= paneheight/10.0) {
            two = true;
        }
        
        if(abs(p.posy - posy) >= panewidth * 9.0/10.0) {
            three = true;
        }
               
        if(abs(p.posx - posx) >= paneheight * 9.0/10.0) {
            four = true;
        }
        
        if(two || three) {
                if(one || four) {
                    close.push_back(p);
                }
        }
    }
}


void Particle::UpdateClose(vector<Particle> &parts) {
    
    Particle p;
    
    for(int i = 0; i < parts.size(); i++) {
        
        p = parts[i];
        bool one = false;
        bool two = false;
        bool three = false;
        bool four = false;
        
         
        if(abs(p.xbox - xbox) <= 1) {
            one = true;
        }
            
        if(abs(p.ybox - ybox) <= 1) {
            two = true;
        }
        
        if(abs(p.ybox - ybox) >= 9) {
            three = true;
        }
               
        if(abs(p.xbox - xbox) >= 9) {
            four = true;
        }
        
        if(two || three) {
            if(one || four) {
                close.push_back(p);
            }
        }        
    }
} 

void Particle::UpdateGridBox() {
        double x = posx;
        double y = posy;

        if(posx <= 50) {
            xbox = 1;
        }else if(posx <= 2*panewidth/10.0 && posx > panewidth/10.0) {
            xbox= 2;
        }else if(posx <= 3*panewidth/10.0 && posx > 4*panewidth/10.0) {
            xbox= 3;
        }else if(posx <= 4*panewidth/10.0 && posx > 3*panewidth/10.0) {
            xbox = 4;
        }else if(posx <= 5*panewidth/10.0 && posx > 4*panewidth/10.0) {
            xbox = 5;
        }else if(posx <= 6*panewidth/10.0 && posx > 5*panewidth/10.0) {
            xbox = 6;
        }else if(posx <= 7*panewidth/10.0 && posx > 6*panewidth/10.0) {
            xbox = 7;
        }else if(posx <= 8*panewidth/10.0 && posx > 7*panewidth/10.0) {
            xbox = 8;
        }else if(posx <= 9*panewidth/10.0 && posx > 8*panewidth/10.0) {
            xbox = 9;
        }else{
            xbox = 10;
        }
            
        if(posy <= paneheight/10.0) {
            ybox = 1;
        }else if(posy <= 2*paneheight/10.0 && posy > paneheight/10.0) {
            ybox= 2;
        }else if(posy <= 3*paneheight/10.0 && posy > 2*paneheight/10.0) {
            ybox= 3;
        }else if(posy <= 4*paneheight/10.0 && posy > 3*paneheight/10.0) {
            ybox = 4;
        }else if(posy <= 5*paneheight/10.0 && posy > 4*paneheight/10.0) {
            ybox = 5;
        }else if(posy <= 6*paneheight/10.0 && posy > 5*paneheight/10.0) {
            ybox = 6;
        }else if(posy <= 7*paneheight/10.0 && posy > 6*paneheight/10.0) {
            ybox = 7;
        }else if(posy <= 8*paneheight/10.0 && posy > 7*paneheight/10.0) {
            ybox = 8;
        }else if(posy <= 9*paneheight/10.0 && posy > 8*paneheight/10.0) {
            ybox = 9;
        }else{
            ybox = 10;
        }
    
}


double Particle::GGen(double mean, double stddv)
{//Box muller method
        double u1, u2, x, result;
       
        
        u1 = (double)rand() / RAND_MAX;
        u2 = (double)rand() / RAND_MAX;
 
        x = sqrt(-2.0 * log(u1)) * cos((double)(2.0 * PI) * u2);
       
        result = x * stddv + mean;
        
        return result;
}

void Particle::UpdatePosition() {
    posx = posx + velocity * cos(theta);
        if(posx > panewidth) {
            posx = posx - panewidth;
        }
        if(posx < 0) {
            posx = panewidth + posx;
        } 
    posy = posy + velocity * sin(theta);
        if(posy > paneheight) {
            posy = posy - paneheight;
        }
        if(posy < 0) {
            posy = paneheight + posy;
        }
    
    
    dx = dx + velocity * cos(theta);
    dy = dy + velocity * sin(theta);
    
    
    dxbox = (posx0 + dx - 0.5) / panewidth;
    dybox = (posy0 + dy - 0.5) / paneheight;
    
    
    sd = dx*dx + dy*dy;
    
    UpdateGridBox();
    
}


void Particle::UpdateVelocity(int c) {
    if(c == 1) {
        velx = velocity*cos(theta) + CalcRepulsionX();
        vely = velocity*sin(theta) + CalcRepulsionY();
        velocity = sqrt(velx*velx + vely*vely); 
//                + GGen(0, stddev);
    }
    if(c == 2) {
        velx = velocity*cos(theta) - CalcRepulsionX();
        vely = velocity*sin(theta) - CalcRepulsionY();
        velocity = sqrt(velx*velx + vely*vely); 
//                + GGen(0, stddev);
    }
    if(c == 3) {
        velocity += dr;
    }
}
void Particle::UpdateTheta(int c) {
    if(c == 1 || c == 2) {
        theta = atan(vely/velx);
//                + GGen(0, stddev);
        
        if(velx == 0 || vely == 0) {
            theta += 0;
        }else if(velx < 0 && vely < 0) {
            theta += PI;
        }else if(velx < 0 && vely > 0) {
            theta += PI;
        }else if(velx > 0 && vely < 0) {
            theta += 0;
        }else if(velx > 0 && vely > 0) {
            theta += 0;
        }
    }
    
    if(c == 3) {
        theta = ((int)((theta + CalcAlignment())*180/PI) % 360)*PI/180; 
    }
}

void Particle::UpdateDR() {
    dr = GGen(0, stddev);
}

