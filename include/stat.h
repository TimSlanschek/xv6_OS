#ifndef INCLUDE_STAT_h_
#define INCLUDE_STAT_h_

#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device

struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
  ushort owner;// Owner of the file         // lab4 addition
  ushort perms;// File permissions          // lab4 addition
};

#endif  // INCLUDE_STAT_h_
