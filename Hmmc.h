#ifndef HMMC_H
#define HMMC_H

#include <iostream>
#include <deque>
#include <vector>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "Connect.h"
#include "Hmm.h"

using namespace std;

connect *connection;
int n_groups;
double logL_opt;
deque<double> clust_opt;
deque<deque<double> > d;

double calculate_clustering_fitness(const vector<int> &clustering) {
    deque<deque<double> > obs;

    /*
    cout << "clustering.size(): " << clustering.size() << endl;
    for (int j = 0; j < clustering.size(); j++) {
        cout << " " << clustering[j];
    }
    cout << endl;
    */

    double logL = 0;
    for (int i = 0; i < n_groups; i++) {
        int count = 0;

        for (int j = 0; j < clustering.size(); j++) {
            if (clustering[j] == i) count++;
        }

        if (count > 0) {
            obs = d;

            int tp = 0;
            for(int j = 0; j < clustering.size(); j++) {
                if (clustering[j] != i) {
                    obs.erase(obs.begin() + (j - tp));
                    tp++;
                }
            }

            deque<deque<deque<double> > > emi = connection->emi_all;
            for(int j = 0; j < connection->n_states; j++) {
                int tp = 0;

                for(int k = 0; k < clustering.size(); k++) {
                    if (clustering[k] != i) {
                        emi[j].erase(emi[j].begin() + (k - tp));
                        tp++;
                    }
                }
            }

            logL += viterbi(obs, connection->m, emi);
        }
    }
    
    return logL;
}


int initialize_hmm_c(int _n_groups, double prob, const deque<deque<double> > &_d) {
    connection = new connect(prob);
    connection->conn(_d);
    d = connection->file_buf;     //Why is d being reset here?
    n_groups = _n_groups;

    return connection->file_buf.size();
}

#endif
