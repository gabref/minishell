# Testing

## Requirements

Requirements to test de project:
```bash
apt-get install libcriterion-dev
```

`make test` to run the tests.
<br>
The tests are in the `tests` folder. We are using the Criterion library to test the project.
The tests are very useful to make sure the functionalities of the functions are working as expected.
Put your tests directly under the `tests` folder: `tests/test_*.c`.

## Memory Leaks
To test memory leaks we are using the `valgrind` tool.
```bash
make valgrind
```
If you want to test specific function for memory leaks, just create a main.c (i'm using the tests folder) and include the function you want to test.
Then in the `Makefile` at line 44 you can comment the original `MAIN` and uncomment the `MAIN` you created.
Then run `make valgrind` to test the memory leaks of the function you want.
