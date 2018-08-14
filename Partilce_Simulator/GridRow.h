/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GridRow.h
 * Author: jelanilyles
 *
 * Created on August 1, 2018, 8:16 PM
 */

#ifndef GRIDROW_H
#define GRIDROW_H

#include "GridBox.h"
#include <vector>

using namespace std;

class GridRow
{
public:

    int y;
    int z;
    
    vector<GridBox> blocks;
    
    GridRow();
    GridRow(int b, int c);
    
};

#endif /* GRIDROW_H */

