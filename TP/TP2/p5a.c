#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
  int fd;
  char *text1="AAAAA";
  char *text2="BBBBB";

  fd = open("f1.txt",O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC,0600);
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

