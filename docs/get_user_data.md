# GET USER DATA

## Useful functions for history

```c
/* appends a user input line to the history */
void				append_history(t_minishell *ms, char *line);
/* gets a history line id, if id of history does not exists, returns null */
char				*get_history_idx(t_minishell *ms, int idx);
```
