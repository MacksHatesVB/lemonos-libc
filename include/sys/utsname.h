#pragma once

// 64 + null
#define UTSNAME_ITEM_LENGTH 65

struct utsname {
	char sysname[UTSNAME_ITEM_LENGTH];
	char nodename[UTSNAME_ITEM_LENGTH];
	char release[UTSNAME_ITEM_LENGTH];
	char version[UTSNAME_ITEM_LENGTH];
	char machine[UTSNAME_ITEM_LENGTH];
	char domainname[UTSNAME_ITEM_LENGTH];
};

typedef struct utsname uname_t;

int uname(struct utsname * name);
