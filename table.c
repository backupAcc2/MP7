/* table.c - MP7
 * Heath Gerrald
 * ECE 2230, Fall 2018
 * contains functions for our hash table
 */

 #include "table.h"

 /*****************************************************************************
  *  The empty table is created.  The table must be dynamically allocated and
  *  have a total size of table_size.  The maximum number of (K, I) entries
  *  that can be stored in the table is table_size-1.  For open addressing,
  *  the table is filled with a special empty key distinct from all other
  *  nonempty keys.
  *
  *  the probe_type must be one of {LINEAR, DOUBLE, QUAD}
  *
  *  Do not "correct" the table_size or probe decrement if there is a chance
  *  that the combinaion of table size or probe decrement will not cover
  *  all entries in the table.  Instead we will experiment to determine under
  *  what conditions an incorrect choice of table size and probe decrement
  *  results in poor performance.
  */
 table_t *table_construct(int table_size, int probe_type){

   table_t *T = (table_t *)malloc(sizeof(table_t));
   T->type_of_probing_used_for_this_table = probe_type;
   T->table_size_M = table_size;
   T->num_keys_stored_in_table = 0;
   T->num_probes_for_most_recent_call = 0;
   T->data_arr = (table_entry_t*)malloc(sizeof(table_entry_t) * table_size);

   // ensure our data array is set to null
   for (int i = 0; i < table_size; i++)
   {
        T->data_arr[i].key = 0;
        T->data_arr[i].data_ptr = NULL;
   }

   return T;
 }



 /*****************************************************************************
  * Sequentially remove each table entry (K, I) and insert into a new
  * empty table with size new_table_size.  Free the memory for the old table
  * and return the pointer to the new table.  The probe type should remain
  * the same.
  *
  * Do not rehash the table during an insert or delete function call.  Instead
  * use drivers to verify under what conditions rehashing is required, and
  * call the rehash function in the driver to show how the performance
  * can be improved.
  */
 table_t *table_rehash(table_t *T, int new_table_size){

 }



 /*****************************************************************************
  * returns number of entries in the table
  */
 int table_entries(table_t *T){
   return T->num_keys_stored_in_table;
 }



 /*****************************************************************************
  * returns 1 if table is full and 0 if not full.
  */
 int table_full(table_t *T){
   if (T->num_keys_stored_in_table == T->table_size_M - 1)
        return 1;

   return 0;

 }



 /*****************************************************************************
  * returns the number of table entries marked as deleted
  */
 int table_deletekeys(table_t *T){
      int delete_count = 0;
      for (int i = 0; i < T->table_size_M; i++)
      {
         if (T->data_arr[i].key == -1)
            delete_count++;
      }

      return delete_count;
 }



 /*****************************************************************************
  * Insert a new table entry (K, I) into the table provided the table is not
  * already full.
  * Return:
  *      0 if (K, I) is inserted,
  *      1 if an older (K, I) is already in the table (update with the new I), or
  *     -1 if the (K, I) pair cannot be inserted.
  */
 int table_insert(table_t *T, hashkey_t K, data_t I){

      int i = K % T->table_size_M;
      int probe_decrement = T->type_of_probing_used_for_this_table;
      int num_probes = 1;

    // set probe_decrement to increment by the correct value
      if (probe_decrement == 2)
          probe_decrement = 4;
      else if (probe_decrement == 1)
          probe_decrement = 2;
      else
          probe_decrement = 1;

 // -1 represents a space that was previously deleted and can be filled in
 // 0 represents an empty spot
      while(T->data_arr[i].key > 0)
      {
          if (T->data_arr[i].key == K) // the key is already inserted
          {
            free(T->data_arr[i].data_ptr);
            T->data_arr[i].data_ptr = I;
            return 1;
          }

          i -= probe_decrement;
          if (i < 0)
              i += T->table_size_M;

          num_probes++;
      }

      if (T->num_keys_stored_in_table == T->table_size_M - 1)
          return -1;

      T->data_arr[i].key = K;
      T->data_arr[i].data_ptr = I;
      T->num_keys_stored_in_table++;
      T->num_probes_for_most_recent_call = num_probes;
      return 0;
 }



 /*****************************************************************************
  * Delete the table entry (K, I) from the table.
  * Return:
  *     pointer to I, or
  *     null if (K, I) is not found in the table.
  *
  * See the note on page 490 in Standish's book about marking table entries for
  * deletions when using open addressing.
  */
 data_t table_delete(table_t *T, hashkey_t K){

    int i = K % T->table_size_M;
    int probe_decrement = T->type_of_probing_used_for_this_table;
    int num_probes = 1;

    // set probe_decrement to increment by the correct value
      if (probe_decrement == 2)
          probe_decrement = 4;
      else if (probe_decrement == 1)
          probe_decrement = 2;
      else
          probe_decrement = 1;

    hashkey_t probe_key = T->data_arr[i].key;

    while (probe_key != K && probe_key != 0)
    {
        i -= probe_decrement;
        num_probes++;
        if (i < 0)
            i += T->table_size_M;
        probe_key = T->data_arr[i].key;
    }

    T->num_probes_for_most_recent_call = num_probes;
    if (probe_key == 0)
        return NULL;


    data_t temp = T->data_arr[i].data_ptr;
    T->data_arr[i].key = -1;
    return temp;

 }


 /*****************************************************************************
  * Given a key, K, retrieve the pointer to the information, I, from the table,
  * but do not remove (K, I) from the table.  Return NULL if the key is not
  * found.
  */
 data_t table_retrieve(table_t *T, hashkey_t K){

      int i = K % T->table_size_M;
      int probe_decrement = T->type_of_probing_used_for_this_table;
      int num_probes = 1;

      // set probe_decrement to increment by the correct value
        if (probe_decrement == 2)
            probe_decrement = 4;
        else if (probe_decrement == 1)
            probe_decrement = 2;
        else
            probe_decrement = 1;

      hashkey_t probe_key = T->data_arr[i].key;

      while ((probe_key != K) && (probe_key != 0))
      {
        i -= probe_decrement;
        num_probes++;
        if (i < 0)
            i += T->table_size_M;
        probe_key = T->data_arr[i].key;
      }


      T->num_probes_for_most_recent_call = num_probes;
      // Determine if success of failure
      if (probe_key <= 0)
          return NULL;

      return T->data_arr[i].data_ptr;

 }



 /*****************************************************************************
  * Free all information in the table, the table itself, and any additional
  * headers or other supporting data structures.
  */
 void table_destruct(table_t *T){

    for (int i = 0; i < T->table_size_M; i++)
    {
       free(T->data_arr[i].data_ptr);
    }
    free(T->data_arr);
    free(T);
 }



 /*****************************************************************************
  * Return the number of probes for the most recent call to table_retrieve,
  * table_insert, or table_delete
  */
 int table_stats(table_t *T){
    return T->num_probes_for_most_recent_call;
 }



 /*****************************************************************************
  * This function is for testing purposes only.  Given an index position into
  * the hash table return the value of the key if data is stored in this
  * index position.  If the index position does not contain data, then the
  * return value must be zero.  Make the first
  * lines of this function
  *       assert(0 <= index && index < table_size);
  */
 hashkey_t table_peek(table_t *T, int index){

 }



 /*****************************************************************************
  * Print the table position and keys in a easily readable and compact format.
  * Only useful when the table is small.
  */
 void table_debug_print(table_t *T){

      for (int i = 0; i < T->table_size_M; i++)
      {
          printf("%d - %d\n", i, T->data_arr[i].key);
      }

 }
