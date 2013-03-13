hmmc_clustering
===============

Project for clustering cancer patients based on hidden markov models.


Compilation instructions:

step 1:
	generate an SSH key for github:

	https://help.github.com/articles/generating-ssh-keys

	you should already have one in .ssh/id_rsa.pub (you don't need to
    generate a new one). You can add this to your git account under 
    account settings.

step 2:
	add cmake to your .bashrc

	alias cmake=/share/apps/usrcmake/bin/cmake

	log out and log back in

step 3:
	clone and build the repository:
	git clone ssh://git@github.com/travisdesell/hmmc_clustering.git

	cd hmmc_clustering
	git submodule init
	git submodule update
	git checkout master
	cd tao
	git submodule init
	git submodule update
	git checkout master

	cd ..
	mkdir build
	cd build
	make

step 4:
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
