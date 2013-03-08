#ifndef HMM_H
#define HMM_H

#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <deque>
#include <stdlib.h>
#include "Model.h"

using namespace std;

/*************************************
  Viterbi algorithm for constructing a hiden markov model
 *************************************/
double viterbi(const deque<deque<double> > &obs, const model &m, const deque<deque<deque<double> > > &hmm_emi_list) {
    if (m.pi.size() != m.A.size() || m.pi.size() != m.A[0].size()) {
        cout << "The number of states is not consistent, abort." << endl;
        return 0;
    }

    deque<double> pi=m.pi;
    deque<deque<double> > A = m.A;
    deque<double> states = m.states;

    int N = pi.size();
    int n = obs.size();
    int T = obs[0].size();

    deque<deque<double> > delta;
    deque<int> sta;
    deque<double> tmpdelta;
    deque<int> tmpsta;

    double p_emi;
    double max = -999;
    double max1 = -999;
    int max_index = 0;
    int max_index1 = 0;

    if (n > 1) {
        for (int i = 0; i < N; i++) {
            deque<double> init;
            init.clear();
            delta.push_back(init);
            delta[i].push_back(log(pi[i]));

            for(int j = 0; j < n; j++) {
                p_emi = hmm_emi_list[i][j][0];
                //cout << p_emi << endl;
                delta[i][0] += log(p_emi);
            }
             
            if (i == 0) {
                max=delta[i][0];
            }

            if (delta[i][0] > max) {
                max = delta[i][0];
                max_index = i;
            }
        }

        sta.push_back(max_index);

        for (int s = 1; s < T; s++) {
            tmpsta.clear();

            for (int j = 0; j < N; j++) {
                tmpdelta.clear();
                //max=-999;
                max_index = 0;

                for (int k = 0; k < N; k++) {
                    tmpdelta.push_back(delta[k][s-1] + log(A[k][j]));

                    if (k == 0) max = tmpdelta[k];

                    if(tmpdelta[k] > max) {
                        max = tmpdelta[k];
                        max_index = k;
                    }
                }

                tmpsta.push_back(max_index);
                delta[j].push_back(max);

                for (int k = 0; k < n; k++) {
                    p_emi = hmm_emi_list[j][k][s];
                    delta[j][s] += log(p_emi);
                }

                if (j == 0) max1=delta[j][s];

                if (delta[j][s] > max1) {
                    max1 = delta[j][s];
                    max_index1 = j;
                }
            }

            sta.push_back(max_index1);

            if ((int)sta[s] < tmpsta.size()) sta[s-1] = tmpsta[sta[s]];
            //else
            //	sta[s-1]=NULL;				//NULL value here
        }

    } else if (n == 1) {
        for (int i = 0; i < N; i++) {
            deque<double> init;
            init.clear();

            delta.push_back(init);
            delta[i].push_back(log(pi[i]));

            p_emi = hmm_emi_list[i][0][0];
            delta[i][0] += log(p_emi);

            if (i == 0) max = delta[i][0];

            if (delta[i][0] > max) {
                max = delta[i][0];
                max_index = i;
            }
        }

        sta.push_back(max_index);

        for (int s = 1; s < T; s++) {
            tmpsta.clear();

            for (int j = 0; j < N; j++) {
                tmpdelta.clear();

                //max=-999;
                max_index=0;

                for(int k = 0; k < N; k++) {
                    tmpdelta.push_back(delta[k][s-1] + log(A[k][j]));

                    if (k==0) max = tmpdelta[k];

                    if (tmpdelta[k] > max) {
                        max = tmpdelta[k];
                        max_index = k;
                    }
                }

                tmpsta.push_back(max_index);
                delta[j].push_back(max);

                p_emi = hmm_emi_list[j][0][s];
                delta[j][s] += log(p_emi);

                if (j == 0) max1=delta[j][s];

                if (delta[j][s] > max1) {
                    max1 = delta[j][s];
                    max_index1 = j;
                }
            }

            sta.push_back(max_index1);

            if ((int)sta[s] < tmpsta.size()) sta[s-1] = tmpsta[sta[s]];
            //else
            //	sta[s-1]=NULL;				//NULL value here
        }
    } else {
        return 0;
    }

    return delta[sta[T-1]][T-1];
}

#endif
