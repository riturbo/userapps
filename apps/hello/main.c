#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <dfs_poll.h>
#include <include/drivers/input_uapi.h>

int main(void)
{
    int fd;
    char name[32] = {0};
    struct pollfd pfd;
    struct input_event ev;

    fd = open("/dev/input0", O_RDONLY);
    if (fd < 0)
    {
        perror("open /dev/input0");
        return 1;
    }

    if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) == 0)
    {
        printf("device: %s\n", name);
    }

    pfd.fd = fd;
    pfd.events = POLLIN;

    while (1)
    {
        int ret = poll(&pfd, 1, -1);
        if (ret < 0)
        {
            perror("poll");
            break;
        }

        if (pfd.revents & POLLIN)
        {
            ssize_t n = read(fd, &ev, sizeof(ev));
            if (n == sizeof(ev))
            {
                printf("type=%u code=0x%02x value=%d time=%ld.%06ld\n",
                       ev.type, ev.code, ev.value,
                       (long)ev.time.tv_sec, (long)ev.time.tv_usec);
            }
        }
    }

    close(fd);
    return 0;
}
