#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "testparams.h"

int
main(int argc, char *argv[])
{
    // Change UID to something different than what was set up in testSetup (2)
    int UID = 4;
    if (UID == testUID) {
        printf(1, "Choose UID different from testUID!\n");
        exit();
    }
    setuid(UID);
    UID = getuid();
    printf(1, "UID changed to %d\n", UID);
    // File Owner (2) and UID (4) are different for all the tests in this file
    // Variables used in the test functions
    int fd;
    char buf[100];
    int res;

    // Testing non protected file
    // -> opening, reading and writing should work, no protection is set

    // Open test file in Write only mode
    //chmod(testNoProtFile, PROT_W);
    fd = open(testNoProtFile, O_WRONLY);
    if (fd < 0) {
        printf(1, "ERROR: Opening testNoProtFile in write only mode failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    close(fd);

    // Open test file in Read only mode
    fd = open(testNoProtFile, O_RDONLY);
    if (fd < 0) {
        printf(1, "ERROR: Opening testNoProtFile in read only mode failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    close(fd);

    // Open test file in Read/Write mode
    fd = open(testNoProtFile, O_RDWR);
    if (fd < 0) {
        printf(1, "ERROR: Opening testNoProtFile in read/write mode failed\n");
        printf(1, "%d\n", fd);
        exit();
    }

    // Read, write and read again from test file
    printf(1, "testNoProtFile content is:\n");
    if((res = read(fd, buf, sizeof(buf))) < 0) {
        printf(1, "Read res is %d\n", res);
        printf(1, "Permission Testfile read failed\n");
        exit();
    }
    printf(1, buf);
    printf(1, "\n");
    if((res = write(fd, "bye", 3) < 0)) {
        printf(1, "Write res is %d\n", res);
        printf(1, "Permission Testfile write failed\n");
        exit();
    }
    if((res = read(fd, buf, sizeof(buf))) < 0) {
        printf(1, "Read res is %d\n", res);
        printf(1, "Permission Testfile read failed\n");
        exit();
    }
    printf(1, buf);
    printf(1, "\n");
    close(fd);


    // Testing read protected file
    // -> opening and reading should not work! Read protection is set!
    // Open test file in Read/Write
    fd = open(testRProtFile, O_RDWR);
    if (fd >= 0) {
        printf(1, "ERROR: Opening testRProtFile in Read/Write mode successful, should fail\n");
        printf(1, "%d\n", fd);
    }
    close(fd);

    // Open test file in Read only mode
    fd = open(testRProtFile, O_RDONLY);
    if (fd >= 0) {
        printf(1, "ERROR: Opening testRProtFile in Read only successful, should fail\n");
        printf(1, "%d\n", fd);
    }
    close(fd);

    // Open test file in Write only mode
    fd = open(testRProtFile, O_WRONLY);
    if (fd < 0) {
        printf(1, "ERROR: Opening testRProtFile in write only mode failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    // Test writing Read protected file
    if((res = write(fd, "bye", 3) < 0)) {
        printf(1, "Write res is %d\n", res);
        printf(1, "Permission Read protected Testfile write failed\n");
        exit();
    }
    close(fd);


    // Testing write protected file
    // -> writing should not work! Writing protection is set!
    // Open test file in Read/Write
    fd = open(testWProtFile, O_RDWR);
    if (fd >= 0) {
        printf(1, "ERROR: Opening testWProtFile in Read/Write mode successful, should fail\n");
        printf(1, "%d\n", fd);
    }
    close(fd);

    // Open test file in Read only mode
    fd = open(testWProtFile, O_WRONLY);
    if (fd >= 0) {
        printf(1, "ERROR: Opening testWProtFile in Write only successful, should fail\n");
        printf(1, "%d\n", fd);
    }
    close(fd);

    // Open test file in Read only mode
    fd = open(testWProtFile, O_RDONLY);
    if (fd < 0) {
        printf(1, "ERROR: Opening testWProtFile in Read only mode failed, should work!\n");
        printf(1, "%d\n", fd);
        exit();
    }
    if((res = read(fd, buf, sizeof(buf))) < 0) {
        printf(1, "Read res is %d\n", res);
        printf(1, "Permission Testfile read failed\n");
        exit();
    }
    printf(1, buf);
    printf(1, "\n");
    close(fd);


    // Testing Read/Write protected file
    // -> opening, reading and writing should not work! All protections are set!
    // Open test file in Read/Write
    fd = open(testRWProtFile, O_RDWR);
    if (fd >= 0) {
        printf(1, "ERROR: Opening testRWProtFile in Read/Write mode successful, should fail\n");
        printf(1, "%d\n", fd);
    }
    close(fd);

    // Open test file in Read only mode
    fd = open(testRWProtFile, O_WRONLY);
    if (fd >= 0) {
        printf(1, "ERROR: Opening testRWProtFile in Write only successful, should fail\n");
        printf(1, "%d\n", fd);
    }
    close(fd);

    // Open test file in Read only mode
    fd = open(testRWProtFile, O_RDONLY);
    if (fd >= 0) {
        printf(1, "ERROR: Opening testRWProtFile in Read only successful, should fail\n");
        printf(1, "%d\n", fd);
    }
    close(fd);

    exit();
} 