#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void	test_cpy(size_t size, size_t dshift, size_t sshift)
{
	void	*dst;
	void	*src;
	size_t	before;
	size_t	after;

	dst = malloc(size + 100);
	src = malloc(size + 100);
	memset(dst, 0x00, size + 100);
	memset(src, 0x00, size + 100);
	//*(unsigned char *)dst = 0;
	//*(unsigned char *)src = 0;

	before = clock();
	MEMCPY(((unsigned char *)dst) + dshift, ((unsigned char *)src) + sshift, size);
	after = clock();
	printf("dshift: %zu, sshift: %zu, time: %zu, res: %d, word_size: %zu\n",
		dshift, sshift, after - before,
		memcmp(((unsigned char *)dst) + dshift, ((unsigned char *)src) + sshift, size),
		sizeof(word));
	free(dst);
	free(src);
}

int main()
{
	test_cpy(SIZE, 0, 0);
	test_cpy(SIZE, 3, 0);
	test_cpy(SIZE, 0, 3);
	test_cpy(SIZE, 2, 3);
	return (0);
}
