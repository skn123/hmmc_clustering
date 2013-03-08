#ifndef MODEL_H
#define MODEL_H

#include <deque>

using namespace std;

struct model
{
	deque<double> states;
	deque<double> pi;
	deque<deque<double> > A;
};

#endif
