#ifndef EMI_H
#define EMI_H

#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <fstream>
#include <deque>
#include "Rpp.h"

using namespace std;

class emi
{
	public:
		emi();
		~emi(){};
		deque<deque<deque<double> > > calEmi(deque<deque<double> > obs, deque<double> st);
		deque<deque<double> > swap(deque<deque<double> > x);
		deque<deque<deque<double> > > lst;
		deque<deque<double> > mat;
	private:
		Rpp r;
		deque<double> states;
};

emi::emi()
{
	states.push_back(0.1);
	states.push_back(1.5);
	states.push_back(2);
	states.push_back(3);
	states.push_back(4);
	states.push_back(5);
}

deque<deque<double> > emi::swap(deque<deque<double> > x)
{
	deque<double> init;
	deque<deque<double> > y;
	for(int i=0;i<x[0].size();i++)
	{
		init.clear();
		for(int j=0;j<x.size();j++)
		{
			init.push_back(x[j][i]);
		}
		y.push_back(init);
	}
	return y;
}

deque<deque<deque<double> > > emi::calEmi(deque<deque<double> > obs, deque<double> st)
{
	ofstream omf("B_mean.txt");
	deque<double> init;
//	int N=st.size();
	int n=obs.size();
	int T=obs[0].size();

	//cout << "row=" << n << endl;
	//cout << "col=" << T << endl;

	/*deque<double> test=r.sd(r.mylog(swap(obs)));
	for(int i=0;i<test.size();i++)
		cout << test[i] << " ";
	cout << endl;*/
	double B=r.mean(r.sd(r.mylog(swap(obs))));
	//double B=r.mean(r.sd(obs));
	omf << "mean=" << B << endl;
	for(int state=0;state<st.size();state++)
	{
		mat.clear();
		for(int i=0;i<n;i++)
		{
			init.clear();
			for(int j=0;j<T;j++)
			{
				init.push_back(r.dnorm(log(obs[i][j]),log(st[state]),B));
			}
			mat.push_back(init);
		}
		lst.push_back(mat);
	}
	omf.close();
	return lst;
}

#endif
