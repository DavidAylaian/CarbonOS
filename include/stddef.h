#ifndef STDDEF_H
#define STDDEF_H

typedef char*		string;
typedef signed		ptrdiff_t;
typedef unsigned	size_t;

#define NULL		(void*) 0x0

// offset of an element in a data structure
#define offsetof(TYPE, MEMBER)	((size_t) & ((TYPE*)0) -> MEMBER)

#endif