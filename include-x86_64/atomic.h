#ifndef __SYNCHRO_ATOMIC_H__
#define __SYNCHRO_ATOMIC_H__

#include <stdatomic.h>

#define __fool_gcc(x) (*(struct {unsigned int a[100];} *)x)

/*
inline size_t fetch_and_store(volatile size_t *address,
				     size_t value);
inline void atmc_add(volatile ssize_t *address, ssize_t value);
inline size_t compare_and_swap32(volatile size_t *address,
				size_t old_value,
				size_t new_value);

inline size_t compare_and_swap64(volatile size_t *address,
				size_t old_value,
				size_t new_value);

inline size_t compare_and_swap_ptr(volatile size_t *address,
				size_t old_value,
				size_t new_value);

#define fetch_and_store(address, value) \
({ \
 volatile size_t ret_val; \
\
 __asm__ __volatile__ ("lock; xchgq %0, %1" \
 		       :"=r" ((ret_val)) \
 		       :"m" (__fool_gcc((address))), "0" ((value)) \
 		       :"memory"); \
 ret_val; \
})

#define atmc_add(address, value) \
({ \
  register volatile ssize_t val = (value); \
\
  __asm__ __volatile__ ("lock; addq %1, %0" \
  			: "=m" (*(address)) \
  			: "r" (val)); \
})

#define compare_and_swap32(address, old_value, new_value) \
({ \
	size_t ret_val = 0; \
	__asm__ __volatile__ ("lock\n\t" \
			"cmpxchgq %2, (%1)\n\t" \
			"sete (%3)\n\t" \
			: \
			: "a" (old_value), "r" (address), "r" (new_value), \
			"r" (&ret_val) \
			: "memory"); \
	ret_val; \
})

#define compare_and_swap64(address, old_value, new_value) \
({ \
	size_t ret_val = 0; \
	__asm__ __volatile__ ("lock\n\t" \
			"cmpxchg8b (%0)\n\t" \
			"sete (%1)\n\t" \
			: \
			: "r" (address), "r" (&ret_val), \
			"d" (*(((unsigned int*)&(old_value))+1)), "a" (*(((unsigned int*)&(old_value))+0)), \
			"c" (*(((unsigned int*)&(new_value))+1)), "b" (*(((unsigned int*)&(new_value))+0)) \
			: "memory"); \
			ret_val; \
})

#define compare_and_swap_ptr(address, old_value, new_value) compare_and_swap32(address, old_value, new_value)
*/

size_t fetch_and_store(volatile size_t *address,
				     size_t value)
{
    size_t ret_val = 0;
    while (!atomic_compare_exchange_weak(address, &ret_val, value))
        ;
    return ret_val;                                                            \
}

void atmc_add(volatile ssize_t*address, ssize_t value)
{
    atomic_fetch_add(address, value);
}

size_t compare_and_swap32(volatile size_t *address,
				size_t old_value,
				size_t new_value)
{
    return atomic_compare_exchange_strong(address, &old_value, new_value);
}

size_t compare_and_swap64(volatile size_t *address,
				size_t old_value,
				size_t new_value)
{
    return atomic_compare_exchange_strong(address, &old_value, new_value);
}

size_t compare_and_swap_ptr(volatile size_t *address,
				size_t old_value,
				size_t new_value)
{
    return atomic_compare_exchange_strong(address, &old_value, new_value);
}

#endif

