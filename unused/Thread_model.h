/******************************************
threads model
******************************************/
#include <deque>

struct t_model
{
	deque<deque<double> > d;
	deque<deque<deque<double> > > emi_a;
	int n_iter;
	int c_n_states;
	model c_m;
	int hmmc_g;
	int id;
	int sv;
};
