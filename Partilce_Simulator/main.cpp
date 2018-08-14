/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: jelanilyles
 *
 * Created on June 5, 2018, 11:18 AM
 */

#include <cstdlib>
#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <vector>
#include "Particle.h"
#include "GridBox.h"
#include "GridRow.h"
using namespace std;

/*
 *  
 */

void trim(string &s) {
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
  
    p = s.find_last_not_of(" \t");
    
    if (string::npos != p)
       s.erase(p+1);
 }


void UpdateGridBoxesAndClose(vector<Particle> parts, vector<GridPlane> planes) {     //Tracks which particles are close to the subject particle based on the grid
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(int m = 0; m < planes.size(); m++) {
            
                planes[m].rows[i].blocks[j].parts = {};
        
            }
        }
    }
    
    for(int q = 0; q < parts.size(); q++) {
        
        Particle p = parts[q];    
                    
        planes[p.zbox].rows[p.ybox].blocks[p.xbox].parts.push_back(p);
    }
    
    bool one = false, two = false, three = false, four = false, five = false, six = false;
    for(int q = 0; q < parts.size(); q++) {
        
        Particle p = parts[q];
        
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                for(int m = 0; m < 10; m++) {
               
                    
        
                    if(abs(i - p.xbox) <= 1) {
                        one = true;
                    }
         
                    if(abs(i - p.xbox) = 9) {
                        two = true;
                    }
                
                    if(abs(j - p.ybox) <= 1) {
                        three = true;
                    }
        
                    if(abs(j - p.ybox) = 9) {
                        four = true;
                    }
                
                    if(abs(m - p.zbox) <= 1) {
                        five = true;
                    }
                    
                    if(abs(m - p.zbox) = 9) {
                        six = true;
                    }
                            
               
        
        
                    if(one || two) {
                        if(three || four) {
                            if(five || six) {
                    
                                for(int l = 0; l < planes[m].rows[j].blocks[i].parts.size(); l++) {
                                    p = planes[m].rows[j].blocks[i].parts.pop_back();
                                    p.close.push_back(p);
                                }
                            }
                        }
                    }
                }
            }    
        }
    }   
}


    
    
    


int main(int argc, char** argv) {
    
    int numcells, numsteps;
    double  velocity, mean, std, k, limit, pw, ph;
    vector<Particle> particles;
    Particle * p, q, r, c;
    vector<GridPlane> planes;
    
    bool a1 = false, b2 = false, c3 = false, d4 = false;
    
    
    
    string filename, filename1, filename2;
    int choice = 0;
    
    
    cout << "Repulsion? Enter 1. Attraction? Enter 2. Neither? Enter 0." << endl;
    cin >> choice;
    if(choice == 1) {
        a1 = true;
        b2 = true;
    }     
    if(choice == 2) {
        a1 = true;
        b2 = false;
    }
    if(choice = 0) {
        a1 = false;
    }
    
    choice = 0;
    
    cout << "Angular Attraction? Enter 1. Repulsion? Enter 2. Neither? Enter 0." << endl;
    cin >> choice;
    if(choice == 1) {
        c3 = true;
        d4 = true;
    }
    if(choice == 2) {
        c3 = true;
        d4 = false;
    }
    if(choice = 0) {
        c3 = false;
    }
    
    if(a1 == 0 && c3 == 0) {
        cout << "No intermolecular forces." << endl;
    }
    
    
    
    cout << "Input filename" << endl;
    cin >> filename;
    
    cout << "Input mean-squared filename" << endl;
    cin >> filename1;
    
    cout << "Input close particles filename" << endl;
    cin >> filename2;
    
    cout << "Input number of particles" << endl;
    cin >> numcells;
    
    cout << "Input number of time steps" << endl;
    cin >> numsteps;
    
    cout << "Input velocity" << endl;
    cin >> velocity;
    
    cout << "Input mean/flow" << endl;
    cin >> mean;
    
    cout << "Input Standard Deviation" << endl;
    cin >> std;
    
    cout << "Input k-value" << endl;
    cin >> k;
    
    cout << "Input limiting distance of interaction" << endl;
    cin >> limit;
    
    cout << "Input pane width" << endl;
    cin >> pw;
   
    cout << "Input pane height" << endl;
    cin >> ph;
    
    
    
    fstream file;
    file.open(filename, ios::out);
    file << filename << endl;
    
    fstream file1;
    file1.open(filename1, ios::out);
    file1 << filename1 << endl;
    
    fstream file2;
    file2.open(filename2, ios::out);
    file2 << filename2 << endl;
    
    
    
    
    file << std::to_string(numcells) + " " + std::to_string(numsteps) + " " + std::to_string(k) << endl;
    file1 << std::to_string(numcells) + " " + std::to_string(numsteps) + " " + std::to_string(k) << endl;
    file2 << std::to_string(numcells) + " " + std::to_string(numsteps) + " " + std::to_string(k) << endl;
    
    
    for(int i = 0; i < numcells; i++) {
        Particle q = Particle(velocity, std, i+1, k, limit, pw, ph);
        particles.push_back(q);
    }
    
    
    
    file << "num/xpos/ypos/zpos/xpos0/ypos0/zpos0/dx/dy/dz/dxbox/dybox/dzbox/xbox/ybox/zbox/velocity/velx/vely/velz/theta/beta/dr" << endl;
    
    string output1;
    
    for(int j = 0; j < numsteps; j++) {
        
        double sd = 0;
        
        UpdateGridBoxesAndClose(particles, planes);
        
        for(int i = 0; i < numcells; i++) {
            
            p = &particles[i];
            
            string output;
            
            output = std::to_string(p->num) + " ";           
            output += to_string(p->posx) + " " + to_string(p->posy) + " " + to_string(p->posz) + " ";
            output += to_string(p->posx0) + " " + to_string(p->posy0) + " " + to_string(p->posz0) + " "; 
            output += to_string(p->dx) + " " + to_string(p->dy) + " " + to_string(p->dz) + " ";
            output += to_string(p->dxbox) + " " + to_string(p->dybox) + " " + to_string(p->dzbox) + " ";
            output += to_string(p->xbox) + " " + to_string(p->ybox) + " " + to_string(p->zbox) + " ";
            output += to_string(p->velocity) + " " + to_string(p->velx) + " " + to_string(p->vely) + " " + to_string(p->velz) + " ";
            output += to_string(p->theta) + " " to_string(p->beta);
            
            
            
      
              
            
            file << output << endl;
            
            
            sd += (p->dx)*(p->dx) + (p->dy)*(p->dy) + (p->dz)*(p->dz); 
            
            p->Update(a1, b2, c3, d4, particles, planes, mean, std);
             
        } 
        
        string output2;
        
        for(int i = 0; i < numcells; i++) {
            
            c = particles[i];
            string output3;
            
            for(int i = 0; i < c.close.size(); i++) {
                r = c.close[i];
                output3 += std::to_string(r.num) + " "; 
            }
            
            trim(output3);
            file2 << output3 << endl;
            
        }
        
        file2 << "-----------------" << endl;
        
        
        output1 = std::to_string(sd / numcells);
        
        file1 << output1 << endl;
  
    }
    
    
    
    
    
    
    
    file.close();
    file1.close();
    file2.close();
    
    
    cout << "Files were successfully written." << endl; 
//   
//    
    
    
////TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST
////TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST
    
//    fstream testfile;
//    testfile.open("test.txt", ios::out);
//    testfile << "test.txt" << endl;
//    
//    vector<Particle> testparticles;
//    Particle * test, test1, test2;
//    
//    int n = 1;
//            
//    for(int i = 1; i < 51; i++) {
//        for(int j = 1; j < 51; j++) {
//            Particle test = Particle(i, j, n, 1);
//            testparticles.push_back(test);
//            n++;
//        }    
//    }
//    
//    string testoutput;
//    
//    for(int i = 0; i < 5; i++) {
//        for(int j = 0; j < 2500 ; j++) {
//            
//            test1 = testparticles[j];
//            test1.CheckClose(testparticles);
//            test1.UpdateGridBox();
//            test1.UpdateVelocity(choice);
//            test1.UpdateTheta(choice);
//            
//            
//            testfile << std::to_string(test1.num) + " ";
//            testfile << std::to_string(test1.posx) + " " + std::to_string(test1.posy) << endl;
//            testfile << std::to_string(test1.xbox) + " " + std::to_string(test1.ybox) << endl;
//            
//            string test3 = " ";
//            
//            for(int i = 0; i < test1.close.size(); i++) {
//                test2 = test1.close[i];
//                test3 += std::to_string(test2.num) + " "; 
//            }
//            
//            trim(test3);
//            testfile << test3 << endl << "--------------" << endl;
// 
//        }
//    }
//            
//    testfile.close();
//    
//    
    
////TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST
////TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST    
    
    
    
    
}

