#include <iostream>
#include <algorithm>
//#include <unistd.h>
#include <stdio.h>
#include <memory.h>
//#include <dirent.h>
#include <sys/stat.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <string>
#include <deque>
#include <stdlib.h>

using namespace std;

class import_file
{
	public:
		import_file(){};
		~import_file(){};
		deque<string> read_name(char *my_path);
		deque<deque<double> > read_F(string my_path, int *stop_value);
	private:
		deque<string> name;
};

/*******************************************
load file only read names
*******************************************/
deque<string> import_file::read_name(char *my_path)
{
	deque<string> name_buf;
	char path[1000];
	char buf[100000];
	char *p;
	string line;
	strcpy(path,my_path);
	ifstream myfile(path);
	if(myfile.is_open())
	{
		getline(myfile,line);
		strcpy(buf,line.c_str());
		p=strtok(buf,",");
		if(strcmp(p,"\"\"")==0)
			p=strtok(NULL,",");
		while(p!=NULL)
		{
			name_buf.push_back(p);
			//cout << p << endl;
			p=strtok(NULL,",");
		}
	}
	return name_buf;
}

/*******************************************
load file and set stop_value
*******************************************/
deque<deque<double> > import_file::read_F(string my_path, int *stop_value)
{
	name.clear();
	deque<deque<double> > matrix_t/*, matrix*/;
	int count=0, sub_count=0;
	//deque<double> row;
	char buf[100000];
	string line;
	char *p;
	char path[1000];
	strcpy(path,my_path.c_str());

	//cout << "input file path" << endl;
	//cin >> path;

	ifstream myfile(path);
	if(myfile.is_open())
	{
		getline(myfile,line);
		//cout << line << endl;
		while(!myfile.eof())
		{
			//row.clear();
			if(count==0)
			{
				strcpy(buf,line.c_str());
				p=strtok(buf,",");
				if(strcmp(p,"\"\"")==0)
					p=strtok(NULL,",");
				while(p!=NULL)
				{
					name.push_back(p);
					//cout << p << endl;
					p=strtok(NULL,",");
				}
				*stop_value=name.size()*name.size();
				for(int i=0;i<name.size();i++)
				{
					deque<double> init;
					init.clear();
					matrix_t.push_back(init);
				}
			}
			else
			{
				sub_count=0;
				strcpy(buf,line.c_str());
				p=strtok(buf,",");
				p=strtok(NULL,",");
				while(p!=NULL)
				{
					//row.push_back(atof(p));
					matrix_t[sub_count].push_back(atof(p));
					//cout << atof(p) << endl;
					p=strtok(NULL,",");
					sub_count++;
				}
				//matrix.push_back(row);
			}
			count++;
			//cout << count << endl;
			getline(myfile,line);
		}
	}
	myfile.close();
	return matrix_t;
}
