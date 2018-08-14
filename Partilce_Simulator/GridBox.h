/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridBox.h
 * Author: jelanilyles
 *
 * Created on August 1, 2018, 5:20 PM
 */

#ifndef GRIDBOX_H
#define GRIDBOX_H
#include "Particle.h"
#include <vector>

using namespace std;

class GridBox
{
public:
    int x;
    int y;
    int z;
    
    vector<Particle> parts;
    
    GridBox();
    GridBox(int a, int b, int c);
};

#endif /* GRIDBOX_H */

