#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <vector>
#include "Hmmc.h"
#include "mpi.h"

/**
 *  From tao 
 */
#include "tao/mpi/mpi_genetic_algorithm.hxx"

/**
 *  From tao/undvc_common
 */
#include "undvc_common/arguments.hxx"


using namespace std;

int row_count;

vector<int> random_encoding() {
    vector<int> encoding(row_count);

    for (int i = 0; i < row_count; i++) {
        encoding[i] = rand() % 3;
    }

    return encoding;
}

vector<int> mutate(const vector<int> &encoding) {
    vector<int> mutation(encoding);

    for (int i = 0; i < 3; i++) {
        int position = rand() % mutation.size();
        switch (mutation[position]) {
            case 0: mutation[position] = 1 + (rand() % 2); break;
            case 1: if (rand() % 2) {
                        mutation[position] = 0;
                    } else {
                        mutation[position] = 2;
                    }
                    break;
            case 2: mutation[position] = (rand() % 2); break;
            default:
                    cerr << "Error, unknown grouping: " << mutation[position] << endl;
                    break;
        }
    }

    return mutation;
}

double crossover_rate = 0.5;
bool binary_recombination = true;

vector<int> crossover(const vector<int> &parent1, const vector<int> &parent2) {
    vector<int> child(parent1);

    if (binary_recombination) {
        //Guarantee at least something is taken from the second parent
        int position = rand() % child.size();
        child[position] = parent2[position];

        for (int i = 0; i < child.size(); i++) {
            if (drand48() < crossover_rate) {
                child[i] = parent2[i];
            }
        }

    } else {    //exponential recombination
        int position = rand() % child.size();

        for (int i = position; i < child.size(); i++) {
            child[i] = parent2[i];
        }
    }

    return child;
}


int main(int argc, char **argv) {
    /**
     *  Initialize MPI
     */
    MPI_Init(&argc, &argv);

    //int n_processes;    //the number of MPI processes
    int rank;           //this process rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //cout << "number of processes: " << n_processes << endl;
    //cout << "process rank       : " << rank << endl;

    // convert the arguments to a vector of strings
    vector<string> arguments(argv, argv + argc);

    //Seed the program once on *EACH* processor -- each seed needs to be different
    srand48(time(NULL) + rank);
    srand(time(NULL) + rank);

    n_groups = -1;
	string input_filename;

    //get_argument is in undvc_common/arguments.hxx, and parses the command line.
    //the boolean argument is whether or not the argument is required (it will quit
    //and print an error message if it is not specified the field is true).
    get_argument(arguments, "--n_groups", true, n_groups);
    get_argument(arguments, "--input_file", true, input_filename);

    if (n_groups < 0) {
        cerr << "Error, must specify a number of groups (clusters) with the flag: '--n_groups <number of clusters>'" << endl;
        exit(1);
    }

    if (input_filename.compare("") == 0) {
        cerr << "Error, must specify an input filename with the flag: '--file <input filename>'" << endl;
        exit(1);
    }

	import_file ifi;
	int stop_value;

	deque<deque<double> > d = ifi.read_F(input_filename, &stop_value);

	double prob = 0.9;

	row_count = initialize_hmm_c(n_groups, prob, d);

    GeneticAlgorithmMPI ga_mpi(arguments, row_count, random_encoding, mutate, crossover);
    ga_mpi.go(calculate_clustering_fitness);

    MPI_Finalize();

	return 0;
}
