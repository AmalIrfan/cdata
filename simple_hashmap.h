/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\
|            Simple Hashmap            |
|      ==========================      |
|       Author: Amal Irfan K C         |
|         Date: 2025-05-05             |
|         File: simple_hashmap.h       |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Example                             |
|  --------                            |
|      The following example uses th-  |
|  is header to make a hashmap to int  |
|  values.                             |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
|  #include <stdio.h>                  |
|                                      |
|  #define HASHMAP_IMPLEMENTATION      |
|  #define HASHMAP_VALUE_TYPE(value)\  |
|      int value                       |
|  #define HASHMAP_SIZE 16             |
|  #define HASHMAP_DEFAULT -1          |
|  #include "hashmap.h"                |
|                                      |
|  int main() {                        |
|      int i = 0;                      |
|      hashmap_set("abc", 1);          |
|      i = hashmap_get("abc");         |
|      printf("%d\n", i);              |
|      return 0;                       |
|  }                                   |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Simple Example                      |
|  ---------------                     |
|      This example shows the default  |
|  behaviour.                          |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
|  #include <stdio.h>                  |
|                                      |
|  #define HASHMAP_IMPLEMENTATION      |
|  #include "hashmap.h"                |
|                                      |
|  void hello() {                      |
|      printf("Hello, World!\n");      |
|  }                                   |
|                                      |
|  int main() {                        |
|      void (*f)();                    |
|      hashmap_set("abc", hello);      |
|      f = hashmap_get("abc");         |
|      (*f)();                         |
|      return 0;                       |
|  }                                   |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Notes                               |
|  ------                              |
|  - HASHMAP_* macros can be defined   |
|    by user in order to customize.    |
|  - hashmap_set will call exit(1) on  |
|    overflow.                         |
|  - hashmap_get will return HASHMAP-  |
|    _DEFAULT if the name is not fou-  |
|    nd.                               |
|*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*|
|  Disclaimer                          |
|  -----------                         |
|      This header was created as pa-  |
|  rt of a creative venture, i.e. any  |
|  and all functionality provided by   |
|  it are unvetted and may or may not  |
|  be reliable. User discretion is r-  |
|  equired.                            |
|      This hashmap only allows you    |
|  to use a single hashmap in a proj-  |
|  ect which is very limitting.        |
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef _HASHMAP_H_
#define _HASHMAP_H_
#include <string.h>

#ifndef HASHMAP_DEFAULT
#define HASHMAP_DEFAULT NULL
#endif
#ifndef HASHMAP_SIZE
#define HASHMAP_SIZE 10
#endif

#ifndef HASHMAP_VALUE_TYPE
#define HASHMAP_VALUE_TYPE(value) \
	void (*value)();
#endif
typedef HASHMAP_VALUE_TYPE(hashmap_value);

struct hashmap_element {
	char *name;
	hashmap_value value;
};

struct hashmap_element
hashmap[HASHMAP_SIZE] = {0};

#ifndef HASHMAP_HASH
int hashmap_hash(char *s);
#else
#define hashmap_hash HASHMAP_HASH
#endif

#define hashmap_index(s) \
	(hashmap_hash(s) % HASHMAP_SIZE)

void hashmap_set(char *name,
                 hashmap_value value);
hashmap_value hashmap_get(char *name);

#ifdef HASHMAP_IMPLEMENTATION
#ifndef HASHMAP_HASH
int hashmap_hash(char *s) {
	int h = 0;
	char c = 0;
	while ((c=*s)) {
		h = h * 33 + c;
		s++;
	}
	return h;
}
#endif

void hashmap_set(char *name,
                 hashmap_value value) {
	int i = hashmap_index(name);
	int j = 0; /* limiter */
	char *hashmap_name = NULL;
	/* skip the ones with names that
	   doesn't match */    
	while ((hashmap_name = hashmap[i].name) != 0
	       && strcmp(hashmap_name, name) != 0
	       && j < HASHMAP_SIZE) {
		i = (i + 1) % HASHMAP_SIZE;
		j++;
	}
	if (j > HASHMAP_SIZE)
		exit(1);
	if (!hashmap_name)
		hashmap[i].name = name;
	hashmap[i].value = value;
}

hashmap_value hashmap_get(char *name) {
	int i = hashmap_index(name);
	int j = 0; /* limiter */
	char *hashmap_name = NULL;
	/* skip the ones with names that
	   doesn't match */
	while ((hashmap_name = hashmap[i].name) != 0
	       && strcmp(hashmap_name, name) != 0
	       && j < HASHMAP_SIZE) {
		i = (i + 1) % HASHMAP_SIZE;
		j++;
	}
	if (!hashmap_name || j > HASHMAP_SIZE)
		return HASHMAP_DEFAULT;
	return hashmap[i].value;
}
#endif /* HASHMAP_IMPLEMENTATION */
#endif /* _HASHMAP_H_ */
