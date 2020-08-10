#include <stdio.h>

int main(){

	int i;

	for (i=0; i<23; i++)
	{
		system("./buzzertest 24");
		usleep(200000);
		system("./buzzertest 0");
		usleep(200000);
	}	
	return 0;

}
