// ------------
// This code is provided solely for the personal and private use of
// students taking the CSC367 course at the University of Toronto.
// Copying for purposes other than this use is expressly prohibited.
// All forms of distribution of this code, whether as given or with
// any changes, are expressly prohibited.
//
// Authors: Bogdan Simion, Maryam Dehnavi, Alexey Khrabrov
//
// All of the files in this directory and all subdirectories are:
// Copyright (c) 2020 Bogdan Simion and Maryam Dehnavi
// -------------

#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "join.h"
#include "options.h"
#include "hash.h"


/* Fragment-and-replicate implementation */
int fragment_replicate(int opt_nthreads,
	const student_record *students,
	int students_count,
	const ta_record *tas,
	int tas_count,
	join_func_t *join_f) {

	int count = 0;

	// Always partition on the larger table to get better performance
	if (tas_count >= students_count) {
			dummyMethod1();
		#pragma omp parallel for reduction(+:count)
		for (int t = 0; t < opt_nthreads; ++t) {
			int start = t * (tas_count / opt_nthreads);
			int end = (t + 1) * (tas_count / opt_nthreads);
			if (t == opt_nthreads - 1) {
				end = tas_count;
			}
			count += join_f(students, students_count, tas + start, end - start);
		}
			dummyMethod2();
	} else {
			dummyMethod1();
		#pragma omp parallel for reduction(+:count)
		for (int s = 0; s < opt_nthreads; ++s) {
			int start = s * (students_count / opt_nthreads);
			int end = (s + 1) * (students_count / opt_nthreads);
			if (s == opt_nthreads - 1) {
				end = students_count;
			}
			count += join_f(students + start, end - start, tas, tas_count);
		}
			dummyMethod2();

	}

	return count;
}

/* Symmetric partitioning implementation */
int symmetric_partitioning(int opt_nthreads,
	const student_record *students,
	int students_count,
	const ta_record *tas,
	int tas_count,
	join_func_t *join_f) {

	int count = 0;

	int min_sid = students[0].sid;
	int max_sid = students[students_count - 1].sid;

	dummyMethod1();
	#pragma omp parallel for reduction(+: count)
	for(int i = 0; i < opt_nthreads; ++i) {
		// Partition on the student sid
		int start_sid = i * ((max_sid - min_sid + 1) / opt_nthreads) + min_sid; // inclusive
		int end_sid = (i + 1) * ((max_sid - min_sid + 1) / opt_nthreads) + min_sid; // exclusive
		if (i == opt_nthreads - 1) {
			end_sid = max_sid + 1;
		}

		// Look for upper and lower indices of the TA table corresponding to the upper and lower sids
		// this thread got assigned to
		int ta_start = -1; // inclusive
		int ta_end = -1; // exclusive

		int t = 0;
		while (t < tas_count && tas[t].sid < end_sid) {
			if (ta_start == -1 && tas[t].sid >= start_sid) {
				ta_start = t;
			}
			t ++;
		}
		ta_end = t;

		// Look for upper and lower indices of the Students table corresponding to the upper and lower sids
		// this thread got assigned to. Can do it this way because the sid is unique and therefore indeces and
		// sids are one-to-one.
		int student_start = i * (students_count / opt_nthreads);
		int student_end = (i + 1) * (students_count / opt_nthreads);
		if (i == opt_nthreads - 1) student_end = students_count;

		count += join_f(students + student_start, student_end - student_start, tas + ta_start, ta_end - ta_start);

	}
	dummyMethod2();
	return count;
}

int main(int argc, char *argv[])
{
	const char *path = parse_args(argc, argv);
	if (path == NULL) return 1;

	if (!opt_replicate && !opt_symmetric) {
		fprintf(stderr, "Invalid arguments: parallel algorithm (\'-r\' or \'-s\') is not specified\n");
		print_usage(argv);
		return 1;
	}

	if (opt_nthreads <= 0) {
		fprintf(stderr, "Invalid arguments: number of threads (\'-t\') not specified\n");
		print_usage(argv);
		return 1;
	}
	omp_set_num_threads(opt_nthreads);

	int students_count, tas_count;
	student_record *students;
	ta_record *tas;
	if (load_data(path, &students, &students_count, &tas, &tas_count) != 0) return 1;

	int result = 1;
	join_func_t *join_f = opt_nested ? join_nested : (opt_merge ? join_merge : join_hash);

	double t_start = omp_get_wtime();

	// Parallel join using OpenMP
	int count = -1;
	if (opt_replicate) {
		count = fragment_replicate(opt_nthreads, students, students_count, tas, tas_count, join_f);
	} else if (opt_symmetric) {
		count = symmetric_partitioning(opt_nthreads, students, students_count, tas, tas_count, join_f);
	}

	double t_end = omp_get_wtime();

	if (count < 0) goto end;
	printf("%d\n", count);
	printf("%f\n", (t_end - t_start) * 1000.0);
	result = 0;

end:
	free(students);
	free(tas);
	return result;
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}