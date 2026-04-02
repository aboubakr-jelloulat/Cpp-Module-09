# Performance Considerations: `std::vector` vs `std::deque`

## CPU Cache and Memory Access

### What is CPU Cache?

Modern CPUs use cache memory to store recently accessed data. Accessing data from cache is significantly faster than accessing main memory. Programs that access memory sequentially benefit from better cache utilization.

---

### Behavior with `std::vector` (Contiguous Memory)

When accessing an element in a `std::vector`, for example:

```cpp
v[0]
```

The CPU often loads adjacent elements into the cache automatically:

```
v[1], v[2], v[3]
```

This happens because all elements are stored next to each other in memory.

This behavior is known as **cache locality**, and it significantly improves performance during iteration and sequential access.

---

### Behavior with `std::deque` (Segmented Memory)

In a `std::deque`, elements are stored in multiple memory blocks:

```
v[0] → Block 1  
v[1] → Block 1  
v[2] → Block 2
```

Since elements may not be adjacent in memory, the CPU cannot efficiently preload nearby elements.

This leads to:

* More cache misses
* More frequent memory accesses
* Slower overall performance

---

## Pointer Arithmetic

### `std::vector`

Accessing an element is straightforward:

```cpp
v[i] = *(base_address + i);
```

This is a single operation using direct pointer arithmetic.

---

### `std::deque`

Access requires two steps:

```cpp
v[i] = block_map[index_block][index_inside_block];
```

Steps involved:

1. Determine which memory block contains the element
2. Access the element within that block

This additional indirection introduces overhead.

---

## Iteration Performance

### `std::vector`

```cpp
for (int x : v)
```

Iteration is very efficient because elements are stored sequentially in memory. The CPU can take advantage of cache locality and prefetching.

---

### `std::deque`

Iteration is slightly slower because:

* Elements may reside in different memory blocks
* The CPU cannot efficiently prefetch data
* There may be more pointer dereferencing

---

## Summary

| Aspect             | `std::vector` | `std::deque`    |
| ------------------ | ------------- | --------------- |
| Memory Layout      | Contiguous    | Segmented       |
| Cache Efficiency   | High          | Lower           |
| Access Speed       | Very fast     | Slightly slower |
| Pointer Arithmetic | Simple        | More complex    |
| Iteration          | Optimized     | Less efficient  |

In performance-critical scenarios, especially those involving frequent iteration or binary search, `std::vector` typically provides better performance due to its contiguous memory layout and cache-friendly behavior.
