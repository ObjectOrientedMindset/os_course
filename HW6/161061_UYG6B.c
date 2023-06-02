#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

extern char etext, edata, end; // Symbols defined by linker

// Error handler for segmentation violation
void segfault_handler(int signal)
{
  printf("Segmentation violation occurred. Access denied.\n");
  exit(1);
}

int main()
{
  // Signal for segmentation violation
  signal(SIGSEGV, segfault_handler);

  // Variables to store addresses
  char *start_read_write, *end_read_write;
  char *start_read_only, *end_read_only;

  // Assign addresses to segments
  start_read_write = &edata;
  end_read_write = &end;
  start_read_only = &etext;
  end_read_only = &edata;

  // Display segment adresses
  printf("Read-Only Segment: %p - %p\n",
         start_read_only, end_read_only);
  printf("Read/Write Segment: %p - %p\n",
         start_read_write, end_read_write);

  // Create addresses inside of the segments
  char *random_read_write = start_read_write + 2;
  char *random_read_only = start_read_only + 4;

  // Read and write to random addresses within segments
  printf("\nTesting read and write permission of random addresses:\n");

  // Read from readable-writable segment
  printf("Read from adress inside read/write segment: %d\n", *random_read_write);

  // Write to readable-writable segment
  *random_read_write = 42;
  printf("Write to adress inside read/write segment: %d\n", *random_read_write);

  // Read from read-only segment
  printf("Read from adress inside read-only segment: %d\n", *random_read_only);

  // Attempt to write to read-only segment(Segmentation violation!)
  *random_read_only = 42;

  return 0;
}
