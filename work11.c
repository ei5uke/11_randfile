#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int return_random()
{
    int fd, *buff, a;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
    {
        printf("Open /dev/urandom failed: %d, %s\n", errno, strerror(errno));
        return -1;
    }

    a = read(fd, buff, sizeof(buff));
    if (a == -1)
    {
        printf("Read fd failed: %d, %s\n", errno, strerror(errno));
        return -1;
    }

    close(fd);
    return *buff;
}

int main()
{
    int ray[10], dupe[10]; //arrays of the random #s
    int copy, w, r;           //file descriptors
    int i;             //iterate through the loop
    printf("Generating random numbers:\n");
    for (i = 0; i < 10; i++)
    {
        ray[i] = return_random();
        printf("\trandom %d: %d\n", i, ray[i]);
    }

    copy = open("copy.txt", O_WRONLY | O_CREAT, 0660);
    if (copy == -1)
    {
        printf("Open copy.txt failed: %d, %s\n", errno, strerror(errno));
        return -1;
    }

    printf("Writing numbers to file\n");

    w = write(copy, ray, sizeof(ray));
    if (w == -1)
    {
        printf("Write copy failed: %d, %s\n", errno, strerror(errno));
        return -1;
    }
    close(copy);

    r = open("copy.txt", O_RDONLY);
    if (r == -1)
    {
        printf("Write copy failed: %d, %s\n", errno, strerror(errno));
        return -1;
    }

    printf("Copying numbers into new array\n");
    read(r, dupe, sizeof(dupe));

    printf("Printing copied numbers:\n");
    for (i = 0; i < 10; i++)
    {
        printf("\tcopy %d: %d\n", i, dupe[i]);
    }

    close(copy);
    return 0;
}