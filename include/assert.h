#ifndef ASSERT_H
#define ASSERT_H


#define STATIC_ASSERT(cond, msg) typedef char static_assertion_##msg[(cond) ? 1 : -1];


#endif