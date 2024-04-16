# Executor

The executor is the last step in the shell pipeline. It is responsible for executing the commands that were parsed and expanded by the parser and the expandor, respectively.

## Binary Executor Tree

The executor uses a binary executor tree (ebt) to store the commands to be executed. The ebt is a binary tree where each node is a command to be executed. The tree is built by the parser and expanded by the expandor.

```c
/*
 * Binary Executor Tree
 *		- command: command to be executed (if type is EBT_OP_COMMAND, else NULL)
 *		- type: type of operation
 *		- left: left node
 *		- right: right node
 */
typedef struct s_ebt
{
    t_command		*command;
    t_ebt_op		type;
    struct s_ebt	*left;
    struct s_ebt	*right;
}					t_ebt;
```

## Tree examples
The tree may look like this for each of the following examples:

### Simple command
<img src="../assets/ms-command.png" width="200" />

### Pipe
<img src="../assets/ms-command-pipeline.png" width="600" />

### Operators
<img src="../assets/ms-command-operators.png" width="600" />

### Substitution and Semicolon
<img src="../assets/ms-command-substitution-semicolon.png" width="600" />

### Subshell
<img src="../assets/ms-command-subshell.png" width="800" />
