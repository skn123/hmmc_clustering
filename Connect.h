#include <iostream>
#include <math.h>
#include <deque>
#include <stdlib.h>

#include "Emi.h"
#include "Hmm.h"
#include "Import_file.h"
#include "Model.h"

using namespace std;
class connect
{
	public:
		connect(double prob);
		~connect(){};
		deque<double> HMM_states;
		deque<double> pi;
		model m;
		int n_states;
		deque<deque<double> > A;
		deque<deque<deque<double> > > emi_all;
		deque<deque<double> > file_buf;
		void conn(deque<deque<double> > d);
};

connect::connect(double prob) {
	HMM_states.push_back(0.1);
	HMM_states.push_back(1.5);
	HMM_states.push_back(2);
	HMM_states.push_back(3);
	HMM_states.push_back(4);
	HMM_states.push_back(5);

	pi.push_back(0.03);
	pi.push_back(0.06);
	pi.push_back(0.8);
	pi.push_back(0.06);
	pi.push_back(0.03);
	pi.push_back(0.02);

	n_states = HMM_states.size();

	for (int i = 0; i < n_states; i++) {
		deque<double> init;
		init.clear();

		for (int j = 0; j < n_states; j++) {
			if (i == j) {
				init.push_back(prob);
            } else {
				init.push_back((1 - prob) / (double)(n_states - 1));
            }
		}
		A.push_back(init);
	}

	m.A = A;
	m.pi = pi;
	m.states = HMM_states;
}

void connect::conn(deque<deque<double> > d) {
	emi e;
	file_buf = d;
	emi_all = e.calEmi(file_buf,HMM_states);
}
