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
#include "Particle.h"

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




    
    
    


int main(int argc, char** argv) {
    
    int numcells, numsteps;
    double  velocity, std, k, limit, pw, ph;
    vector<Particle> particles;
    Particle * p, q, r, c;
    
    
    
    
    
    string filename, filename1, filename2;
    int choice;
    
    
    cout << "Input simulation type" << endl;
    cout << "1. Repulsion" << endl;
    cout << "2. Attraction" << endl;
    cout << "3. Angular Attraction" << endl;
    cin >> choice;
    
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
    
    
    
    file << "num/xpos/ypos/xpos0/ypos0/dx/dy/dxbox/dybox/xbox/ybox/velocity/theta/velx/vely/dr" << endl;
    
    string output1;
    
    for(int j = 0; j < numsteps; j++) {
        
        double sd = 0;
        
        for(int i = 0; i < numcells; i++) {
            
            p = &particles[i];
            
            string output;
            
            output = std::to_string(p->num) + " ";
            
            
            output += std::to_string(p->posx) + " " + std::to_string(p->posy) + " ";
            p->UpdatePosition();
            output += std::to_string(p->posx0) + " " + std::to_string(p->posy0) + " "; 
            output += std::to_string(p->dx) + " " + std::to_string(p->dy) + " ";
            output += std::to_string(p->dxbox) + " " + std::to_string(p->dybox) + " ";
            
            
            output += std::to_string(p->xbox) + " " + std::to_string(p->ybox) + " ";
            p->UpdateGridBox();
            
            
            output += std::to_string(p->velocity) + " " + std::to_string(p->velx) + " " + to_string(p->vely) + " ";
            p->UpdateVelocity(choice);
            
            output += std::to_string(p->theta) + " ";
            p->UpdateTheta(choice);
            
            
            output += std::to_string(p->dr);
            p->UpdateDR();  
            
            file << output << endl;
            
            sd += (p->dx)*(p->dx) + (p->dy)*(p->dy); 
             
        } 
        
        string output2;
        
        for(int i = 0; i < numcells; i++) {
            
            c = particles[i];
            c.UpdateClose(particles);
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
    
    
////    TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST//TEST TEST TEST TEST TEST TEST TEST
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
////    
    
    
    
    
}

