/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridPlane.h
 * Author: jelanilyles
 *
 * Created on August 3, 2018, 2:47 PM
 */

#ifndef GRIDPLANE_H
#define GRIDPLANE_H

#include <vector>
#include "Particle.h"
#include "GridBox.h"
#include "GridRow.h"

using namespace std;


class GridPlane
{
public:
    
    int z;
    
    vector<GridRow> rows;
    
    GridPlane();
    GridPlane(int c);
};



#endif /* GRIDPLANE_H */

