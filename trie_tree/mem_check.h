#ifdef __MEM_CHECK_H__
#define __MEM_CHECK_H__

void memcheck_init();
void* my_calloc(int size, int num);
void my_free(void* addr);
void memcheck_deinit();
void memcheck_show();

#endif //__MEM_CHECK_H__
