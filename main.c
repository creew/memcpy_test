#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SIZE (1000*1000*1000)
#define MEMCPY ft_memcpy
typedef unsigned long word;

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*orig_dst;

	orig_dst = dst;
	while (n > sizeof(word))
	{
		*(word *)dst = *(word *)src;
		dst = ((word *)dst) + 1;
		src = ((word *)src) + 1;
		n -= sizeof(word);
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

void test_memcpy(void *dst, void *src, size_t size)
{
	size_t	before;
	size_t	after;

	before = clock();
	MEMCPY(dst, src, size);
	after = clock();
	printf("Both aligned: %zu, res: %d, word_size: %zu\n", after - before, memcmp(dst, src, size), sizeof(word));

	before = clock();
	MEMCPY(((unsigned char *)dst) + 3, src, size);
	after = clock();
	printf("Src aligned: %zu, res: %d, word_size: %zu\n", after - before, memcmp(((unsigned char *)dst) + 3, src, size), sizeof(word));

	before = clock();
	MEMCPY(dst, ((unsigned char *)src) + 3, size);
	after = clock();
	printf("Dst aligned: %zu, res: %d, word_size: %zu\n", after - before, memcmp(dst, ((unsigned char *)src) + 3, size), sizeof(word));

	before = clock();
	MEMCPY(((unsigned char *)dst) + 2, ((unsigned char *)src) + 3, size);
	after = clock();
	printf("Both non-aligned: %zu, res: %d, word_size: %zu\n", after - before, memcmp(((unsigned char *)dst) + 2, ((unsigned char *)src) + 3, size), sizeof(word));
}

int main()
{
	int 	fd;
	void	*dst;
	void	*src;

	fd = open("/dev/random", O_RDONLY);
	dst = malloc(SIZE + 100);
	src = malloc(SIZE + 100);
	read(fd, src, SIZE + 100);
	close(fd);
	test_memcpy(dst, src, SIZE);
	free(src);
	free(dst);
	return (0);
}
