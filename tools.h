#include "sys/time.h"
#include "stdlib.h"

struct timeval t1, t2;
#define start_time()	do { gettimeofday(&t1, NULL); } while(0)
#define stop_time()	do { gettimeofday(&t2, NULL); printf("time diff = %ld\r\n", \
	t2.tv_sec*1000 + t2.tv_usec/1000 - (t1.tv_sec*1000 + t1.tv_usec/1000)); } while (0)

#if 0
inline void create_nums(int* nums, int num, int min, int max)
{
	int	limit = max - min;
	struct timeval t;

	gettimeofday(&t, NULL);
	srandom(t.tv_usec);
	for (int i = 0; i < num; ++i) {
		nums[i] = random()%(limit+1) + min;
	}
}
#endif

#define create_nums(nums, num, min, max)	do {\
	int	limit = max - min;\
	struct timeval t; \
\
	gettimeofday(&t, NULL); \
	srandom(t.tv_usec);	\
	for (int i = 0; i < num; ++i) {	\
		nums[i] = random()%(limit+1) + min; \
	} \
} while (0)
