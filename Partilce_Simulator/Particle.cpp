/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Particle.h"
#include "GridBox.h"
#include "GridRow.h"
#include "GridPlane.h"
#include <vector>
#include "math.h"
#define PI 3.1415926535

using namespace std;

Particle::Particle() {
    
}
Particle::Particle(double vel, double std, int num, double k, double limit, double pw, double ph) {  // Particle initialization
    panewidth = pw;
    paneheight = ph;
    posx = rand()%panewidth;
    posy = rand()%paneheight;
    posz = rand()%panedepth;
    posx0 = posx;
    posy0 = posy;
    posz0 = posz;
    dx = 0;
    dy = 0;
    dz = 0;
    dxbox = 0;
    dybox = 0;
    dzbox = 0;
    vel0 = vel;
    velocity = vel;
    theta = (double)(rand()%(2 * PI));
    beta = (double)(rand()%(2 * PI));
    velx = vel * cos(theta);
    vely = vel * sin(theta);
    velz = vel * sin(beta);
    dr = GGen(0, std);
    stddev = std;
    sd = dx*dx + dy*dy + dz*dz;
    UpdateGridBox();
    this->num = num;
    this->k = k;
    limitdistance = limit;
}

Particle::Particle(double x, double y, double z, int num, int std) {                        //Test Particle Initialization
    panewidth = 500;
    paneheight = 500;
    posx = x*10 - 5;
    posy = y*10 - 5;
    posz = z*10 - 5;
    velocity = 0;
    theta = 0;
    stddev = std;
    UpdateGridBox();
    this->num = num;
}
void Particle::Update(bool f1, bool f2, bool f3, bool f4, vector<Particle> &parts, vector<GridPlane> planes, double mean, double stddv) {                                                   // Updates the position based on the velocity
        
        Particle p;
          
        
        bool one = false, two = false, three = false;
        
        double xf, yf, zf, tf, bf, x, y, z;
        
        for(int i = 0; i < close.size(); i++) {
            
            p = close[i]; 
            
            if(abs(p.xbox - xbox) <= 1) {
                one = true;
            }
            
            if(abs(p.ybox - ybox) <= 1) {
                two = true;
            }
            
            if(abs(p.zbox - zbox) <= 1) {
                two = true;
            }
    
            if(one) { 
                x = p.posx - posx;
            }else if(p.posx > posx) {
                x = p.posx - posx - panewidth;
            }else if(p.posx < posx) {
                x = panewidth - posx + p.posx;
            }
    
            if(two) {
                y = abs(p.posy - posy);
            }else if(p.posy > posy) {
                y = p.posy - posy - paneheight;
            }else if(posy > p.posy) {
                y = paneheight - posy + p.posy;
            }
            
            if(three) {
                z = abs(p.posz - posz);
            }else if(p.posz > posz) {
                z = p.posz - posz - panedepth;
            }else if(posz > p.posz) {
                z = panedepth - posz + p.posz;
            }
        
    
            double r = sqrt(x*x + y*y z*z);
            
            
    
            if(r < limitdistance) {
                xf += (1 - r / limitdistance) * x / r;
                yf += (1 - r / limitdistance) * y / r;
                zf += (1 - r / limitdistance) * z / r;
                tf += (1 - r / limitdistance) * (p.theta - theta) / 2;
                bf += (1 - r / limitdistance) * (p.beta - beta) / 2;
            }                     
        }
        
        
        
        
        if(!f1) {
            xf = 0;
            yf = 0;
            zf = 0;
        }
        if(f1 && f2) {
            xf = xf * -1;
            yf = yf * -1;
            zf = zf * -1;
        }
        if(f1 && !f2) {
            xf = xf;
            yf = yf;
            zf = zf;
        }
        
        if(f3 && f4) {
            tf = tf * -1;
            bf = bf * -1;
        }
        
        if(f3 && !f4) {
            tf = tf;
            bf = bf;
        }
        
        if(!f3) {
            tf = 0;
            bf = 0;
        }
       
        
        posx += velocity * cos(theta + tf * k) * sin(beta + bf * k) + xf * k;
            if(posx > panewidth) {
                posx = posx - panewidth;
            }
            if(posx < 0) {
                posx = panewidth + posx;
            } 
        posy += velocity * sin(theta + tf * k) * sin(beta + bf * k) + yf * k;
            if(posy > paneheight) {
                posy = posy - paneheight;
            }
            if(posy < 0) {
                posy += paneheight + posy;
            }
        posz += velocity * cos(beta + bf * k) + zf * k;
            if(posz > panedepth) {
                posz = posz - panedepth;
            }
            if(posz < 0) {
                posz += panedepth + posz;
            }
    
    
        dx += velocity * cos(theta + tf * k) * sin(beta + bf * k) + xf * k;                                                    // Total displacement
        dy += velocity * sin(theta + tf * k) * sin(beta + bf * k) + yf * k;
        dz += velocity * cos(beta + bf * k) + zf * k;
    
    
        dxbox = (int)(((((posx0 + dx) / panewidth)*100)) - (((int)((posx0 + dx) / panewidth)*100) % 100))/100;   // Box displacement, how many times has the particle been transferred across a border
        dybox = (int)(((((posy0 + dy) / paneheight)*100)) - (((int)((posy0 + dx) / paneheight)*100) % 100))/100;
        dzbox = (int)(((((posz0 + dz) / panedepth)*100)) - (((int)((posz0 + dz) / panedepth)*100) % 100))/100;
    
        sd = dx*dx + dy*dy + dz*dz;
        
        if(posx <= 50) {
            xbox = 0;
        }else if(posx <= 2*panewidth/10.0 && posx > panewidth/10.0) {
            xbox = 1;
        }else if(posx <= 3*panewidth/10.0 && posx > 4*panewidth/10.0) {
            xbox = 2;
        }else if(posx <= 4*panewidth/10.0 && posx > 3*panewidth/10.0) {
            xbox = 3;
        }else if(posx <= 5*panewidth/10.0 && posx > 4*panewidth/10.0) {
            xbox = 4;
        }else if(posx <= 6*panewidth/10.0 && posx > 5*panewidth/10.0) {
            xbox = 5;
        }else if(posx <= 7*panewidth/10.0 && posx > 6*panewidth/10.0) {
            xbox = 6;
        }else if(posx <= 8*panewidth/10.0 && posx > 7*panewidth/10.0) {
            xbox = 7;
        }else if(posx <= 9*panewidth/10.0 && posx > 8*panewidth/10.0) {
            xbox = 8;
        }else{
            xbox = 9;
        }
            
        if(posy <= paneheight/10.0) {
            ybox = 0;
        }else if(posy <= 2*paneheight/10.0 && posy > paneheight/10.0) {
            ybox = 1;
        }else if(posy <= 3*paneheight/10.0 && posy > 2*paneheight/10.0) {
            ybox = 2;
        }else if(posy <= 4*paneheight/10.0 && posy > 3*paneheight/10.0) {
            ybox = 3;
        }else if(posy <= 5*paneheight/10.0 && posy > 4*paneheight/10.0) {
            ybox = 4;
        }else if(posy <= 6*paneheight/10.0 && posy > 5*paneheight/10.0) {
            ybox = 5;
        }else if(posy <= 7*paneheight/10.0 && posy > 6*paneheight/10.0) {
            ybox = 6;
        }else if(posy <= 8*paneheight/10.0 && posy > 7*paneheight/10.0) {
            ybox = 7;
        }else if(posy <= 9*paneheight/10.0 && posy > 8*paneheight/10.0) {
            ybox = 8;
        }else{
            ybox = 9;
        }
        
        if(posz <= panedepth/10.0) {
            zbox = 0;
        }else if(posz <= 2*panedepth/10.0 && posz > panedepth/10.0) {
            zbox = 1;
        }else if(posz <= 3*panedepth/10.0 && posz > 2*panedepth/10.0) {
            zbox = 2;
        }else if(posz <= 4*panedepth/10.0 && posz > 3*panedepth/10.0) {
            zbox = 3;
        }else if(posz <= 5*panedepth/10.0 && posz > 4*panedepth/10.0) {
            zbox = 4;
        }else if(posz <= 6*panedepth/10.0 && posz > 5*panedepth/10.0) {
            zbox = 5;
        }else if(posz <= 7*panedepth/10.0 && posz > 6*panedepth/10.0) {
            ybox = 6;
        }else if(posz <= 8*panedepth/10.0 && posz > 7*panedepth/10.0) {
            zbox = 7;
        }else if(posz <= 9*panedepth/10.0 && posz > 8*panedepth/10.0) {
            zbox = 8;
        }else{
            zbox = 9;
        }
     
}    


double Particle::FindTheta(Particle p) {                                            // finds the theta between 2 particles with the axis being the non called particle
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
                               


double Particle::GGen(double mean, double stddv)                                    // Random number generator
{//Box muller method
        double u1, u2, x, result;
       
        
        u1 = (double)rand() / RAND_MAX;
        u2 = (double)rand() / RAND_MAX;
 
        x = sqrt(-2.0 * log(u1)) * cos((double)(2.0 * PI) * u2);
       
        result = x * stddv + mean;
        
        return result;
}

void Particle::UpdateGridBox() {
    if(posx <= 50) {
            xbox = 0;
        }else if(posx <= 2*panewidth/10.0 && posx > panewidth/10.0) {
            xbox = 1;
        }else if(posx <= 3*panewidth/10.0 && posx > 4*panewidth/10.0) {
            xbox = 2;
        }else if(posx <= 4*panewidth/10.0 && posx > 3*panewidth/10.0) {
            xbox = 3;
        }else if(posx <= 5*panewidth/10.0 && posx > 4*panewidth/10.0) {
            xbox = 4;
        }else if(posx <= 6*panewidth/10.0 && posx > 5*panewidth/10.0) {
            xbox = 5;
        }else if(posx <= 7*panewidth/10.0 && posx > 6*panewidth/10.0) {
            xbox = 6;
        }else if(posx <= 8*panewidth/10.0 && posx > 7*panewidth/10.0) {
            xbox = 7;
        }else if(posx <= 9*panewidth/10.0 && posx > 8*panewidth/10.0) {
            xbox = 8;
        }else{
            xbox = 9;
        }
            
        if(posy <= paneheight/10.0) {
            ybox = 0;
        }else if(posy <= 2*paneheight/10.0 && posy > paneheight/10.0) {
            ybox = 1;
        }else if(posy <= 3*paneheight/10.0 && posy > 2*paneheight/10.0) {
            ybox = 2;
        }else if(posy <= 4*paneheight/10.0 && posy > 3*paneheight/10.0) {
            ybox = 3;
        }else if(posy <= 5*paneheight/10.0 && posy > 4*paneheight/10.0) {
            ybox = 4;
        }else if(posy <= 6*paneheight/10.0 && posy > 5*paneheight/10.0) {
            ybox = 5;
        }else if(posy <= 7*paneheight/10.0 && posy > 6*paneheight/10.0) {
            ybox = 6;
        }else if(posy <= 8*paneheight/10.0 && posy > 7*paneheight/10.0) {
            ybox = 7;
        }else if(posy <= 9*paneheight/10.0 && posy > 8*paneheight/10.0) {
            ybox = 8;
        }else{
            ybox = 9;
        }
        
        if(posz <= panedepth/10.0) {
            zbox = 0;
        }else if(posz <= 2*panedepth/10.0 && posz > panedepth/10.0) {
            zbox = 1;
        }else if(posz <= 3*panedepth/10.0 && posz > 2*panedepth/10.0) {
            zbox = 2;
        }else if(posz <= 4*panedepth/10.0 && posz > 3*panedepth/10.0) {
            zbox = 3;
        }else if(posz <= 5*panedepth/10.0 && posz > 4*panedepth/10.0) {
            zbox = 4;
        }else if(posz <= 6*panedepth/10.0 && posz > 5*panedepth/10.0) {
            zbox = 5;
        }else if(posz <= 7*panedepth/10.0 && posz > 6*panedepth/10.0) {
            ybox = 6;
        }else if(posz <= 8*panedepth/10.0 && posz > 7*panedepth/10.0) {
            zbox = 7;
        }else if(posz <= 9*panedepth/10.0 && posz > 8*panedepth/10.0) {
            zbox = 8;
        }else{
            zbox = 9;
        }
}



void Particle::UpdateTheta(int c) {                                                    // Updates the theta angle based on forces
    if(c == 1 || c == 2) {  //Repulsion or attraction force updater
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
    
    if(c == 3) {   // Angular force updater
        theta = ((int)((theta + CalcAlignment())*180/PI) % 360)*PI/180; 
    }
}

void Particle::UpdateDR() {                                                             //Updates dr, the random factor if that factor is to be uniform for each step
    dr = GGen(0, stddev);
}


