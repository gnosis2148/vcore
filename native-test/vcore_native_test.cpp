#include <stdio.h>
#include <vcore.h>
#pragma comment (lib, "vcore")


int	main (void)
{
	fprintf (stderr, "Starting vcore server\n");
	int rc = vcore_init ("../../native-test/test_config.txt");
	rc = vcore_start ();

	return 0;
}