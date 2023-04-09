# About the project

Bun is a simple jumping game developed in C++ with the SFML library. 
It was a way for me to practice C++ development (which I am new to) and learn to produce clean and documented code.

# How to install?
You simply need to clone or download this repository, and run the `bun.exe` file. 
If you are using an IDE, you can also run the `main` function from there.

:warning: Make sure not to move the files around, otherwise the `bun.exe` file 
might not be able to find the `asset` folder that contains necessary sprites and text fonts.

# How to play?

## :warning: Known issue
At the moment, the duration of game loops that process events and render the game is dependent on the machine.
If you have a machine that is significantly faster or slower than mine, you might experience major issues such as the bunny not being able to jump high enough to reach platforms.

This issue could be fixed by implementing fixed time steps as described in [this article](https://subscription.packtpub.com/book/game+development/9781849696845/1/ch01lvl1sec11/game-loops-and-frames).
However, I won't be fixing the issue for now since this game is just a small personal project that I don't plan on actually distributing.
Feel free to suggest a fix if that's something you're interested in!