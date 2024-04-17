#include "arena.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1024

arena_t *ArenaAlloc(void) {
  arena_t *arena = malloc(INITIAL_SIZE);
  arena->stack_memory = (uint8_t *)arena;
  arena->stack_alloc_pos = 0;

  return arena;
}

void ArenaRelease(arena_t *arena) { free(arena); }

// push some bytes onto the 'stack' - the way to allocate
void *ArenaPush(arena_t *arena, uint64_t size) {
  void *ptr;
  ptr = arena->stack_memory + size;
  arena->stack_alloc_pos += size;

  return ptr;
}

void *ArenaPushZero(arena_t *arena, uint64_t size) {
  void *ptr;
  ptr = arena->stack_memory + size;
  arena->stack_alloc_pos += size;

  memset(ptr, 0, size);

  return ptr;
}

// pop some bytes off the 'stack' - the way to free
void ArenaPop(arena_t *arena, uint64_t size) { arena->stack_alloc_pos -= size; }

// get the # of bytes currently allocated.
uint64_t ArenaGetPos(arena_t *arena) { return arena->stack_alloc_pos; }

// also some useful popping helpers:
void ArenaSetPosBack(arena_t *arena, uint64_t pos) {
  arena->stack_alloc_pos = pos;
}

void ArenaClear(arena_t *arena) { arena->stack_alloc_pos = 0; }

int main() {
  printf("hello arena allocator\n");

  arena_t *a = ArenaAlloc();

  int *ptr = ArenaPush(a, sizeof(int *));
  *ptr = 420;

  printf("%llu\n", ArenaGetPos(a));

  return 0;
}
