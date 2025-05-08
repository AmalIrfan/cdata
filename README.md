# An exploration of Data Structures in C

## Arena Allocator

See [arena.h](./arena.h), eg:

```c
#include <stdio.h>
#define ARENA_IMPLEMENTATION
#include "arena.h"

int main() {
    struct arena a = arena_create(
100);
    char* buf = arena_alloc(&a,
100);
    fgets(buf, 100, stdin);
    printf("%.*s", strlen(buf),
buf);
    arena_distroy(&a);
    return 0;
}
```

## Simple Hashmap

See [simple_hashmap.h](./simple_hashmap.h), eg:

```c
#include <stdio.h>

#define HASHMAP_IMPLEMENTATION
#define HASHMAP_VALUE_TYPE(value)\
    int value
#define HASHMAP_SIZE 16
#define HASHMAP_DEFAULT -1
#include "simple_hashmap.h"

int main() {
    int i = 0;
    hashmap_set("abc", 1);
    i = hashmap_get("abc");
    printf("%d\n", i);
    return 0;
}
```
