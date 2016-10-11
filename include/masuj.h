#ifndef MASUJ_H_
#define MASUJ_H_

#define MAX_SUB_JOBS 16

struct SubJob;

struct MainJob
{
	unsigned long long id;

	unsigned long long sub_jobs_id[MAX_SUB_JOBS];
	struct SubJob* sub_jobs;
	size_t number_of_sub_jobs;

	/**
	 * Repeats: spawns the subsidiary jobs then waits for synchronization.
	 * The spawn stage, uses scheduler to dispatch subsidiary jobs to available resources (job scheduler employs various
	 * scheduling policies).
	 * */
	bool (*func)(unsigned char* data, size_t size, unsigned char* res, size_t res_size);
};

struct SubJob
{
	unsigned long long id;

	unsigned long long main_job_id;
	struct MainJob* main_job;

	/**
	 * Executes a round of CPU-intensive computation.
	 * */
	bool (*func)(unsigned char* data, size_t size, unsigned char* res, size_t res_size);
}

struct Job
{
	struct MainJob* main_job;
	struct SubJob* sub_jobs[MAX_SUB_JOBS];
	size_t number_of_sub_jobs;
};

#endif
