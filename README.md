I did this function studying at 42. This function when called must receive a file descriptor generated with open (from fcntl.h) and a pointer of pointer where the function will put the found line.

You can run a test with command:\
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c main.c && ./a.out

result:\
return=1, line=file1 line 1\
return=1, line=file1 line 2\
return=0, line=file1 line 3

**Note that the function return in the last line is 0 if the file does not ending with an EOL (\\n).*

| Fild   | Definition                                                            |
|--------|-----------------------------------------------------------------------|
| string | pointer to the position of element string start on the buffer         |
| len    | the length from the string start to the end of the line or buffer     |
| eol    | =1 if this element is the end of line, =0 if not                      |
| free   | pointer to the buffer start if this is the last element of the buffer |
| next   | pointer to the next element                                           |

