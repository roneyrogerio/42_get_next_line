I did this function during my studies at 42. This is not my first version, the first is in [v1.0](https://github.com/roneyrogerio/get_next_line/tree/v1.0). In comparison with the old one it solves some issues, for example with this it is possible to not read a file until the end and still not have a memory leak, besides other improvements.

This function when called will get line by line one at a time, it must receive a file descriptor generated with open (from fcntl.h) and a pointer of pointer where the function will put the found line.

You can run a test with command:\
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c main.c && ./a.out

result:\
return=1, line=file1 line 1\
return=1, line=file1 line 2\
return=0, line=file1 line 3

**Note that the function return in the last line is 0 if the file does not ending with an EOL (\\n).*

# My own logic for the exercise solution

I use linked list. The function has two structures, one is static and remains in the next function call, the second is used in the linked list.

When the function is called it will verify if there is already a loaded line inside the linked list, for this there is a field in my static variable that indicates this.

When there are lines the function will transfers the string of each element to **line that was passed in the function argument and and free all elements of the linked list.

When there are no lines loaded in the linked list, the function reads the file (receiving n bytes defined in BUFFER_SIZE), then creates an new element in the linked list. If in the received buffer there is at least one newline it creates an new element, and only one new element, where the string of that element will contain everything before that newline, an offset is also saved in the statistical variable indicating the initial position in the buffer that has not yet been used. . If the buffer has no newline, the entire contents of the buffer are copied to the string of a new element in the linked list.
