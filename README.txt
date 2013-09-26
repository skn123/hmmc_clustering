hmmc_clustering
===============

Project for clustering cancer patients based on hidden markov models.

Compilation instructions:

Step 1: Make a github account.

Step 2: Go to your github account settings and add your PUBLIC ssh key:
This can be found in:

~/.ssh/id_rsa.pub

On hodor.

Step 3: Clone the repository:

git clone ssh://git@github.com/travisdesell/hmmc_clustering.git

Step 4: Check out the submodules:

    cd hmmc_clustering
    git submodule init
    git submodule update
    git checkout master
    cd tao
    git submodule init
    git submodule update
    git checkout master

step 5:
	add cmake to your .bashrc

	alias cmake=/share/apps/usrcmake/bin/cmake

	log out and log back in

Step 6: Compile:

    cd ..
    mkdir build
    cd build
    cmake ..
    make

step 7:
	Run:

	For two processes (master/worker) for testing:
		mpirun -np 2 ./hmmc --n_groups 3 --input_file ../data/AST79.csv

	To run on hodor, you can use the hodor_submit.pbs script.  You'll need to update this for your home directory and own email.
	The hmmc_clustering directory needs to be in your home directory, eg: ~/hmmc_clustering

	Then submit with:
		sub hodor_submit.pbs

	You can track the job status with:
		qstat -a

	It will also email you when your job starts running and when it completes.  The output will be in:
	~/hmmc_clustering/build/hmmc_out.txt
	and
	~/hmmc_clustering/build/hmmc_error.txt
