# kmatmul
## Introduction
this is a Linux kernel module for efficient matrix computation

## Usage
compile the files and insert kernel module by typing
```shell
$ sudo make
```

after that execute the user program to give the matrix input to kernel module:
```shell
$ ./users
```

when you've done everything, clean the executes and remove kernel module by typing:
```shell
$ sudo make clean
```