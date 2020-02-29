#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*orig_dst;

	orig_dst = dst;
	while (n > sizeof(unsigned long))
	{
		*(unsigned long *)dst = *(unsigned long *)src;
		dst = ((unsigned long *)dst) + 1;
		src = ((unsigned long *)src) + 1;
		n -= sizeof(unsigned long);
	}
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst = ((unsigned char *)dst) + 1;
		src = ((unsigned char *)src) + 1;
		n -= sizeof(unsigned char);
	}
	return (orig_dst);
}

#define SIZE (1000*1000*1000)
#define MEMCPY ft_memcpy

int main()
{
	size_t	before;
	size_t	after;
	int 	fd;
	void	*dst;
	void	*src;

	fd = open("/dev/random", O_RDONLY);
	dst = malloc(SIZE + 100);
	src = malloc(SIZE + 100);
	read(fd, src, SIZE + 100);
	close(fd);

	before = clock();
	MEMCPY(dst, src, SIZE);
	after = clock();
	printf("Both aligned: %zu, res: %d\n", after - before, memcmp(dst, src, SIZE));

	before = clock();
	MEMCPY(((unsigned char *)dst) + 3, src, SIZE);
	after = clock();
	printf("Src aligned: %zu, res: %d\n", after - before, memcmp(((unsigned char *)dst) + 3, src, SIZE));

	before = clock();
	MEMCPY(dst, ((unsigned char *)src) + 3, SIZE);
	after = clock();
	printf("Dst aligned: %zu, res: %d\n", after - before, memcmp(dst, ((unsigned char *)src) + 3, SIZE));

	free(src);
	free(dst);
	return (0);
}
