#include<stdio.h>
int main()
{
	printf("my pid=%d, my parent pid=%d\n",getpid(),getppid());
	fork();
	fork();
	/*
 	OR
  		for(i=0;i<2;i++)
		fork();
	*/
	wait(NULL);
	printf("my pid=%d, my parent pid=%d\n",getpid(),getppid());
	

return 0;
}
/*
 *
 * my pid=2648, my parent pid=1853
 * my pid=2650, my parent pid=2648
 * my pid=2651, my parent pid=2649
 * my pid=2649, my parent pid=2648
 * my pid=2648, my parent pid=1853
 */

