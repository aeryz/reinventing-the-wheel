#include "ctl_str.h"
#include <stdio.h>


int main() {
	ctl_str str1;
	ctl_str str2;
	ctl_str_from("selameke", &str1);
	ctl_str_from("cool and very very very long strrrssss", &str2);
	ctl_str_debug(&str1);
	ctl_str_debug(&str2);
	ctl_str_concat(&str1, &str2);
	ctl_str_debug(&str1);
	ctl_str_concat(&str2, &str1);
	ctl_str_debug(&str2);
}
