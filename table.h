/* Heath Gerrald
 * Lab7: Hash Tables
 * ECE 2230, Fall 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FALSE 0
#define TRUE 1

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
hashkey_t table_peek(table_t *T, int index);
void table_debug_print(table_t *T);

void set_increment(table_t *, hashkey_t K, int loop_count, int *i);
