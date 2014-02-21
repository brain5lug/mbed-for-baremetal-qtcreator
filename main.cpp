#include "mbed.h"
 
DigitalOut myled(LED1);
 
int main() {
	while(1) {
		myled = 1;
		wait(0.2);
		myled = 0;
		wait(0.2);
	}
}

extern "C" {
void _exit(int code)
{
    while(1);

}

int kill(int pid, int sig)
{
    _exit(sig);

    return 0;
}

/*
* getpid -- only one process, so just return 1.
*/
#define __MYPID 1
int _getpid()
{
return __MYPID;
}

/*
* kill -- go out via exit...
*/
int _kill(int pid, int sig)
{

return -1;
}
char *heap_end = 0;
caddr_t _sbrk(int incr) {
 extern char heap_low; /* Defined by the linker */
 extern char heap_top; /* Defined by the linker */
 char *prev_heap_end;
 
 if (heap_end == 0) {
  heap_end = &heap_low;
 }
 prev_heap_end = heap_end;
 
 if (heap_end + incr > &heap_top) {
  /* Heap and stack collision */
  return (caddr_t)0;
 }
 
 heap_end += incr;
 return (caddr_t) prev_heap_end;
}
}
