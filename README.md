## notes to self

These notes are not necessarily accurate.

- Segmentation faults happen when a program is trying to read a region of memory that the operating has not allocated to the calling program.
- Local variables are allocated on the stack.
- The current function being executed has a return address which on the stack.
- When the current function exits, the execution of the program continues where the return address is pointing to.
- When writing data outside of a buffer's range allocated on the stack,
  the return pointer address of the current function being executed may be overwritten.
- If the resulting return pointer address points outside of the program memory region, it will cause a segmentation fault.
- Otherwise, it will cause the program to execute whatever the address is pointing to as if it were executable code.


## normal

Compile:

```sh
$ gcc -o main src/main/c/main.c
$ chmod +x main
```

Execute:

```sh
$ ./main 0123456789012345678901234567890123456789
0123456789012345678901234567890123456789

$ ./main 01234567890123456789012345678901234567890
01234567890123456789012345678901234567890
*** stack smashing detected ***: ./main terminated
Abandon (core dumped)     
```

## no-stack-protector

Compile:

```sh
gcc -o main src/main/c/main.c -fno-stack-protector
chmod +x main
```

Execute:

```sh
$ ./main 01234567890123456789012345678901234567890
01234567890123456789012345678901234567890

$ ./main 01234567890123456789012345678901234567890000000000000000
01234567890123456789012345678901234567890000000000000000
Erreur de segmentation (core dumped)
```