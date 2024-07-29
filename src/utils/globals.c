#include "../../inc/utils.h"

static int g_signal;

void set_global_signal(int signum)
{
	g_signal = signum;
}

int get_global_signal(void)
{
	return (g_signal);
}
