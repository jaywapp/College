#include <stdio.h>

int main()
{
	int i;

	for(i=0; i<23; i++){
		system("./buzzertest 24");
		usleep(200000);
		system("./buzzertest 19");
		usleep(200000);
	}
	system("./buzzertest 0");
	return 0;
}
