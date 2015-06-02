/*
 * monitor.cpp
 *
 *  Created on: Mar 30, 2010
 *      Author: Leonard Harris
 */

#include <iostream>
#include "monitor.hh"

using namespace std;
using namespace MoMMA;

Monitor::Monitor(){
	if (MoMMA::debug)
		cout << "Monitor constructor called.\n";
}

Monitor::Monitor(vector<Tracker*> tr){
	if (MoMMA::debug)
		cout << "Monitor constructor called.\n";
	this->addTrackers(tr);
}

Monitor::Monitor(vector<Tracker*> tr, vector<double> ts){
	if (MoMMA::debug)
		cout << "Monitor constructor called.\n";
	this->addTrackers(tr,ts);
}

Monitor::Monitor(vector<Tracker*> tr, vector<double> ts, vector<double> init){
	if (MoMMA::debug)
		cout << "Monitor constructor called.\n";
	this->addTrackers(tr,ts,init);
}

Monitor::~Monitor(){
	if (MoMMA::debug)
		cout << "Monitor destructor called.\n";
}

void Monitor::addTrackers(vector<Tracker*> tr){
	this->trackers = tr;
	for (unsigned int i=0;i < tr.size();i++){
		this->timescales.push_back(INFINITY);
		this->initialTimes.push_back(0.0);
	}
}
void Monitor::addTrackers(vector<Tracker*> tr, vector<double> ts){
	if (tr.size() != ts.size()){
		cout << "Error in Monitor::addTrackers(): trackers and timescales vectors must be the same size. Exiting." << endl;
		exit(1);
	}
	this->trackers = tr;
	this->timescales = ts;
	for (unsigned int i=0;i < tr.size();i++){
		this->initialTimes.push_back(0.0);
	}
}
void Monitor::addTrackers(vector<Tracker*> tr, vector<double> ts, vector<double> init){
	if (tr.size() != ts.size() || tr.size() != init.size() || ts.size() != init.size()){
		cout << "Error in Monitor::addTrackers(): trackers, timescales and initialTimes vectors must all be the same size.\n";
		cout << "Exiting." << endl;
		exit(1);
	}
	this->trackers = tr;
	this->timescales = ts;
	this->initialTimes = init;
}

bool Monitor::anyExceeded(){
	for (unsigned int i=0;i < this->trackers.size();i++){
		if (this->trackers.at(i)->exceeded()){
			return true;
		}
	}
	return false;
}

vector<Tracker*> Monitor::getExceeded(){
	vector<Tracker*> exceeded;
	for (unsigned int i=0;i < this->trackers.size();i++){
		if (this->trackers.at(i)->exceeded()){
			exceeded.push_back(this->trackers.at(i));
		}
	}
	return exceeded;
}

vector<Tracker*> Monitor::getChanged(){
	vector<Tracker*> changed;
	for (unsigned int i=0;i < this->trackers.size();i++){
		if (this->trackers.at(i)->changed()){
			changed.push_back(this->trackers.at(i));
		}
	}
	return changed;
}

Tracker* Monitor::getTracker(string name){
	for (unsigned int i=0;i < this->trackers.size();i++){
		if (this->trackers.at(i)->getName().compare(name) == 0){
			return this->trackers.at(i);
		}
	}
	cout << "Warning in Monitor::getTracker(): No Tracker named " << name << " could be found. Returning NULL." << endl;
	return NULL;
}

void Monitor::resetExceeded(double currentTime){
	for (unsigned int i=0;i < this->trackers.size();i++){
		if (this->trackers.at(i)->exceeded()){
			this->trackers.at(i)->reset();
			this->timescales.at(i) = currentTime - this->initialTimes.at(i);
			this->initialTimes.at(i) = currentTime;
			// Error check
			if (this->timescales.at(i) < 0.0){
				cout << "Error in Monitor::resetExceeded(): Timescale for variable " << this->trackers.at(i)->getName()
					 << " is negative (" << this->timescales.at(i) << "). Exiting." << endl;
				exit(1);
			}
		}
	}
}

void Monitor::resetAll(double currentTime){
	for (unsigned int i=0;i < this->trackers.size();i++){
		if (this->trackers.at(i)->exceeded()){
			this->timescales.at(i) = currentTime - this->initialTimes.at(i);
		}
		this->trackers.at(i)->reset();
		this->initialTimes.at(i) = currentTime;
	}
}

void Monitor::synchronize(double currentTime){
	for (unsigned int i=0;i < this->trackers.size();i++){
		if (!this->trackers.at(i)->synchronized()){
			this->initialTimes.at(i) = currentTime;
		}
	}
}

double Monitor::getTimescale(){
	if (this->timescales.size() > 0){
		double ts = this->timescales.at(0);
		for (unsigned int i=1;i < this->timescales.size();i++){
			if (this->timescales.at(i) < ts){
				ts = this->timescales.at(i);
			}
		}
		return ts;
	}
	return NAN;
}
