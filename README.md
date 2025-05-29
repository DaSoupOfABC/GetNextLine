# get_next_line

> A project from 42 school that implements a function to read a line from a file descriptor.

## 📚 Project Description

The `get_next_line` project is part of the 42 school curriculum. Its objective is to implement a function that reads one line at a time from a file descriptor, efficiently managing memory and buffer usage. The function must be able to return lines of any length and should work with multiple file descriptors simultaneously.

### 🛠 Function Prototype

```c
char *get_next_line(int fd);
```

- **fd**: File descriptor to read from.
- **Returns**: A string containing the next line from the file descriptor, including the newline character (`'\n'`) if present, or `NULL` if the end of the file is reached or an error occurs.

## 📁 Project Files

```
get_next_line/
├── get_next_line.c        // Contains the core logic
├── get_next_line_utils.c  // Utility functions (e.g. custom strlen, strchr, etc.)
├── get_next_line.h        // Header file with function declarations
├── main.c                 // Optional file for testing purposes
```

## ✅ Features

- Reads from a file descriptor line by line.
- Handles multiple file descriptors at the same time.
- Efficient memory usage and error handling.
- Respects 42’s coding standards and constraints.

## ⚙️ Compilation

To compile and run with your own test file:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl
```

You can replace `42` with any buffer size you'd like to test.

## 🧪 Usage Example

```c
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd = open("sample.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## 📌 Notes

- Only the following standard functions are allowed: `read`, `malloc`, and `free`.
- Custom implementations must be written for any other standard string functions used (like `strchr`, `strlen`, etc.).
- Behavior must be consistent with files that have or don’t have newline characters at the end.
- Buffer size must be variable and defined using the `BUFFER_SIZE` macro during compilation.
