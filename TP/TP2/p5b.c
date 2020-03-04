#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
  int fd;
  char *text1="CCCCC";
  char *text2="DDDDD";

  fd = open("f1.txt", O_WRONLY|O_SYNC,0600);
  write(fd,text1,5);
  write(fd,text2,5);

  getchar();
    if (write(fd, text1, 5) < 0) {
        perror("Error writing text1");
        return 2;
    }

    getchar();
    if (write(fd, text2, 5) < 0) {
        perror("Error writing text2");
        return 3;
    } 

  close(fd);
  return 0;
}

