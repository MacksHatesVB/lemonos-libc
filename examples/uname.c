#include <sys/utsname.h>
#include <stdio.h>

int main() {
	struct utsname name;
	uname(&name);
	printf("%s %s %s %s %s\n", name.sysname, name.nodename, name.release, name.version, name.machine);
	return 0;
}
