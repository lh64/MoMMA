/*
 * fCommunicator.cpp
 *
 *  Created on: Oct 26, 2009
 *      Author: Leonard Harris
 */

#include "fCommunicator.hh"
#include <math.h>

using namespace std;
using namespace MoMMA;

fCommunicator::fCommunicator(){
	if (MoMMA::debug) cout << "fCommunicator constructor called.\n";
}

fCommunicator::fCommunicator(map<Data*,Module*> outgoing, vector<Translator*> incoming){
	if (MoMMA::debug) cout << "fCommunicator constructor called.\n";
	this->addOutgoing(outgoing);
	this->addIncoming(incoming);
}

fCommunicator::fCommunicator(vector<Translator*> incoming, map<Data*,Module*> outgoing){
	if (MoMMA::debug) cout << "fCommunicator constructor called.\n";
	this->addOutgoing(outgoing);
	this->addIncoming(incoming);
}

fCommunicator::~fCommunicator(){
	if (MoMMA::debug) cout << "fCommunicator destructor called." << endl;
	map<string,Translator*>::iterator it;
	for ( it=this->incoming.begin() ; it != this->incoming.end(); it++ ){
		delete (*it).second;
	}
}

void fCommunicator::addIncoming(Translator* t){
	this->incoming.insert( pair<string,Translator*>(t->getName(),t) );
}

// IMMEDIATE ACTION

bool fCommunicator::send(Data* outData){
	Module* dest;
	if (this->outgoing.find(outData->getName()) != this->outgoing.end()){
		dest = this->outgoing.find(outData->getName())->second;
		cout << "Sending data element '" << outData->getName() << "' to Module " << dest->getName()
			 << " (#" << dest->getId() << ")..." << endl;
		return dest->comm->receive(outData);
	}
	else{
		cout << "Data element '" << outData->getName() << "' not on outgoing list." << endl;
		return false;
	}

}

bool fCommunicator::receive(Data* inData){
	cout << "Message received...";
	if (this->incoming.find(inData->getName()) != this->incoming.end()){
		// Translate
		this->incoming.find(inData->getName())->second->translate(inData);
		return true;
	}
	else {
		cout << "Oops, '" << inData->getName() << "' doesn't exist." << endl;
		return false;
	}
}

// DELAYED ACTION
bool fCommunicator::send(Data* outData, double timeStamp){
	Module* dest;
	if (this->outgoing.find(outData->getName()) != this->outgoing.end()){
		dest = this->outgoing.find(outData->getName())->second;
		cout << "Sending data element '" << outData->getName() << "' to Module " << dest->getName()
			 << " (#" << dest->getId() << ")..." << endl;
		return dest->comm->receive(outData,timeStamp);
	}
	else{
		cout << "Data element '" << outData->getName() << "' not on outgoing list." << endl;
		return false;
	}
}

bool fCommunicator::receive(Data* inData, double timeStamp){
	cout << "Message received...";
	if (this->incoming.find(inData->getName()) != this->incoming.end()){
		// Store in the inbox
		this->inbox.insert( pair<Data*,double>(inData,timeStamp) );
		cout << "Added to inbox." << endl;
		return true;
	}
	else {
		cout << "Oops, '" << inData->getName() << "' doesn't exist." << endl;
		return false;
	}
}

void fCommunicator::processInbox(double upToTime){
	cout << "Processing inbox..." << endl;
	map<Data*,double>::iterator iter;
	Data* d;
	double t;
	for (iter = this->inbox.begin();iter != this->inbox.end();iter++){
		d = (*iter).first;
		t = (*iter).second;
		if (t <= upToTime){
			cout << "Translating data element '" << d->getName() << "' at time " << t << "..." << endl;
			this->incoming.find(d->getName())->second->translate(d);
			// Delete element
			this->inbox.erase(d);
		}
	}
	cout << "Done." << endl;
}
