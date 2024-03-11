# Doom_hunter

In this project we had to recreate a _Duck Hunt_ like game using the _CSFML_ lib.

# Compilation

Compilation work using Makefile, you can use:

```
make
```

To compile the project

```
make clean
```

To remove ".o" files

```
make fclean
```

To remove ".o" files and the executable

```
make re
```

To recompile the project

## Execution

To execute the project, use the name specified in the Makefile _NAME_ variable, by default it's: _my_hunter_

```
./my_hunter
```

# The game

Click on the enemy to shoot them, you have 3 lives, if you let an enemy passed you by, you lose one life, the more your enemy kill streak increase, the more enemy go fast and the more you gain point, you have to wait for your gun to reload to shoot again.
