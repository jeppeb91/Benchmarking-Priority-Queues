#!/bin/bash

#Run benchmarks with highest priorities using specified input file and output data
sudo nice -n -20 ./bin/skew_heap_inserts "dists/unif09-11.txt" > out/skew/inserts_unif09-11.dat
sudo nice -n -20 ./bin/skew_heap_inserts "dists/triangular.txt" > out/skew/inserts_triangular.dat
sudo nice -n -20 ./bin/skew_heap_inserts "dists/exponential1.txt" > out/skew/inserts_exponential.dat


#Run benchmarks with highest priorities using specified input file and output data
sudo nice -n -20 ./bin/linked_list_inserts "dists/unif09-11.txt" > out/linked/inserts_unif09-11.dat
sudo nice -n -20 ./bin/linked_list_inserts "dists/triangular.txt" > out/linked/inserts_triangular.dat
sudo nice -n -20 ./bin/linked_list_inserts "dists/exponential1.txt" > out/linked/inserts_exponential.dat


#Run benchmarks with highest priorities using specified input file and output data
sudo nice -n -20 ./bin/skew_heap_pops "dists/unif09-11.txt" > out/skew/pops_unif09-11.dat
sudo nice -n -20 ./bin/skew_heap_pops "dists/triangular.txt" > out/skew/pops_triangular.dat
sudo nice -n -20 ./bin/skew_heap_pops "dists/exponential1.txt" > out/skew/pops_exponential.dat

#Run benchmarks with highest priorities using specified input file and output data
sudo nice -n -20 ./bin/linked_list_pops "dists/unif09-11.txt" > out/linked/pops_unif09-11.dat
sudo nice -n -20 ./bin/linked_list_pops "dists/triangular.txt" > out/linked/pops_triangular.dat
sudo nice -n -20 ./bin/linked_list_pops "dists/exponential1.txt" > out/linked/pops_exponential.dat

#Plot the results

gnuplot << EOF

	set terminal png
	set key left top

	set xlabel "Queue size"
	set ylabel"Insertion time (µs)"

	set xrange [0:9000]
	set yrange [0:800]

	set output './graphs/Skew_inserts.png'
	set title "Benchmarking Skew heap inserts"

	plot	"./out/skew/inserts_triangular.dat" u 1:2 w lines title "triangular", \
		"./out/skew/inserts_exponential.dat" u 1:2 w lines title "exponential", \
		"./out/skew/inserts_unif09-11.dat" u 1:2 w lines title "uniform0.9-1.1"
EOF

gnuplot << EOF
	
	set terminal png
	set key left top

	set xlabel "Queue size"
	set ylabel"Insertion time (µs)"

	set xrange [0:10000]
	set yrange [0:70000]

	set output './graphs/Linked_list_inserts.png'
	set title "Benchmarking Linked list inserts"

	plot	"./out/linked/inserts_triangular.dat" u 1:2 w lines title "triangular", \
		"./out/linked/inserts_exponential.dat" u 1:2 w lines title "exponential", \
		"./out/linked/inserts_unif09-11.dat" u 1:2 w lines title "uniform0.9-1.1"
	
EOF

gnuplot << EOF
	
	set terminal png
	set key right top

	set xlabel "Queue size"
	set ylabel"Insertion time (µs)"

	set xrange [0:9000]
	set yrange [0:5000]

	set output './graphs/Insertion_comparison.png'
	set title "Linked list vs Skew heap insertions"

	plot	"./out/linked/inserts_triangular.dat" u 1:2 w lines title "linked triangular", \
		"./out/linked/inserts_exponential.dat" u 1:2 w lines title "linked exponential", \
		"./out/linked/inserts_unif09-11.dat" u 1:2 w lines title "linked uniform0.9-1.1", \
		"./out/skew/inserts_triangular.dat" u 1:2 w lines title "skew triangular", \
		"./out/skew/inserts_exponential.dat" u 1:2 w lines title "skew exponential", \
		"./out/skew/inserts_unif09-11.dat" u 1:2 w lines title "skew uniform0.9-1.1"	
EOF



gnuplot << EOF

	set terminal png
	set key left top

	set xlabel "Queue size"
	set ylabel"Removal time (µs)"

	set xrange [0:10000]
	set yrange [0:2000]

	set output './graphs/Skew_pops.png'
	set title "Benchmarking Skew heap pops"

	plot	"./out/skew/pops_triangular.dat" u 1:2 w lines title "triangular", \
		"./out/skew/pops_exponential.dat" u 1:2 w lines title "exponential", \
		"./out/skew/pops_unif09-11.dat" u 1:2 w lines title "uniform0.9-1.1"
EOF

gnuplot << EOF
	
	set terminal png
	set key left top

	set xlabel "Queue size"
	set ylabel"Removal time (µs)"

	set xrange [0:10000]
	set yrange [0:300]

	set output './graphs/Linked_list_pops.png'
	set title "Benchmarking Linked list pops"

	plot	"./out/linked/pops_triangular.dat" u 1:2 w lines title "triangular", \
		"./out/linked/pops_exponential.dat" u 1:2 w lines title "exponential", \
		"./out/linked/pops_unif09-11.dat" u 1:2 w lines title "uniform0.9-1.1"
	
EOF

gnuplot << EOF
	
	set terminal png
	set key right top

	set xlabel "Queue size"
	set ylabel"Removal time (µs)"

	set xrange [0:10000]
	set yrange [0:2000]

	set output './graphs/Pops_comparison.png'
	set title "Linked list vs Skew heap pops"

	plot	"./out/linked/pops_triangular.dat" u 1:2 w lines title "linked triangular", \
		"./out/linked/pops_exponential.dat" u 1:2 w lines title "linked exponential", \
		"./out/linked/pops_unif09-11.dat" u 1:2 w lines title "linked uniform0.9-1.1", \
		"./out/skew/pops_triangular.dat" u 1:2 w lines title "skew triangular", \
		"./out/skew/pops_exponential.dat" u 1:2 w lines title "skew exponential", \
		"./out/skew/pops_unif09-11.dat" u 1:2 w lines title "skew uniform0.9-1.1"	
EOF
