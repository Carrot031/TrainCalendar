#include <stdio.h>
#include <stdlib.h>

int count_spaces(char* buf)
{
	int count = 0;
	while(1)
	{
		char c = *buf++;
		if(c == ' ')
		{
			count++;
		}
		if(c == '\0')
		{
			return count;
		}
	}
}

int main()
{
	char* buf = malloc(256);
	fgets(buf,256,stdin);
	printf("The sentence countains %d words\n",count_spaces(buf)+1);
	return 0;
}
