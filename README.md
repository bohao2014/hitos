# hitos (lab7 shared memory, based on lab6 semaphore)

- copy files under hitos/mount_files to hitos/hdc/usr/root to uplad the fies on the os
- if mount failed, try more times with same cmd

## lab7 notes
- make sure to manually copy unistd.h into mounted drive, otherwise will see error when compile.
- main reference to this lab
    - https://www.cnblogs.com/mirage-mc/p/13034973.html
    - https://blog.csdn.net/qq_37857224/article/details/119349669

## lab6 notes
- remove the comment with cn charaters in pc.c before copy it to the mounted drive
- <linux ws>/include/unistd.h and <linux ws>/include/linux/sem.h need to be copied to hdc/usr/include and hdc/usr/include/linux
- use "sudo xxd hdc/usr/root/buffer_file" to decode the buffer files
- main reference to this lab
    - https://www.cnblogs.com/tradoff/p/5754583.html
    - https://www.cnblogs.com/mirage-mc/p/12913993.html
