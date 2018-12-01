/* table.h
 * Lab7: Hash Tables
 * ECE 2230, Fall 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* constants used to indicate type of probing.  */
enum ProbeDec_t {LINEAR, DOUBLE, QUAD};

typedef void *data_t;   /* pointer to the information, I, to be stored in the table */
typedef unsigned int hashkey_t;   /* the key, K, for the pair (K, I) */

typedef struct table_etag {
    hashkey_t key;
    data_t data_ptr;
} table_entry_t;

typedef struct table_tag {
    // you need to fill in details, and you can change the names!
    int table_size_M;
    int type_of_probing_used_for_this_table;
    int num_keys_stored_in_table;
    int num_probes_for_most_recent_call;
    table_entry_t *data_arr;
} table_t;


table_t *table_construct(int table_size, int probe_type);
table_t *table_rehash(table_t * T, int new_table_size);
int table_entries(table_t *);
int table_full(table_t *);
int table_deletekeys(table_t *);
int table_insert(table_t *, hashkey_t K, data_t I);
data_t table_delete(table_t *, hashkey_t K);
data_t table_retrieve(table_t *, hashkey_t K);
void table_destruct(table_t *);
int table_stats(table_t *);

/* This function is for testing purposes only.  Given an index position into
 * the hash table return the value of the key if data is stored in this
 * index position.  If the index position does not contain data, then the
 * return value must be zero.  Make the first
 * lines of this function
 *       assert(0 <= index && index < table_size);
 */
hashkey_t table_peek(table_t *T, int index);

/* Print the table position and keys in a easily readable and compact format.
 * Only useful when the table is small.
 */
void table_debug_print(table_t *T);
