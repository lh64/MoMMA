/**
 * @file src/MoMMA.hh
 * @brief The main header file for MoMMA
 *
 * This file contains the main function headers and declarations.
 *
 * @author Michael Sneddon
 * @date Started: Oct 14, 2009    Last edited: Oct 14, 2009
 *
 * @todo Fill in the details.
 *
 */
#ifndef MOMMA_HH_
#define MOMMA_HH_

#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>

#include "borrowed/data.hh"
#include "core/module.hh"
#include "core/fSimulator.hh"
#include "core/fCommunicator.hh"
#include "core/monitor.hh"
#include "core/translator.hh"
#include "core/tracker.hh"
#include "core/conductor.hh"

//!  Core Hive classes and functionality.
/*!
 *  All of the Hive framework classes and methods are defined in this namespace,
 *  so you should use this namespace in all of your projects.  Be sure to define
 *  a new namespace for problem specific projects.
 *  @author Michael Sneddon
 */
namespace MoMMA{
	static bool debug = false;
	static double TOL = 1e-12;
	static bool isNAN(double x){ return x != x; }
	static void serialSetup();
}


#endif /* MOMMA_HH_ */
