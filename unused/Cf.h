/*
# pho is a double variable between 0 and 1.

 

genData = function(m, n, s, k, pho) {

  d = matrix(rnorm(n, mean=0, sd=s), nrow=n)

  for (i in 2:m) {

    d = cbind(d, pho*d[,i-1]+(1-pho)*rnorm(n, mean=0, sd=s))

  }

  d = as.numeric(d) + 2# change matrix to vector

  rid = sample(1:m*n, k)

  d[rid] = d[rid] + 2

  d = matrix(d, nrow=n)

  g2 = seq(2, n, 2) # index of group2

  d[g2, (m/2):(m/2+5)] = d[g2, (m/2):(m/2+5)] +2 # group2 has 3 consecutive amplifications

  d[d<0] = 0.01

  d

}

*/

#include <iostream>
#include <algorithm>
//#include <unistd.h>
#include <stdio.h>
#include <memory.h>
//#include <dirent.h>
#include <sys/stat.h>
#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
#include <deque>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

class cf
{
	public:
		double norm(double mean, double sigma);
		int genData(int m,int n,double s,int k, double pho);
		deque<deque<double> > d;
	private:
};

double cf::norm(double mean, double sigma)
{
	unsigned int seed=rand()%100000;
	//cout << seed << endl;
	boost::mt19937 rng(seed);
	boost::normal_distribution<> nd(mean, sigma);
	boost::variate_generator<boost::mt19937&,boost::normal_distribution<> > var_nor(rng, nd);
	double d = var_nor();
	return d;
}

int cf::genData(int m,int n,double s,int k, double pho)
{
	d.clear();
//	srand( (unsigned)time( NULL ) );
/****************************init**************************/
	for(int i=0;i<n;i++)
	{
		deque<double> init;
		init.clear();
		d.push_back(init);
	}
/****************************init**************************/

	for(int i=0;i<n;i++)
		d[i].push_back(norm(0.0,s));

	for(int i=1;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			d[j].push_back(pho*d[j][i-1]+(1-pho)*norm(0.0,s));
		}
	}

	for(int i=0;i<k;i++)
	{
		int temp=rand()%(m*n);
		d[temp%n][temp/n]+=2;
	}

	
	for(int i=m/2;i<=m/2+5;i++)
	{
		for(int j=1;j<n;j=j+2)
		{
			d[j][i]+=2;
		}
	}


	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(d[j][i]<0)
				d[j][i]=0.01;
		}
	}
	
	return 0;
}
