## notes to self

Why?

- I realize that I often read about security vulnerabilities from an outsider point of view.
- When I see "execute arbitrary code" or "remote code execution", I have no idea how it is even possible.
- I know that buffer overflows are a source of security vulnerabilities, but I completely lack the theory on how to bridge a "buffer overflow" into a "vulnerability".
- So I decided to look and learn a bit about it myself to get some minimal understanding of what's going on.

These notes are not necessarily accurate.

- Segmentation faults happen when a program is trying to read a region of memory that the operating has not allocated to the calling program.
- Local variables are allocated on the stack.
- The current function being executed has a return address which on the stack.
- When the current function exits, the execution of the program continues where the return address is pointing to.
- When writing data outside of a buffer's range allocated on the stack,
  the return pointer address of the current function being executed may be overwritten.
- If the resulting return pointer address points outside of the program memory region, it will cause a segmentation fault.
- Otherwise, it will cause the program to execute whatever the address is pointing to as if it were executable code.

### writing executable code on the stack

- It is possible to write executable code in the stack, and make the return address point to the stack so that it will be executed.
- However since the stack should not normally contain executable code, operating systems may prevent running executable code on the stack.
- Usually a combination of:
  - Heap spraying: The buffer is filled with a repeated value, which will do nothing (no op) when executed.
  - Shellcode: An arbitrary piece of executable code
  - Return address: An address that will point into the region of memory that was filled with no op.

### return-to-library

- Rather than writing executable code in the stack, craft return addresses towards existing library functions.
- Chaining library function executions together pretty much means executing arbitrary code.
- However since memory addresses for these libraries needs to be known beforehand, operating systems may prevent executing these functions by randomizing their location.

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