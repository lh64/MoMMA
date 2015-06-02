/*
 * postleapChecker.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: Leonard Harris
 */

#include "postleapChecker.hh"

using namespace std;
using namespace MoMMA;

PostleapChecker::PostleapChecker(){
	if (MoMMA::debug)
		cout << "PostleapChecker constructor called." << endl;
}

PostleapChecker::PostleapChecker(const PostleapChecker& pl){
	if (MoMMA::debug)
		cout << "PostleapChecker copy constructor called." << endl;
}

PostleapChecker::~PostleapChecker(){
	if (MoMMA::debug)
		cout << "PostleapChecker destructor called." << endl;
}

bool PostleapChecker::check(){
	cout << "Error in PostleapChecker::check(): Cannot use base method, must overload. Exiting." << endl;
	exit(1);
	return NULL;
}

void PostleapChecker::correct(vector<double>& k, double& tau){
	cout << "Error in PostleapChecker::correct(): Cannot use base method, must overload. Exiting." << endl;
	exit(1);
}

void PostleapChecker::update(){
	if (MoMMA::debug)
		cout << "Using base method PostleapChecker::update(): Doing nothing." << endl;
}

