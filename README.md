I did this function during my studies at 42. This function uses only read (unistd.h), free and malloc (stdlib.h). It must receive a file descriptor generated with open (from fcntl.h) and a pointer of pointer where the function will put the found line. When called will get line by line one at a time.

This get_next_line.c is not my first version, the first is in [v1.0](https://github.com/roneyrogerio/get_next_line/tree/v1.0). In comparison with the old one it solves some issues, for example with this it is possible to not read a file until the end and still not have a memory leak, besides other improvements.

You can run a test with command:
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c main.c && ./a.out
```
result:
```bash
return=1, line=file1 line 1
return=1, line=file1 line 2
return=0, line=file1 line 3
```
**Note that the function return in the last line is 0 if the file does not ending with an EOL (\\n).*

# My own logic to solve the exercise

I use linked list. The function has two structures, one is static and remains in the next function call, the second is used in the linked list.

When the function is called it will verify if there is already a loaded line inside the linked list, for this there is a field in my static struct variable that indicates this.

When there are lines in the linked list, the function will transfers the string of each element to **line that was passed in the function argument and and free all elements of the linked list.

When there are no lines loaded in the linked list, the function reads the file (receiving n bytes defined in BUFFER_SIZE). If in the received buffer there is at least one newline it creates a new element, and only one new element, where the string of that element will contain everything before that newline, an offset is also saved in the static variable indicating the initial position in the buffer that has not yet been used. If the buffer has no newline, the entire contents of the buffer are copied to the string of a new element in the linked list.

When a new line is requested, it is checked if any part of the last buffer stored in the static needs to be used. If it exists, that part is transferred to the linked list.

Look at the source code if you want to understand in detail.

# The get_next_line_cub.c version

The version get_next_line_cub.c is a more friendly version to use in a real situation. I created it to use in my next project, cub3d. It works similar to getline (from stdio.h), it returns the number of bytes of each line and returns -1 when there are no more lines.

You can run a test with command:
```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line_cub.c main_cub.c && ./a.out
```
result:
```bash
return=12, line=file1 line 1
return=12, line=file1 line 2
return=12, line=file1 line 3
return=-1, line=
```
