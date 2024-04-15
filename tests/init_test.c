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
	append_history(&ms, "ls -l");
	append_history(&ms, "ls -la");
	append_history(&ms, "pwd");
	append_history(&ms, "ls -la | grep ciao");
	append_history(&ms, "bella > stdout");
	append_history(&ms, "jq {}");
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
