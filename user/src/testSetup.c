#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "testparams.h"

int
main(int argc, char *argv[])
{
    //
    // Test setting and getting of UID
    //

    printf(1, "\n");
    printf(1, "\n");
    printf(1, "Setting/Getting UID Test Start \n");
    printf(1, "\n");
    printf(1, "\n");

    int rc = -1;
    int UID = testUID;
    rc = setuid(UID);
    printf(1, "Setting UID to %d\n", UID);

    if (rc < 0) {
        printf(1, "ERROR: setuid failed\n");
        exit();
    }
    rc = getuid();
    if (rc < 0) {
        printf(1, "ERROR: getuid failed\n");
        exit();
    }
    printf(1,"Parent UID = %d\n",rc);

    //
    // Test changing file owner and permissions
    //
    printf(1, "\n");
    printf(1, "\n");
    printf(1, "Changing file owner/persmissions Test Start \n");
    printf(1, "\n");
    printf(1, "\n");

    int fd = open(testChangeFile, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf(1, "ERROR: Creating testfile failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    printf(1, "File created successfully\n");
    write(fd, "hello", 5);
    printf(1, "File written to successfully\n");
    close(fd);

    int new_own = UID;
    if (chown(testChangeFile, new_own) < 0) {
        printf(1, "ERROR: Setting owner failed\n");
        exit();
    }
    printf(1, "Owner for change/persistence test set to %d\n", new_own);

    int new_perms = PROT_W;
    if (chmod(testChangeFile, new_perms) < 0) {
        printf(1, "ERROR: Setting permissions failed\n");
        exit();
    }
    printf(1, "Permissions for change/persistence test set to %d, write protected\n", new_perms);

    //
    // Set up Permissions Test
    //
    printf(1, "\n");
    printf(1, "\n");
    printf(1, "Permission Test Start \n");
    printf(1, "\n");
    printf(1, "\n");

    // Create the No Protection test file
    fd = open(testNoProtFile, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf(1, "ERROR: Creating testNoProtFile failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    close(fd);

    // Setting testfile owner to UID
    if (chown(testNoProtFile, testUID) < 0) {
        printf(1, "ERROR: Setting owner failed\n");
        exit();
    }
    printf(1, "Owner Read Protection test file set to %d\n", testUID);

    printf(1, "Initial Permission after creating the file are %d, should be 0\n", getmod(testNoProtFile));
    // Setting testfile permissions to no permissions
    if (chmod(testNoProtFile, PROT_RW) < 0) {
        printf(1, "ERROR: Setting permissions failed\n");
        exit();
    }
    printf(1, "Permissions for No Protection test set to %d, no protection\n", getmod(testNoProtFile));
    printf(1, "\n", 0);

    // Create the Read Protection test file
    fd = open(testRProtFile, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf(1, "ERROR: Creating testRProtFile failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    close(fd);

    // Setting testfile owner to UID
    if (chown(testRProtFile, testUID) < 0) {
        printf(1, "ERROR: Setting owner failed\n");
        exit();
    }
    printf(1, "Owner for Read Protection test file set to %d\n", getown(testRProtFile));

    printf(1, "Initial Permission after creating the file are %d, should be 0\n", getmod(testRProtFile));
    // Setting testfile permissions to no permissions
    if (chmod(testRProtFile, PROT_W) < 0) {
        printf(1, "ERROR: Setting permissions failed\n");
        exit();
    }
    printf(1, "Permissions for Read Protection test set to %d, read protection\n", getmod(testRProtFile));
    printf(1, "\n", 0);

    // Create the Write Protection test file
    fd = open(testWProtFile, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf(1, "ERROR: Creating testWProtFile failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    write(fd, "W_ProtFile", 10);
    close(fd);

    // Setting testfile owner to UID
    if (chown(testWProtFile, testUID) < 0) {
        printf(1, "ERROR: Setting owner failed\n");
        exit();
    }
    printf(1, "Owner for Write Protection test file set to %d\n", getown(testWProtFile));

    printf(1, "Initial Permission after creating the file are %d, should be 0\n", getmod(testWProtFile));
    // Setting testfile permissions to no permissions
    if (chmod(testWProtFile, PROT_R) < 0) {
        printf(1, "ERROR: Setting permissions failed\n");
        exit();
    }
    printf(1, "Permissions for Write Protection test set to %d, Write protection\n", getmod(testWProtFile));
    printf(1, "\n", 0);

    // Create the Read/Write Protection test file
    fd = open(testRWProtFile, O_CREATE | O_RDWR);
    if (fd < 0) {
        printf(1, "ERROR: Creating testRWProtFile failed\n");
        printf(1, "%d\n", fd);
        exit();
    }
    write(fd, "RW_ProtFile", 11);
    close(fd);

    // Setting testfile owner to UID
    if (chown(testRWProtFile, testUID) < 0) {
        printf(1, "ERROR: Setting owner failed\n");
        exit();
    }
    printf(1, "Owner for Read/Write Protection test file set to %d\n", getown(testRWProtFile));

    printf(1, "Initial Permission after creating the file are %d, should be 0\n", getmod(testRWProtFile));
    // Setting testfile permissions to no permissions
    if (chmod(testRWProtFile, 0) < 0) {
        printf(1, "ERROR: Setting permissions failed\n");
        exit();
    }
    printf(1, "Permissions for Read/Write Protection test set to %d, Read/Write protection\n", getmod(testRWProtFile));
    printf(1, "\n", 0);

    exit();
} 