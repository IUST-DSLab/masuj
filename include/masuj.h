#ifndef MASUJ_H_
#define MASUJ_H_

#define MAX_SUB_JOBS 16

class SubJob;

class MainJob
{
	unsigned long long id;

	unsigned long long sub_jobs_id[MAX_SUB_JOBS];
	SubJob* sub_jobs;
	size_t number_of_sub_jobs;

	/**
	 * Repeats: spawns the subsidiary jobs then waits for synchronization.
	 * The spawn stage, uses scheduler to dispatch subsidiary jobs to available resources (job scheduler employs various
	 * scheduling policies).
	 * */
	bool (*func)(unsigned char* data, size_t size, unsigned char* res, size_t res_size);
};

class SubJob
{
	unsigned long long id;

	unsigned long long main_job_id;
	MainJob* main_job;

	/**
	 * Executes a round of CPU-intensive computation.
	 * */
	bool (*func)(unsigned char* data, size_t size, unsigned char* res, size_t res_size);
}

class Job
{
	MainJob* main_job;
	SubJob* sub_jobs[MAX_SUB_JOBS];
	size_t number_of_sub_jobs;
};

#endif
