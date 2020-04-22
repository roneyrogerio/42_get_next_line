I did this function studying at 42. This function when called must receive a file descriptor generated with open (from fcntl.h) and a poninter of pointer where the function will put the found line.

You can run a test with command:\
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c main.c && ./a.out

result:\
return=1, line=file1 line 1\
return=1, line=file1 line 2\
return=0, line=file1 line 3

**Note that the function return in the last line is 0 if the file does not ending with an EOL (\\n).**
