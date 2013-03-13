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
	git clone ssh://git@github.com/travisdesell/tomography.git

	cd tomography
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

