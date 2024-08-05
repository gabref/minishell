# Minishell

## TODOS
* [x] double quotes and single quotes escapes
* [x] only spaces or tabs as input
* [x] enter after ctrl-c with text already written "the buffer should be clean, press enter to make sure nothing from previous prompt is executed"
* [x] ctrl-c in the middle of a blocking command like cat
* [x] history
* [x] heredoc
* [x] glob

## Requirements

Requirements to test de project:
```bash
apt-get install libcriterion-dev
```

Also readline library is needed:
```bash
sudo apt-get install libreadline-dev
```

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

## Working commit before norminette
* (Working commit before norminette - f34a42d)[https://github.com/gabref/minishell/tree/f34a42d94fb072cc0eac350af50563ca90dea5fc]
