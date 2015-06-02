/*
 * postleapChecker.hh
 *
 *  Created on: Feb 15, 2011
 *      Author: Leonard Harris
 */

#ifndef POSTLEAPCHECKER_HH_
#define POSTLEAPCHECKER_HH_

#include "../../../MoMMA.hh"
#include "../../../model_spec/reaction.hh"

using namespace std;

namespace MoMMA{

	class PostleapChecker{
	public:
		PostleapChecker();
		PostleapChecker(const PostleapChecker& pl);
		virtual ~PostleapChecker();
		virtual bool check();
		virtual void correct(vector<double>& k, double& tau);
		virtual void update();
		virtual PostleapChecker* clone() const{ return new PostleapChecker(*this); }
	};
}

#endif /* POSTLEAPCHECKER_HH_ */
