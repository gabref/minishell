#include "../inc/minishell.h"
#include "../inc/initializers.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

t_minishell	ms;

void suite_setup(void)
{
	init_minishell(&ms, NULL);
}

void suite_teardown(void)
{
	destroy_minishell(&ms);
}

TestSuite(init_minishell, .init=suite_setup, .fini=suite_teardown);

Test(init_minishell, create)
{
	cr_assert_not_null(ms.env);
	cr_assert_eq(ms.history.inputs, NULL);
	cr_assert_eq(ms.history.cur_idx, 0);
	cr_assert_eq(ms.ebt, NULL);
	cr_assert_eq(ms.last_exit_status, 0);
	cr_assert_gt(ms.pid, 0);
}

Test(init_minishell, history)
{
	ms_append_history(&ms, "ls -l");
	ms_append_history(&ms, "ls -la");
	ms_append_history(&ms, "pwd");
	ms_append_history(&ms, "ls -la | grep ciao");
	ms_append_history(&ms, "bella > stdout");
	ms_append_history(&ms, "jq {}");
	cr_assert_str_eq(ms.history.inputs->content, "jq {}");
	cr_assert_str_eq(ms.history.inputs->next->content, "bella > stdout");
	cr_assert_str_eq(get_history_idx(&ms, 0), "jq {}");
	cr_assert_str_eq(get_history_idx(&ms, 2), "ls -la | grep ciao");
	cr_assert_str_eq(get_history_idx(&ms, 5), "ls -l");
	cr_assert_null(get_history_idx(&ms, 6));
	cr_assert_null(get_history_idx(&ms, -1));
	destroy_history(&ms);
	cr_assert_null(ms.history.inputs);
}

Test(init_minishell, envs)
{
	char	*env[] = {"PATH=/usr/bin", "PWD=/home", "USER=me", NULL};
	init_minishell(&ms, env);
	cr_assert_str_eq(ms_get_env(&ms, "PATH"), "/usr/bin");
	cr_assert_str_eq(ms_get_env(&ms, "PWD"), "/home");
	cr_assert_str_eq(ms_get_env(&ms, "USER"), "me");
	cr_assert_null(ms_get_env(&ms, "LOGPOSE"));
	cr_assert_null(ms_get_env(&ms, "SHELL"));
	ms_set_env(&ms, "SHELL", "/bin/sh");
	ms_set_env(&ms, "LOGPOSE", "whatever");
	cr_assert_str_eq(ms_get_env(&ms, "SHELL"), "/bin/sh");
	cr_assert_str_eq(ms_get_env(&ms, "LOGPOSE"), "whatever");
}
