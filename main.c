#include <stdio.h>
#include <cpufeats.h>

int main(int argc, char * argv[]) {
	char buffer[92];
	cpu_get_vendor_name(buffer);
	printf("CPU Vendor: %s\n", buffer);
	cpu_get_model_name(buffer);
	printf("CPU Model: %s\n", buffer);

	sprintf(buffer, "hi %r hi\n", buffer);
	puts(buffer);
}
