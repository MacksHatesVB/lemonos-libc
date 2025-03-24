#include <db.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

db_t * db_create(char * name) {
	db_t * db = malloc(sizeof(db_t));
	db->name = strdup(name);
	db->tables = NULL;
	return db;
}

db_table_t * db_leaf_table(db_table_t * list) {
	if (!list) {
		return NULL;
	}
	while (list->next) {
		list = list->next;
	}
	return list;
}

db_entry_t * db_leaf_entry(db_entry_t * list) {
	if (!list) {
		return NULL;
	}
	while (list->next) {
		list = list->next;
	}
	return list;
}

db_table_t * db_append_table(db_table_t * list, db_table_t * table) {
	table->next = NULL;
	if (!list) {
		table->back = NULL;
		return table;
	}

	db_table_t * top = db_leaf_table(list);
	top->next = table;
	table->back = top;
	return list;
}

db_entry_t * db_append_entry(db_entry_t * list, db_entry_t * entry) {
	entry->next = NULL;
	if (!list) {
		entry->back = NULL;
		return entry;
	}

	db_entry_t * top = db_leaf_entry(list);
	top->next = entry;
	entry->back = top;
	return list;
}

db_table_t * db_create_table(db_t * db, char * name, char ** keys, int len) {
	db_table_t * table = malloc(sizeof(db_table_t));
	table->name = strdup(name);
	table->keys = NULL;
	table->entries = NULL;
	db->tables = db_append_table(db->tables, table);

	int i = 0;
	db_key_t * previous = table->keys;
	db_key_t * first = table->keys;
	while (len--) {
		db_key_t * key = malloc(sizeof(db_key_t));
		key->name = strdup(keys[i]);
		key->next = NULL;
		key->back = previous;

		if (previous) {
			previous->next = key;
		}
		if (!first) {
			first = key;
		}
		previous = key;
		i++;
	}
	if (!table->keys) {
		table->keys = first;
	}
	return table;
}

db_table_t * db_find_table(db_t * db, char * name) {
	db_table_t * list = db->tables;
	if (!list) {
		return NULL;
	}
	while (list) {
		if (strcmp(list->name, name) == 0) {
			return list;
		}
		list = list->next;
	}
	return NULL;
}

// db_table_t * db_create_table(db_t * db, char * name, char ** keys, int len) {
// db_entry_t * list, db_entry_t * entry
db_kv_t * db_create_kv(db_key_t * key, db_kv_t * previous, char ** values, int len, int i) {
	db_kv_t * kv = malloc(sizeof(db_kv_t));
	char * value = "null";
	kv->name = key->name;
	kv->back = previous;
	kv->next = NULL;
	if (i < len) {
		value = values[i];
	}
	kv->value = strdup(value);
	return kv;
}

void db_insert(db_t * db, char * name, char ** values, int len) {
	db_table_t * table = db_find_table(db, name);
	db_entry_t * entry = malloc(sizeof(db_entry_t));
	table->entries = db_append_entry(table->entries, entry);


	int i = 0;
	db_kv_t * previous = NULL;
	db_kv_t * keys = NULL;
	db_key_t * key = table->keys;
	while (key) {
		db_kv_t * kv = db_create_kv(key, previous, values, len, i++);
		if (previous) {
			previous->next = kv;
		} else {
			keys = kv;
		}
		previous = kv;
		key = key->next;
	}
	if (!entry->keys) {
		entry->keys = keys;
	}
}
