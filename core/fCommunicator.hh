/*
 * fCommunicator.hh
 *
 *  Created on: Oct 26, 2009
 *      Author: Leonard Harris
 */

#ifndef FCOMMUNICATOR_HH_
#define FCOMMUNICATOR_HH_

#include "../MoMMA.hh"

using namespace std;

namespace MoMMA{
	class Module;
	class Translator;
	class fCommunicator{
	public:
		map<string,Module*> outgoing;  // <data_name,destination>
		map<string,Translator*> incoming; // <data_name,translator>
		map<Data*,double> inbox; // <incoming_data,timestamp>

		fCommunicator();
		fCommunicator(map<Data*,Module*> outgoing, vector<Translator*> incoming);
		fCommunicator(vector<Translator*> incoming, map<Data*,Module*> outgoing);
		~fCommunicator();

		void addOutgoing(Data* d, Module* dest){ this->outgoing.insert( pair<string,Module*>(d->getName(),dest) ); }
		void addOutgoing(map<Data*,Module*> outgoing){
			map<Data*,Module*>::iterator outIter;
			for (outIter = outgoing.begin();outIter != outgoing.end();outIter++){
				this->addOutgoing((*outIter).first,(*outIter).second);
			}
		}

		void addIncoming(Translator* t);
		void addIncoming(vector<Translator*> incoming){
			for (unsigned int i=0;i < incoming.size();i++){ this->addIncoming(incoming.at(i)); }
		}

		bool send(Data* outData);  // IMMEDIATE ACTION
		bool receive(Data* inData);

		bool send(Data* outData, double timeStamp);  // DELAYED ACTION
		bool receive(Data* inData, double timeStamp);

		void processInbox(double upToTime);
	};
}

#endif /* FCOMMUNICATOR_HH_ */
