/*
 * vdso_readelr.c: Sample code to test parse_vdso.c
 *
 * Subject to the GNU General Public License, version 2
 *
 * Compile with:
 * gcc -std=gnu99 vdso_readelf.c parse_vdso.c
 *
 */

#include <stdint.h>
#include <elf.h>
#include <stdio.h>
#include <sys/auxv.h>
#include <sys/time.h>
#include <sys/types.h>
#include <inttypes.h>
#include <time.h>

#include "parse_vdso.h"

int main(int argc, char **argv)
{
	char s[32];
	struct vdso_info *p = &vdso_info;
	unsigned long sysinfo_ehdr = getauxval(AT_SYSINFO_EHDR);
	typedef int (*func_t)();
	func_t func;

	if (!sysinfo_ehdr) {
		printf("AT_SYSINFO_EHDR is not present!\n");
		return 0;
	}

	vdso_init_from_sysinfo_ehdr(getauxval(AT_SYSINFO_EHDR));

	printf("%-16p\t%-20s\n\n", (void *)p->load_addr, "vdso address");
	printf("%-16s\t%-20s\n", "Address", "Name");

	strcpy(s, "clock_gettime");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	strcpy(s, "__vdso_gettimeofday");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	strcpy(s, "__vdso_getcpu");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	strcpy(s, "gettimeofday");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	strcpy(s, "time");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	strcpy(s, "getcpu");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	strcpy(s, "__vdso_clock_gettime");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	strcpy(s, "__vdso_time");
	func = (func_t)vdso_sym("LINUX_2.6", s);
	printf("%-16p\t%-20s\n", func, s);

	return 0;
}
