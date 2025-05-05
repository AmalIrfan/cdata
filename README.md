# An exploration of Data Structures in C

## Simple Hashmap

See [simple_hashmap.h](./simple_hashmap.h), eg:

```c
#include <stdio.h>

#define HASHMAP_IMPLEMENTATION
#define HASHMAP_VALUE_TYPE(value)\
    int value
#define HASHMAP_SIZE 16
#define HASHMAP_DEFAULT -1
#include "hashmap.h"

int main() {
    int i = 0;
    hashmap_set("abc", 1);
    i = hashmap_get("abc");
    printf("%d\n", i);
    return 0;
}
```
