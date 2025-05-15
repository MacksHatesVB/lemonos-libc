#include <stdio.h>
#include <string.h>
#include <cpufeats.h>

int main(int argc, char * argv[]) {
	char buffer[92];
	cpu_get_vendor_name(buffer);
	printf("CPU Vendor: %s\n", buffer);
	cpu_get_model_name(buffer);
	printf("CPU Model: %s\n", buffer);

	strncpy(buffer, "hello world", 4);
	puts(buffer);
}
