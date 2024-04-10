# Minishell Research and Planning

## Repositories
* [Nice explanation of the project](https://github.com/maiadegraaf/minishell)
* [Evaluation Sheet](https://42evals.com/Cursus/minishellhttps://42evals.com/Cursus/minishell)
* [Walkthrough of the project + cool image at the end](https://github.com/migmanu/minishell?tab=readme-ov-file)

## Articles
* [Building mini bash (guy went for AST)](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)
* [Very noice article with references - High level explanation](https://haglobah.github.io/Mastering-42/holy_graph/minishell.html)
* [Interesting collection of references](https://minishell.simple.ink/)
* [Nicee explanation of each of the allowed functions - use google translator](https://velog.io/@chez_bono/Minishell)
* [Bigger Picture](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)
* [Suspectedoceano collection of resources](https://suspectedoceano.notion.site/Cursus-97a5ef0ea22b47779a24de1299e53e9b)

## Important
* [List of edge cases](https://docs.google.com/spreadsheets/d/1TDwyd-S0WBAXehgkrKQtBJ6zquQ4p6k7JfE5g3jICNA/edit#gid=0)
* [List of more edge cases, but not to worry too much](https://docs.google.com/spreadsheets/u/0/d/1uJHQu0VPsjjBkR4hxOeCMEt3AOM1Hp_SmUzPFhAH-nA/htmlview?lsrp=1#gid=0)

## About git for who wants to learn more
[Git for beginners](https://learngitbranching.js.org/)

## Some random intereseting links
* [Noice simple version of shell](https://brennan.io/2015/01/16/write-a-shell-in-c/)
* [Another simple version of shell](https://www.geeksforgeeks.org/making-linux-shell-c/)
* [The pdf in 42docs](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

## Some practice Studies
* [AST in typescript](./ast-example-js/)
* [AST in C](./ast-example-c/)

# PLANNING AND DIVISION OF TASKS

### Requirements
* [x] Mandatory part
* [ ] Bonus part (will do?)

## Parts of the Program
<br>

```
INIT_MINISHELL -> GET_USER_DATA -> LEXER -> EXPANDER -> PARSER -> EXECUTOR
```

### INIT_MINISHELL
* [ ] Initialize structure minishell
    ```c
    typedef struct s_minishell
    {
        t_list  *env; // or hashmap
        t_list  *commands;
        pid_t   pid; // pid of the shell
        pid_t   *pids; // pids of the children
        char    **history; // history of commands
    } t_minishell;
    ```
* [ ] Initialize environment variables
    * SHLVL - shell level
    * PWD - present working directory
    * HOME - home directory
    * OLDPWD - old present working directory
    * PATH - path to the executables
    * _ - name of the shell

### GET_USER_DATA
* [ ] Get user input
    * [ ] Handle signals
        * need a function handle_exit, that frees all the memory of all parts of the program
    * [ ] Create prompt
        * Print the prompt ($> )
    * [ ] Read line
    * [ ] Add to history

### LEXER
* [ ] Tokenize the input (return a list of tokens)
    * [ ] Handle quotes
    * [ ] Handle escape characters
    * [ ] Handle redirections
    * [ ] Handle pipes
    * [ ] Handle semicolons
    * [ ] Handle newlines
    * [ ] Handle EOF

Lexer will return a list of tokens <br>
The lexer structure could look like this:
```c
typedef enum e_token_type
{
    WORD,
    PIPE,
    SEMICOLON,
    GREAT,
    DGREAT,
    LESS,
    DLESS,
    NEWLINE,
    AND,
    OR,
    EOF
} t_token_type;

typedef struct s_token
{
    // first two are for debugging porpuses
    int         input_start_idx;
    int         current_idx;
    char        *value;
    t_token_type type;
} t_token;

typedef struct s_lexer
{
    t_list *tokens;
    int     size;
} t_lexer;

/** 
  * input will be the entry string from the prompt
  * return will have a list of tokens that represent the input
  */
t_lexer *lexer(char *input);
```

### EXPANDER
* [ ] Expand the tokens
    * [ ] Handle environment variables
        example: $HOME -> /home/user (attention to quotes double quotes edge cases)
    * [ ] Handle tilde
        * ~ -> home directory
    * [ ] Handle wildcard (bonus) -> glob -> create a copy of the command with the wildcard expanded
    * [ ] Handle command substitution 
        * example: echo $(ls) -> execute ls and replace the $(ls) with the output of the command

### PARSER
* [ ] Parse the tokens (return a list of commands)
    * [ ] Handle redirections
    * [ ] Handle pipes
    * [ ] Handle semicolons
    * [ ] Handle newlines
    * [ ] Handle EOF

Parser will return a list of commands <br>
Each command could look like this:
```c
typedef struct s_command
{
    char    *command;
    char    **args;
    char    *heredoc_file_name;
    t_token *fd;
} t_command;

typedef struct s_commands
{
    t_list *commands;
} t_commands;
```

### EXECUTOR
* [ ] Execute the commands
    * [ ] Handle redirections (open files and redirect stdin, stdout, stderr)
    * [ ] Handle executables
        * [ ] Handle builtins
            * [ ] echo
            * [ ] cd (cd - and cd ~)
            * [ ] pwd
            * [ ] export
            * [ ] unset
            * [ ] env
            * [ ] exit
    * [ ] wait for the children to finish and handle errors
    * [ ] clean memory, loop will restart
