#pragma once

typedef struct db_key {
	char * name;
	struct db_key * back;
	struct db_key * next;
} db_key_t;

typedef struct db_kv {
	char * name;
	char * value;
	struct db_kv * back;
	struct db_kv * next;
} db_kv_t;

typedef struct db_entry {
	db_kv_t * keys;
	struct db_entry * back;
	struct db_entry * next;
} db_entry_t;

typedef struct db_table {
	char * name;
	db_key_t * keys;
	db_entry_t * entries;
	struct db_table * back;
	struct db_table * next;
} db_table_t;

typedef struct {
	char * name;
	db_table_t * tables;
} db_t;

db_t * db_create(char * name);
db_table_t * db_create_table(db_t * db, char * name, char ** keys, int len);
db_table_t * db_find_table(db_t * db, char * name);
void db_insert(db_t * db, char * name, char ** values, int len);
