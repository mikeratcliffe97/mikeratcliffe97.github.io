---
layout: post
title: GEP Dev 1
date: 2019-01-22
description: First development blog for Mario Kart
category: development
published: true
tags: [dev, blog, DX]
---

This is the first entry in my dev diary for Mario Kart.
As a group, we've been assigned the task of making mario kart using the Scarle Engine, a 3D game engine built on DirectX.

Initially, we created an 'alpha' version using Unity and identified all the features our game would need, including:

Splitscreen cameras
Driving physics and Collision
Controller (Gamepad) Support
Artificial Intelligence for NPCs
Lap Clock/Timer system
Collectibles/Items (powerups etc)

This was achieved, minus the AI, and we've started working in the Scarle Engine.
I've created a basic scene manager, similar to ones I've used in other modules, and have began working on importing 
models into the game for courses and player characters. I'm learning a lot about rendering 3D models and textures in C++. 
I initally struggled as I called the wrong .mtl file so the renderer couldn't find any textures. *Syntax*.

Next to do is applying physics to these models.



