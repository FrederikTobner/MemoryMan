# Ressource Pool

A ressource pool is a struct that contains an dynamic array of pointers. These pointers can be freed together if there are not needed anymore.
This should serve as a convinient way to allocate and free memory.

Functions:

* ressource_pool_malloc(ressource_pool * pool, size_t size) - should allocate the prefered amount of memory and add the pointer to the dynamic array.
* ressource_pool_free(ressource_pool * pool) - should free all the pointers stored in the pool
* ressource_pool_remove(ressource_pool * pool, void * pointer) - should remove a specific pointer in the pool and free the memory it occupies.
