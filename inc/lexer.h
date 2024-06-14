#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	/* 0 */ WORD,          /* parola */
	/* 1 */ O_PARENTHESES, /* (, [, { */
	/* 2 */ C_PARENTHESES, /* ), ], } */
	/* 3 */ DOT,           /* . */
	/* 4 */ SEMICOLON,     /* ; */
	/* 5 */ COLON,         /* : */
	/* 6 */ COMMA,         /* , */
	/* 7 */ MARK,          /* ? e ! */
	/* 8 */ DOUBLE_Q,      /* " */
	/* 9 */ SINGLE_Q,      /* ' */
	/* 10 */ OPERATORS,    /* - e + */
	/* 11 */ N_LINE,       /* \n */
	/* 12 */ BSLASH,       /* \ */
	/* 13 */ TILDE,
	/* 14 */ AND,         /* & */
	/* 15 */ DAND,        /* && */
	/* 16 */ PIPE,        /* | */
	/* 17 */ OR,          /* || */
	/* 18 */ EXIT_STATUS, /* $? */
	/* 19 */ CMD_SUB,     /* dollaro + parentesi */
	/* 20 */ DOLLAR,      /* dollaro + parola che lo segue */
	/* 21 */ OUT_APPEND,  /* > e >> */
	/* 22 */ IN,          /* < */
	/* 23 */ HEREDOC,     /* << */
	/* 24 */ INSTRUCTION, /* set e unset */
	/* 25 */ GLOB,        /* asterisco + parola che lo segue e che lo precede */
	/* 26 */ END_OF_FILE
}					t_token_type;

typedef struct s_token
{
	int				input_start_idx;
	int				current_idx;
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	t_token			*tokens;
	int				size;
}					t_lexer;

/*lexer.c*/
t_lexer				*lexer(char *input);

/*lexer_utils.c*/
void				free_and_quit(t_lexer *lexer, char *token);

int					init_lexer(t_lexer *lexer);
void				free_lexer(t_lexer *lex);
void	print_lexer(t_lexer *lex); // DA CANCELLARE

/*minilib.c*/
char				*ft_substr_lex(char *s, int start, int len);
int					ft_strncmp_lex(char *s1, const char *s2, int n);
int					ft_strlen_lex(char *s);
void				ft_putstr_fd(char *s, int fd);

/*minilib_2*/
void				*ft_memcpy_lex(void *dest, void *src, int n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *src);
int					strchr_lex(char *str, char c);

/*minilib3*/
int					ft_isalnum_lex(char c);
int					ft_isprint_lex(int c);
void				recur_list_dalloc(t_token **root);

int					add_end(t_token **ret, char *str, int strt, int end,
						t_token_type type);

/*tokenizer.c*/

int					token_finder(char *trim_input, t_token_type *type);
int					tokenizer(t_lexer *lex_struct, char *input);

/*token_1*/
int					is_parentheses(char *trim_input, t_token_type *type);
int					is_mark(char *trim_input, t_token_type *type);
int					is_quote(char *trim_input, t_token_type *type);

/*TOKEN_2*/
int					is_punctuation(char *trim_input, t_token_type *type);
int					is_nline_bslash_tilde(char *trim_input, t_token_type *type);
int					is_logical_or_pipe(char *trim_input, t_token_type *type);

int					is_redir_or_her(char *trim_input, t_token_type *type);

int					is_operator(char *trim_input, t_token_type *type,
						int *count);

/*token_3*/
int					is_dollar(char *trim_input, t_token_type *type, int *count);
int					is_exti_or_cmd_sub(char *trim_input, t_token_type *type);
int					is_istruction(char *trim_input, t_token_type *type);
int					is_globe(char *trim_input, t_token_type *type, int *count);
int					is_word_or_glob(char *trim_input, t_token_type *type,
						int *count);

#endif
