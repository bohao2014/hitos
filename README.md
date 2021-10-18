# hitos (lab4, process tracking and proc stats analysis)

# copy files under hitos/mount_files to hitos/hdc/usr/root to uplad the fies on the os

if mount failed, try more times with same cmd.

- main reference to this lab: https://www.cnblogs.com/mirage-mc/p/12899929.html
- \<ws root\>/Code includes the orignal tool files for this lab, including process.c and stats_log.py.
- chose to use \<ws root\>/mount_files/process_cnb.c to compile the process program on linux 0.11
  it only wait for the first child to exit(compiled as process.o for now on linux-0,11). sync should 
  be executed only when the first child process finished in order to see throughtput difference with 
  different time slice setting. process_new.c waits for all child processes to complete(compiled as 
  process for now on linux-0.11).  For this case, throughput will be the same no matter of what the 
  time slice is.

