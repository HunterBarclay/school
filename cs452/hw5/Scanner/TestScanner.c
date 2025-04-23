#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define ERR(s) err(s,__FILE__,__LINE__)
#define ASSERT(x, s) if (!(x)) ERR(s)

static void err(char *s, char *file, int line) {
  fprintf(stderr,"%s:%d: %s\n",file,line,s);
  exit(1);
}

static int init_scanner(const char* sep, int len) {
  int scanner=open("/dev/Scanner",O_RDWR);
  if (scanner<0)
    ERR("open() failed");

  if (sep) {
    if (ioctl(scanner,0,0))
      ERR("ioctl() for separators failed");
    if (write(scanner,sep,len)!=len)
      ERR("write() of separators failed");
  }

  return scanner;
}

static void test_single_sep() {
  enum {max=100};
  char buf[max+1];
  int len;

  fprintf(stderr, "Start Test A: Single Separator...\n");

  int scanner = init_scanner(":", 1);
  ASSERT(write(scanner, "Hello:World", 11) == 11, "[A] Failed to write data");

  ASSERT((len=read(scanner, buf, max)) == 5, "[A] Failed to read token 1");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Hello") == 0, "[A] Bad token 1");
  ASSERT((len=read(scanner, buf, max)) == 0, "[A] Failed to end token 1");

  ASSERT((len=read(scanner, buf, max)) == 5, "[A] Failed to read token 2");
  buf[len] = 0;
  ASSERT(strcmp(buf, "World") == 0, "[A] Bad token 2");
  ASSERT((len=read(scanner, buf, max)) == 0, "[A] Failed to end token 2");

  ASSERT((len=read(scanner, buf, max)) == -1, "[A] Failed to end data");
  
  close(scanner);
  fprintf(stderr, "Test A Passed\n");
  return;
}

static void test_double_sep() {
  enum {max=100};
  char buf[max+1];
  int len;

  fprintf(stderr, "Start Test B: Double Separator...\n");

  int scanner = init_scanner(":,", 2);
  ASSERT(write(scanner, ",Test:a,b:c,data,", 17) == 17, "[B] Failed to write data");

  ASSERT((len=read(scanner, buf, max)) == 0, "[B] Failed to read token 1");

  ASSERT((len=read(scanner, buf, max)) == 4, "[B] Failed to read token 2");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Test") == 0, "[B] Bad token 2");
  ASSERT((len=read(scanner, buf, max)) == 0, "[B] Failed to end token 2");

  ASSERT((len=read(scanner, buf, max)) == 1, "[B] Failed to read token 3");
  buf[len] = 0;
  ASSERT(strcmp(buf, "a") == 0, "[B] Bad token 3");
  ASSERT((len=read(scanner, buf, max)) == 0, "[B] Failed to end token 3");

  ASSERT((len=read(scanner, buf, max)) == 1, "[B] Failed to read token 4");
  buf[len] = 0;
  ASSERT(strcmp(buf, "b") == 0, "[B] Bad token 4");
  ASSERT((len=read(scanner, buf, max)) == 0, "[B] Failed to end token 4");

  ASSERT((len=read(scanner, buf, max)) == 1, "[B] Failed to read token 5");
  buf[len] = 0;
  ASSERT(strcmp(buf, "c") == 0, "[B] Bad token 5");
  ASSERT((len=read(scanner, buf, max)) == 0, "[B] Failed to end token 5");

  ASSERT((len=read(scanner, buf, max)) == 4, "[B] Failed to read token 6");
  buf[len] = 0;
  ASSERT(strcmp(buf, "data") == 0, "[B] Bad token 6");
  ASSERT((len=read(scanner, buf, max)) == 0, "[B] Failed to end token 6");

  ASSERT((len=read(scanner, buf, max)) == 0, "[B] Failed to read token 7");

  ASSERT((len=read(scanner, buf, max)) == -1, "[B] Failed to end data");
  ASSERT((len=read(scanner, buf, max)) == -1, "[B] Failed to end data");
  ASSERT((len=read(scanner, buf, max)) == -1, "[B] Failed to end data");

  close(scanner);
  fprintf(stderr, "Test B Passed\n");
  return;
}

static void test_default_sep() {
  enum {max=100};
  char buf[max+1];
  int len;

  fprintf(stderr, "Start Test C: Default Separator...\n");

  int scanner = init_scanner(NULL, 0);
  ASSERT(write(scanner, "Test Data", 9) == 9, "[C] Failed to write data");

  ASSERT((len=read(scanner, buf, max)) == 4, "[C] Failed to read token 1");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Test") == 0, "[C] Bad token 1");
  ASSERT((len=read(scanner, buf, max)) == 0, "[C] Failed to end token 1");

  ASSERT((len=read(scanner, buf, max)) == 4, "[C] Failed to read token 2");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Data") == 0, "[C] Bad token 2");
  ASSERT((len=read(scanner, buf, max)) == 0, "[C] Failed to end token 2");

  ASSERT((len=read(scanner, buf, max)) == -1, "[C] Failed to end data");

  close(scanner);
  fprintf(stderr, "Test C Passed\n");
  return;
}

static void test_null_sep() {
  enum {max=100};
  char buf[max+1];
  int len;

  fprintf(stderr, "Start Test D: Null Separator...\n");

  int scanner = init_scanner("\0a/", 3);
  ASSERT(write(scanner, "So\0me, Massive/ish-buffer\0\0\0hi\0\0there", 37) == 37, "[D] Failed to write data");

  ASSERT((len=read(scanner, buf, max)) == 2, "[D] Failed to read token 1");
  buf[len] = 0;
  ASSERT(strcmp(buf, "So") == 0, "[D] Bad token 1");
  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 1");

  ASSERT((len=read(scanner, buf, max)) == 5, "[D] Failed to read token 2");
  buf[len] = 0;
  ASSERT(strcmp(buf, "me, M") == 0, "[D] Bad token 2");
  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 2");

  ASSERT((len=read(scanner, buf, max)) == 5, "[D] Failed to read token 3");
  buf[len] = 0;
  ASSERT(strcmp(buf, "ssive") == 0, "[D] Bad token 3");
  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 3");

  ASSERT((len=read(scanner, buf, max)) == 10, "[D] Failed to read token 4");
  buf[len] = 0;
  ASSERT(strcmp(buf, "ish-buffer") == 0, "[D] Bad token 4");
  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 4");

  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 5");

  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 6");

  ASSERT((len=read(scanner, buf, max)) == 2, "[D] Failed to read token 7");
  buf[len] = 0;
  ASSERT(strcmp(buf, "hi") == 0, "[D] Bad token 7");
  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 7");

  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 8");

  ASSERT((len=read(scanner, buf, max)) == 5, "[D] Failed to read token 9");
  buf[len] = 0;
  ASSERT(strcmp(buf, "there") == 0, "[D] Bad token 9");
  ASSERT((len=read(scanner, buf, max)) == 0, "[D] Failed to end token 9");

  ASSERT((len=read(scanner, buf, max)) == -1, "[D] Failed to end data");

  close(scanner);
  fprintf(stderr, "Test D Passed\n");
  return;
}

static void test_buff_max() {
  enum {max=3};
  char buf[max+1];
  int len;

  fprintf(stderr, "Start Test E: Buffer Max...\n");

  int scanner = init_scanner(":", 1);
  ASSERT(write(scanner, "Hello:World", 11) == 11, "[E] Failed to write data");

  ASSERT((len=read(scanner, buf, max)) == 3, "[E] Failed to read token 1 part 1");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Hel") == 0, "[E] Bad token 1 part 1");
  ASSERT((len=read(scanner, buf, max)) == 2, "[E] Failed to read token 1 part 2");
  buf[len] = 0;
  ASSERT(strcmp(buf, "lo") == 0, "[E] Bad token 1 part 2");
  ASSERT((len=read(scanner, buf, max)) == 0, "[E] Failed to end token 1");

  ASSERT((len=read(scanner, buf, max)) == 3, "[E] Failed to read token 2 part 1");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Wor") == 0, "[E] Bad token 2 part 1");
  ASSERT((len=read(scanner, buf, max)) == 2, "[E] Failed to read token 2 part 2");
  buf[len] = 0;
  ASSERT(strcmp(buf, "ld") == 0, "[E] Bad token 2 part 2");
  ASSERT((len=read(scanner, buf, max)) == 0, "[E] Failed to end token 2");

  ASSERT((len=read(scanner, buf, max)) == -1, "[E] Failed to end data");

  close(scanner);
  fprintf(stderr, "Test E Passed\n");
  return;
}

static void test_multi_data() {
  enum {max=100};
  char buf[max+1];
  int len;

  fprintf(stderr, "Start Test F: Multiple Data...\n");

  int scanner = init_scanner(":", 1);
  ASSERT(write(scanner, "Hello:World", 11) == 11, "[F] Failed to write data 1");

  ASSERT((len=read(scanner, buf, max)) == 5, "[F] Failed to read token 1:1");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Hello") == 0, "[F] Bad token 1:1");
  ASSERT((len=read(scanner, buf, max)) == 0, "[F] Failed to end token 1:1");

  ASSERT(write(scanner, "Second:Data", 11) == 11, "[F] Failed to write data 2");

  ASSERT((len=read(scanner, buf, max)) == 6, "[F] Failed to read token 2:1");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Second") == 0, "[F] Bad token 2:1");
  ASSERT((len=read(scanner, buf, max)) == 0, "[F] Failed to end token 2:1");

  ASSERT((len=read(scanner, buf, max)) == 4, "[F] Failed to read token 2:2");
  buf[len] = 0;
  ASSERT(strcmp(buf, "Data") == 0, "[F] Bad token 2:2");
  ASSERT((len=read(scanner, buf, max)) == 0, "[F] Failed to end token 2:2");

  ASSERT((len=read(scanner, buf, max)) == -1, "[E] Failed to end data 2");

  close(scanner);
  fprintf(stderr, "Test F Passed\n");
  return;
}

/**
 * Try Scanner module
 */
int main(int argc, char **args) {
  if (argc == 2 && strcmp(args[1], "test") == 0) {
    fprintf(stderr, "Test Mode\n");
    test_single_sep();
    test_double_sep();
    test_default_sep();
    test_null_sep();
    test_buff_max();
    test_multi_data();

    return 0;
  }

  enum {max=100};
  char buf[max+1];
  int len;

  int scanner = init_scanner(":", 1);

  for (char *line; scanf("%m[^\n]\n",&line)!=EOF;) {
    len=strlen(line);
    if (len!=write(scanner,line,len))
      ERR("write() of data failed");
    free(line);
    while ((len=read(scanner,buf,max))>=0) {
      buf[len]=0;
      printf("%s%s",buf,(len ? "" : "\n"));
    }
  }

  close(scanner);
  return 0;
}
