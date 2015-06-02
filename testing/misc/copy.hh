/*
 * copy.hh
 *
 *  Created on: Jun 17, 2010
 *      Author: Leonard Harris
 */

#ifndef COPY_HH_
#define COPY_HH_

#include <iostream>
#include <string>

using namespace std;

namespace MoMMA{

	class Base{
	public:
		string name;
		Base(){};
		Base(string name){ this->name = name; }
		Base(const Base& b){ this->name = "copyOf_" + b.name; }
		virtual ~Base(){}
		virtual void hello(){ cout << "hello" << endl; }
		virtual Base* copyOf(){ return new Base(*this); }
	};

	class ChildX : public Base{
	public:
		int x;
		ChildX(string name, int x) : Base(name){ this->x = x; }
		ChildX(const ChildX& cx) : Base(cx){ this->x = cx.x; }
		virtual ~ChildX(){}
		virtual void hello(){ cout << "hello_X" << endl; }
		virtual Base* copyOf(){ return new ChildX(*this); }
	};

	class ChildY : public Base{
	public:
		double y;
		ChildY(string name, double y) : Base(name){ this->y = y; }
		ChildY(const ChildY& cy) : Base(cy){ this->y = cy.y; }
		virtual ~ChildY(){}
		virtual void hello(){ cout << "hello_Y" << endl; }
		virtual Base* copyOf(){ return new ChildY(*this); }
	};
}


#endif /* COPY_HH_ */
