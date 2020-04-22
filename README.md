I did this function studying at 42. This function will get line by line one at a time, when called must receive a file descriptor generated with open (from fcntl.h) and a pointer of pointer where the function will put the found line.

You can run a test with command:\
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c main.c && ./a.out

result:\
return=1, line=file1 line 1\
return=1, line=file1 line 2\
return=0, line=file1 line 3

**Note that the function return in the last line is 0 if the file does not ending with an EOL (\\n).*

# My own logic for the exercise solution

Basically I have a linked list where each element of the list looks like this:

| Fild     | Definition                                                            |
|-----------|-----------------------------------------------------------------------|
| *string   | pointer to the position of element string start on the buffer         |
| *int* len | the length from the string start to the end of the line or buffer     |
| *int* eol | =1 if this element is the end of line, =0 if not                      |
| *free_buf | pointer to the buffer start if this is the last element of the buffer |
| *next     | pointer to the next element                                           |

let's assume we have a file with the following content:

a b c d e f\\ng h\\ni j l\\n m n o p q...

In a real situation, when i read a text file with a limited BUFFER_SIZE i don't know if what i will receive will be 0, 1, 2, 100, 1000 ... lines. In the example when i read the file using BUFFER_SIZE=11 i do not get any \\n in my buffer and i need to do a new reading, but this way i keep that first buffer/string in an element of my linked list:

| Fild      | value                 |
|-----------|-----------------------|
| *string   | a b c d e f           |
| len       | 11                    |
| eol       | 0                     |
| *free_buf | pointer to the buffer |
| *next     | NULL                  |

The string points to the buffer, and free_buf will be used to free the buffer when it is fully used, the string will not always point to the start of the buffer, see nexte example. Whem i continue to read the file more 11 bytes will be loaded and i will get on buffer "\\ng h\\ni j l\\n", this will be separated into several elements, no element of the list can have more than one line:

| Fild      | value                 |
|-----------|-----------------------|
| *string   | a b c d e f           |
| len       | 11                    |
| eol       | 0                     |
| *free_buf | pointer to the buffer |
| *next     | points to the next el |

| Fild      | value                 |
|-----------|-----------------------|
| *string   | \\ng h\\ni j l\\n     |
| len       | 0                     |
| eol       | 1                     |
| *free_buf | NULL                  |
| *next     | points to the next el |

| Fild      | value                 |
|-----------|-----------------------|
| *string   | g h\\ni j l\\n        |
| len       | 3                     |
| eol       | 1                     |
| *free_buf | pointer to the buffer |
| *next     | points to the next el |

| Fild      | value                 |
|-----------|-----------------------|
| *string   | i j l\\n              |
| len       | 5                     |
| eol       | 1                     |
| *free_buf | pointer to the buffer |
| *next     | NULL                  |

