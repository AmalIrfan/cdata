/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
|           Arena Allocator            |
|       ========================       |
|        Author: Amal Irfan K C        |
|          Date: 2025-05-08            |
|          File: arena.h               |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Simple Example                      |
|  ---------------                     |
|                                      |
|  #include <stdio.h>                  |
|  #define ARENA_IMPLEMENTATION        |
|  #include "arena.h"                  |
|                                      |
|  int main() {                        |
|      struct arena a = arena_create(  |
|  100);                               |
|      char* buf = arena_alloc(&a,     |
|  100);                               |
|      fgets(buf, 100, stdin);         |
|      printf("%.*s", strlen(buf),     |
|  buf);                               |
|      arena_distroy(&a);              |
|      return 0;                       |
|  }                                   |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Other Example                       |
|  --------------                      |
|                                      |
|  #include <string.h>                 |
|  #include <stdio.h>                  |
|  #define ARENA_IMPLEMENTATION        |
|  #include "arena.h"                  |
|                                      |
|  char* agetline(struct arena* a) {   |
|      char* line = NULL;              |
|      int n = 0;                      |
|                                      |
|      static char buf[256];           |
|      if( fgets(buf,sizeof(buf),      |
|                stdin) == NULL)       |
|          return NULL;                |
|                                      |
|      n = strlen(buf);                |
|      buf[n] = '\0';                  |
|      line = arena_alloc(a, n);       |
|      memcpy(line, buf, n);           |
|      return line;                    |
|  }                                   |
|                                      |
|  int main() {                        |
|      struct arena a = arena_create(  |
|  1000);                              |
|      char* line = NULL;              |
|      while(1) {                      |
|          line = agetline(&a);        |
|          if(line == NULL)            |
|              break;                  |
|          puts(line);                 |
|      }                               |
|      arena_distroy(&a);              |
|      return 0;                       |
|  }                                   |
|                                      |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Notes                               |
|  ------                              |
|  - ARENA_* macros can be defined by  |
|    user in order to customize.       |
|  - arena_alloc will call exit(1  on  |
|    overflow.                         |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Disclaimer                          |
|  -----------                         |
|      This header was created as pa-  |
|  rt of a creative venture, i.e. any  |
|  and all functionality provided by   |
|  it are unvetted and may or may not  |
|  be reliable. User discretion is r-  |
|  equired.                            |
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _ARENA_H_
#define _ARENA_H_

#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#if !defined(ARENA_MALLOC) \
 || !defined(ARENA_FREE)
#include <stdlib.h>
#define ARENA_MALLOC malloc
#define ARENA_FREE   free
#endif

struct arena {
	size_t capacity;
	size_t size;
	uint8_t* data;
};

struct arena arena_create(size_t capacity);
void* arena_alloc(struct arena* a,
                  size_t size);
void arena_distroy(struct arena *a);

#ifdef ARENA_IMPLEMENTATION
struct arena arena_create(size_t capacity) {
	struct arena a;
	a.capacity = capacity;
	a.size = 0;
	a.data = ARENA_MALLOC(capacity);
	return a;
}

#define _ARENA_UINITIALISED \
	"error: arena_alloc: uninitialised arena\n"
#define _ARENA_OVEFLOW \
	"error: arena_alloc: arena overflow\n" \
	"         requested: %d\n" \
	"         available: %d\n"

void* arena_alloc(struct arena* a,
                  size_t size) {
	void* p;
	/* check if it is usable */
	if (!a || !a->data) {
		fprintf(stderr,
		        _ARENA_UINITIALISED);
		exit(1);
	}
	/* check capacity */
	if (a->size + size > a->capacity) {
		fprintf(stderr,
		        _ARENA_OVEFLOW,
			size,
			a->capacity - a->size);
		exit(1);
	}
	p = a->data + a->size;
	a->size += size;
	return p;
}

void arena_distroy(struct arena *a) {
	ARENA_FREE(a->data);
	a->data = NULL;
	a->capacity = 0;
	a->size = 0;
}
#endif /* ARENA_IMPLEMENTATION */
#endif /* _ARENA_H_ */
