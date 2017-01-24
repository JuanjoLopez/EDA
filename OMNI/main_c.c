#include <stdio.h>

#include "Comni.h"

int main()
{

	Comni *t = NULL;

	t = omnisequential_new();

	omni_query(t,"juanj",2);

	return 0;
}