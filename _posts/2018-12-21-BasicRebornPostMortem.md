---
layout: post
title: Game 1 Post Mortem
date: 2018-12-21
description: C++ Port of a BASIC text adventure game
category: Post Mortem
published: true
tags: [retro, c++, text, adventure, ASGE, degree]
---
# Basic Reborn
<figure>
    <img src="../assets/img/BR3.JPG">
    </figure>
For my first second year assignment, we were asked to convert this **[game](http://www.colorcomputerarchive.com/coco/Documents/Books/Write%20Your%20Own%20Adventure%20Programs%20(1983)(Usborne).pdf)** into C++ using the ASGE Engine.

To fully modernise my game, I decided to base my game on a spaceship instead of a haunted house. I wanted to keep a horror element, so loosely based the game on the horror game, Dead Space.
<figure>
    <img src="../assets/img/deadspace.jpg">
 </figure>
    
## Key Features
 - This was my first game that used text validation
 - The game relied heavily on file reading for:
    - the route that the player uses
    - the items that the player can collect
  <figure> 
    <img src="../assets/img/BR1.jpg">
   </figure>
   
   <figure>
    <img src="../assets/img/BR2.JPG">
   </figure>
    
   As I was mainly focused on the technical aspects, I did not have much time to focus on design aspects for the game.
   To improve in future I would change background sprites and font, and possibly music. <br>
   I was happy with my use of classes and basic file handling, I set up a class for the items which was inherited by the class for the 
   rooms. This made my code run efficiently and easy to read and debug.
    
