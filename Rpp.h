#ifndef RPP_H
#define RPP_H

#include <iostream>
#include <algorithm>
//#include <unistd.h>
#include <stdio.h>
#include <memory.h>
//#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <fstream>
#include <string>
#include <deque>
#include <stdlib.h>

using namespace std;

//typedef function<VOID (int)> callback;

/************************************************
mathematic methods transfer to C++ language
************************************************/

class Rpp
{
	public:
		Rpp(){};
		~Rpp(){};
		deque<deque<double> > mylog (deque<deque<double> > x);
		deque<double> mylog(deque<double> x);
		double mean(deque<deque<double> > x);
		double mean(deque<double> x);
		deque<double> sum(deque<deque<double> > x);
		deque<double> wmax(deque<deque<double> > x);
		deque<double> sd(deque<deque<double> > x);
		double sd(deque<double> x);
		double dnorm(double x, double m, double s);
	private:
};

deque<deque<double> > Rpp::mylog (deque<deque<double> > x)
{
	deque<deque<double> > result;
	for(int i=0;i<x.size();i++)
	{
		deque<double> init;
		init.clear();
		for(int j=0;j<x[i].size();j++)
		{
			init.push_back(log(x[i][j]));
		}
		result.push_back(init);
	}
	return result;
}

deque<double> Rpp::mylog(deque<double> x)
{
	deque<double> result;
	for(int i=0;i<x.size();i++)
	{
		result.push_back(log(x[i]));
	}
	return result;
}

double Rpp::mean(deque<deque<double> > x)
{
	double total=0;
	int count=0;
	for(int i=0;i<x.size();i++)
	{
		for(int j=0;j<x[i].size();j++)
		{
			count++;
			total+=x[i][j];
		}
	}
	return(total/(double)count);
}

double Rpp::mean(deque<double> x)
{
	double total=0;
	for(int i=0;i<x.size();i++)
		total+=x[i];
	return(total/(double)x.size());
}

deque<double> Rpp::sum(deque<deque<double> > x)
{
	deque<double> result;
	double total=0;
	for(int i=0;i<x.size();i++)
	{
		total=0;
		for(int j=0;j<x[i].size();j++)
		{
			total+=x[i][j];
		}
		result.push_back(total);
	}
	return(result);
}

deque<double> Rpp::wmax(deque<deque<double> > x)
{
	deque<double> result;
	double max=0;
	int max_index=0;
	for(int i=0;i<x.size();i++)
	{
		max_index=0;
		for(int j=0;j<x[i].size();j++)
		{
			if(j==0)
				max=x[i][j];
			if(x[i][j]>max)
			{
				max=x[i][j];
				max_index=j;
			}
		}
		result.push_back(max_index);
	}
	return(result);
}

deque<double> Rpp::sd(deque<deque<double> > x)
{
	double total=0,m=0;
	deque<double> result;
	for(int i=0;i<x.size();i++)
	{
		m=mean(x[i]);
		total=0;
		for(int j=0;j<x[i].size();j++)
			total+=(x[i][j]-m)*(x[i][j]-m);
		result.push_back(sqrt(total/(double)(x[i].size()-1)));
	}
	return result;
}

double Rpp::sd(deque<double> x)
{
	int count=0;
	double total=0,m=0;
	double result;
	m=mean(x);
	count=0;
	total=0;
	for(int j=0;j<x.size();j++)
	{
		total+=(x[j]-m)*(x[j]-m);
		count++;
	}
	result=(sqrt(total/(double)(count-1)));
	return result;
}

double Rpp::dnorm(double x, double m, double s)
{
	double pi=3.1415926;
	double result=0;
	result=(double)1.0/(sqrt(2*pi)*s)*exp(-(x-m)*(x-m)/(2*s*s));
	return result;
}

#endif
