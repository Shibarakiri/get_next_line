*This project has been created as part of the 42 curriculum by jeguiber.*

# get_next_line

## Description

`get_next_line` is a C function that returns one line at a time from a file
descriptor. Each call continues reading from the previous position, which
makes it possible to process a file or standard input line by line.

The returned line includes its terminating `\n` character when one is present.
For the last line of a file, the function returns the remaining characters
without adding a newline. When there is nothing left to read, or when an error
occurs, the function returns `NULL`.

The project introduces static variables and buffered reading. The buffer size
used by `read()` is configurable at compile time with the `BUFFER_SIZE` macro.

## Instructions

### Compilation

The project does not require an external library or a Makefile. Compile the
mandatory source files into object files from the repository root:

```sh
cc -Wall -Wextra -Werror -c get_next_line.c get_next_line_utils.c
```

To choose a specific buffer size, define `BUFFER_SIZE` during compilation:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c \
	get_next_line.c get_next_line_utils.c
```

The project also compiles without `-D BUFFER_SIZE`, in that case, the default
value defined in `get_next_line.h` is used. The evaluator may test different
values, including very small and very large buffer sizes.

## Usage

This project provides the `get_next_line()` function. The function receives a file descriptor and returns the next line every time it is called:

```c
#include "get_next_line.h"

char	*get_next_line(int fd);
```

For example, a test program can call the function repeatedly with its own file
descriptor:

```c
#include <stdio.h>
#include <stdlib.h>

char	*line;

line = get_next_line(fd);
while (line != NULL)
{
	printf("%s", line);
	free(line);
	line = get_next_line(fd);
}
```

The file descriptor is supplied by the caller or by the evaluator. Every line
returned by `get_next_line()` is dynamically allocated and must be freed by the
caller.

## Algorithm

The implementation keeps unread data in a static pointer named `stash`. This
storage persists between calls without using a global variable. The reading,
line extraction, and cleanup helpers are named `ft_stash_all`, `ft_get_line`,
and `ft_free_all`.

1. Allocate a temporary `tmp` buffer of `BUFFER_SIZE + 1` bytes.
2. Read chunks with `read()` into `tmp` and append them to `stash` until a newline is
   found or the end of the file is reached.
3. Use `ft_get_line` to extract the first line from `stash`, including the newline
   when present.
4. Use `ft_free_all` to remove the extracted line from `stash` and keep the remaining characters for
   the next call.
5. Free temporary allocations and return the extracted line.

The function reads only until it has enough data to return the next line. It
does not read the entire file in advance. The helper functions in
`get_next_line_utils.c` handle string length calculation, newline detection,
and dynamic string joining.

The mandatory implementation uses one static pointer for a single reading
state. It is intended for sequential calls on one file descriptor. A bonus
implementation would use the `_bonus.c` and `_bonus.h` naming required by the
subject and preserve a separate state for multiple file descriptors.

## Project structure

| File | Purpose |
|---|---|
| `get_next_line.c` | Main `get_next_line()` implementation and line processing. |
| `get_next_line_utils.c` | String and stash management helper functions. |
| `get_next_line.h` | Function prototypes, system headers, and default `BUFFER_SIZE`. |

## Constraints

- The project is written in C and follows the Norm.
- Only `read`, `malloc`, and `free` are used as external functions by the
  mandatory implementation.
- `lseek()` and global variables are not used.
- The project must work with different `BUFFER_SIZE` values.
- Binary files and modifying a file after reading has started are outside the
  defined behavior of the subject.

## Resources

- The official `get_next_line` subject.
- `man 2 read` - reading bytes from a file descriptor.
- `man 2 open` - opening files and obtaining file descriptors.
- `man 2 close` - closing file descriptors.

### AI usage

AI assistance was used to help structure and write this README. The implementation and testing remain the responsibility of the project author, who is accountable for
understanding, checking, and defending the code.
