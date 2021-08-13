#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int	num = 0;
	char*	str = "02";

	//scanf("%02d", &num);
	sscanf(str, "%02d", &num);
	printf("num = %d\r\n", num);
}
