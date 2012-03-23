
#include <cstdlib> //for exit, abort
#include <unistd.h> //for fork, sleep, _exit
#include <sys/wait.h> //for wait
#include <signal.h> //for kill
#include <iostream>

#define LOG(mess) { std::cout << mess << std::endl; }
#define ASSERT(cond,mess) { if (!(cond)) { LOG("ERROR " << mess); abort(); } }
#define PRINT(value) LOG(#value << " = " << value)

int safe_fork ()
{
  LOG("forking kernel");
  int pid = fork();
  if (pid) PRINT(pid);
  ASSERT(pid >= 0, "failed to fork");
  return pid;
}

int main () {

  int pid_abort = 0;
  if ((pid_abort = safe_fork()) == 0) {
    sleep(1);
    LOG("abort()ing");
    abort();
  }

  int pid_exit_0 = 0;
  if ((pid_exit_0 = safe_fork()) == 0) {
    sleep(2);
    LOG("_exit(0)ing");
    _exit(0);
  }

  int pid_exit_1 = 0;
  if ((pid_exit_1 = safe_fork()) == 0) {
    sleep(3);
    LOG("_exit(1)ing");
    _exit(1);
  }

  int pid_sleep = 0;
  if ((pid_sleep = safe_fork()) == 0) {
    LOG("sleeping...");
    sleep(4);
    LOG("..._exit(0)ing");
    _exit(0);
  }

  int pid_spin = 0;
  if ((pid_spin = safe_fork()) == 0) {
    LOG("spinning...");
    while (true) {}
  }

  while (pid_abort or pid_exit_0 or pid_exit_1 or pid_sleep or pid_spin) {

    LOG("");

    int status;
    int pid = wait(&status);
    int exited = WIFEXITED(status);
    int exitstatus = WEXITSTATUS(status);
    bool ok = exited and exitstatus == 0;
    ASSERT(pid >= 0, "failed to wait");
    PRINT(pid);
    PRINT(exited);
    PRINT(exitstatus);
    PRINT(ok);

    if (pid == pid_abort) {
      pid_abort = 0;
      LOG("finished abort()");

    } else if (pid == pid_exit_0) {

      pid_exit_0 = 0;
      LOG("finished _exit(0)");

    } else if (pid == pid_exit_1) {

      pid_exit_1 = 0;
      LOG("finished _exit(1)");

    } else if (pid == pid_sleep) {

      pid_sleep = 0;
      LOG("finished sleeping");
      kill(pid_spin, 9);

    } else if (pid == pid_spin) {

      pid_spin = 0;
      LOG("finished spinning");
    }
  }

  return 0;
}

