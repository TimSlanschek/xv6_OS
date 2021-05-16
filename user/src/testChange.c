#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "testparams.h"

int
main(int argc, char *argv[])
{
    setuid(testUID);
    int UID = getuid();
    printf(1, "Current UID is %d\n", UID);

    // Testing file owner change
    int owner = getown(testChangeFile);
    printf(1, "Owner of the file is uid %d\n", owner);

    // Testing permission change
    int perms = getmod(testChangeFile);
    printf(1, "Permissions of the file are %d\n", perms);

    // Testing file creation and write
    int fd;
    fd = open(testChangeFile, O_RDWR);
    if (fd < 0) {
        printf(1, "ERROR: open testfile failed\n");
        exit();
    }

    printf(1, "testfile content is:\n");
    char buf[100];
    int res;
    if((res = read(fd, buf, sizeof(buf))) != 5) {
        printf(1, "Read res is %d\n", res);
        printf(1, "Testfile read failed\n");
        exit();
    }
    printf(1, buf);
    printf(1, "\n");
    close(fd);

    exit();
} 