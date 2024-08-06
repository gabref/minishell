#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef enum e_token_type
{
	/* 0  */ WORD,          /* parola */
	/* 1  */ O_PARENTHESES, /* (, [, { */
	/* 2  */ C_PARENTHESES, /* ), ], } */
	/* 3  */ DOT,           /* . */
	/* 4  */ SEMICOLON,     /* ; */
	/* 5  */ COLON,         /* : */
	/* 6  */ COMMA,         /* , */
	/* 7  */ MARK,          /* ? e ! */
	/* 8  */ DOUBLE_Q,      /* " */
	/* 9  */ SINGLE_Q,      /* ' */
	/* 10 */ OPERATORS,     /* - e + */
	/* 11 */ N_LINE,        /* \n */
	/* 12 */ BSLASH,        /* \ */
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
	/* 26 */ END_OF_FILE,
	/* 27 */ O_BRACKETS,       /* ( */
	/* 28 */ C_BRACKETS,       /* ) */
	/* 29 */ O_CURLY,          /* { */
	/* 30 */ C_CURLY,          /* } */
	/* 31 */ O_SQUARE,         /* [ */
	/* 32 */ C_SQUARE,         /* ] */
	/* 33 */ O_ANGLE_BRACKET,  /* > */
	/* 34 */ C_ANGLE_BRACKET,  /* < */
	/* 35 */ O_DANGLE_BRACKET, /* << */
	/* 36 */ C_DANGLE_BRACKET, /* >> */
}					t_token_type;

typedef struct s_token
{
	int				input_start_idx;
	int				current_idx;
	char			*value;
	t_token_type	type;
}					t_token;

typedef struct s_lexer
{
	t_list			*tokens;
	int				size;
}					t_lexer;

/*lexer.c*/
t_lexer				*lexer(char *input);
void				free_lexer(t_lexer *lex);

void				test_print_token(void *ptr);
void				ms_print_lexer(t_lexer *lex);

#endif
