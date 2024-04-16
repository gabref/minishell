# Expansor

## Visit nodes of tree

The **Execute Binary Tree** is composed by nodes like this:

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

The expansor responsability is to visit all the nodes in the ebt (executor binary tree) and expand all necessary variables. <br>

### Traverse a tree
There are several algorithms to traverse a tree (or visit all nodes), the one that makes more sense for this project is the inorder traverse method, that will visit first all the nodes to the left, then the node itself, and the all to the right.
<br>
It is easy to achieve that with a recursive function like this:
```c
void inorder_traversal(t_ebt *root)
{
    if (root == NULL)
        return ;
    inorder_traversal(root->left);
    visit(root);
    inorder_traversal(root->right);
}
```

The visit function is where the expandor will shine! For all nodes that are a EBT_OP_COMMAND, expand
```c
void visit(t_ebt *node)
{
    if (node->type != EBT_OP_COMMAND)
        return ;
    ...
}
```

## Env variables
The command struct has a `key` called `args`. Usually the stuff to expand will always be in the args. 
<br>
For a command like:
```bash
ls $HOME/documents -l -a -h
```
the command will look something like this:
```
t_command->command = "ls"
t_command->args = ["$HOME/documents", "-l", "-a", "-h"]
...
```

after the expansion it should look like this:
```
t_command->command = "ls"
t_command->args = ["/home/gabre/documents", "-l", "-a", "-h"]
...
```

<br>

let's say $HOME does not exists, then the expansion should look like:
```
t_command->command = "ls"
t_command->args = ["/documents", "-l", "-a", "-h"]
...
```

A useful function to get the env variable is this:
```c
char				*ms_get_env(t_minishell *ms, char *key);
```
if the env variable exists, it will return the string that represents the env variable, else it will return NULL.

## Glob

This one is 'complicated'. Let's say we have a directory like this:
```bash
ciao.txt
main.c
we-young.mp3
bellissime-picture.png
roma-collection.zip
```

when we have a command like this:

```
t_command->command = "ls"
t_command->args = ["*a*", "-l", "-a", "-h"]
...
```

it should look like this after the expansion:

```
t_command->command = "ls"
t_command->args = ["ciao.txt", "main.c", "roma-collection.zip", "-l", "-a", "-h"]
...
```
