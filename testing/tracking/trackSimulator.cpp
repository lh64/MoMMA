/*
 * trackSimulator.cpp
 *
 *  Created on: Apr 20, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include <math.h>
#include "trackSimulator.hh"

using namespace std;
using namespace MoMMA;

TrackSimulator::TrackSimulator(double v_init, double p_init){
	if (MoMMA::debug) cout << "TrackSimulator constructor called." << endl;
	this->v = v_init;
	this->p = p_init;
}
/*
double TrackSimulator::run(int n){
	int v_init = this->v;
	for (int i=0;i<n;i++){
		this->v += this->p;
	}
	return (static_cast<double>(this->v - v_init)/1e6);
}
*/
double TrackSimulator::run(double t){
	double time = 0.0;
	while (time < t){
		this->v += 1.0;
		time += 1.0/(this->v*this->p);
	}
	return time;
}
