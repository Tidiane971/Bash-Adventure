// kbhit
#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>
#include <stdbool.h>

int kbhit(void) {
    static bool initflag = false;
    static const int STDIN = 0;

    if (!initflag) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initflag = true;
    }

    int nbbytes;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
}

int getKey(){
  char c;
  while (!kbhit()) {
      fflush(stdout);
      sleep(1);
  }
  c = getchar();


  return c;
}


int scangets(){
  char c;
  scanf("%c",&c);
  if(c>=48 && c<=57){
    while((getchar()) != '\n');
    return (c - '0');
  }
  else{
    while((getchar()) != '\n');
    return c;
  }

}
