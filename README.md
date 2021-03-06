# Kwest Kingdom

## About

"Kwest Kingdom" is a simple turn-based strategy game. It features randomly generated worlds and tile based graphics.

As the hero, you work your way through a world full of enemies in order to reach the end. The game is turn based, but has been designed to feel as if things are taking place in real time. The world and location of the enemies are randomly generated each time you play.

## Gameplay

You goal is to make it through the forest. In the regular game mode, the game ends after forty rooms. You have a few weapons and items to help you make it to the end. You can't get hurt when you hold the shield, but be cautious! You will move around the screen more slowly while carrying a heavy shield. It will take two turns to use the bow and arrow: one to draw the arrow and aim and one to shoot.

Different enemies will try to stop your progress. The brown enemies, Chompers, will walk towards you when you get close. The red enemies, Ninjas, will dash at you andpoke you with their sword as soon as they see you. Look out! The green enemies with the beards, Archers, will shoot arrows at you. The enemies can be overbearing, but you have three health points to help you. When your health points reaches zero, it's the end of the game.

## Features

* An original game combining strategy with cute graphics
* Story mode and endless survival mode
* Nice animations and classic sound effects
* It's pretty fun!

## Reviews

draconishinobi, 5 stars:

> Interesting concept. It's actually quite easy when you know what to do (use shield and attack mostly with bow). It does require strategy, but it would be nice if it were a bit more challenging (scaling with levels) and less monotonous. *draconishinobi*, 5 stars

## Building

Kwest Kingdom is written in C++ using the Allegro 4 game programming library.

Compile time and runtime dependencies:

* allegro4: Portable library mainly aimed at video game and multimedia programming (legacy version)

The application icon for X is built using the "fix icon" script that comes with Allegro:

  tools/x11/xfixicon.sh

Built using GNU autotools and GCC:

  ./configure
  make
  make install

See "INSTALL" for more information.
