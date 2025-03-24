#include <db.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void print_line(int i) {
	while (i--) {
		putchar('-');
	}
	putchar('\n');
}

void print_db(db_t * db) {
	printf("name: %s\n\n", db->name);

	db_table_t * table = db->tables;
	while (table) {
		printf("table name: %s\n", table->name);

		db_key_t * keys = table->keys;
		putchar('|');
		while (keys) {
			printf(" %s |", keys->name);
			keys = keys->next;
		}
		putchar('\n');

		db_entry_t * entries = table->entries;
		while (entries) {
			db_kv_t * kv = entries->keys;
			putchar('|');
			while (kv) {
				printf(" %s |", kv->value);
				kv = kv->next;
			}
			putchar('\n');
			entries = entries->next;
		}
		putchar('\n');

		table = table->next;
	}
}

int main(int argc, char * argv[]) {
	db_t * db = db_create("mydb");
	db_table_t * table = db_create_table(db, "table", (char *[]) {"key", "key2"}, 2);
	db_insert(db, "table", (char *[]) {"value", "value2"}, 2);
	db_insert(db, "table", (char *[]) {"value3"}, 1);

	db_table_t * table2 = db_create_table(db, "table2", (char *[]) {"key3", "key4"}, 2);
	db_insert(db, "table2", (char *[]) {"value4", "value5"}, 2);
	db_insert(db, "table2", (char *[]) {"value6"}, 1);

	print_db(db);
	free(db);
}
