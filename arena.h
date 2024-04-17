#ifndef ARENA_H
#define ARENA_H

// https://stackoverflow.com/questions/12825148/what-is-the-meaning-of-the-term-arena-in-relation-to-memory

#include <stdint.h>

typedef struct {
  uint8_t *stack_memory;
  uint64_t stack_alloc_pos;
} arena_t;

// create or destroy a 'stack' - an "arena"
arena_t *ArenaAlloc(void);
void ArenaRelease(arena_t *arena);

// push some bytes onto the 'stack' - the way to allocate
void *ArenaPush(arena_t *arena, uint64_t size);

// some macro helpers that I've found nice:
#define PushArray(arena, type, count)                                          \
  (type *)ArenaPush((arena), sizeof(type) * (count))
#define PushArrayZero(arena, type, count)                                      \
  (type *)ArenaPushZero((arena), sizeof(type) * (count))
#define PushStruct(arena, type) PushArray((arena), (type), 1)
#define PushStructZero(arena, type) PushArrayZero((arena), (type), 1)

// pop some bytes off the 'stack' - the way to free
void ArenaPop(arena_t *arena, uint64_t size);

// get the # of bytes currently allocated.
uint64_t ArenaGetPos(arena_t *arena);

// also some useful popping helpers:
void ArenaSetPosBack(arena_t *arena, uint64_t pos);
void ArenaClear(arena_t *arena);

#endif
