---
layout: post
title: Game 3 Post Mortem
date: 2019-04-09
description:  Mission Mars Post Mortem
category: development
published: true
tags: [dev, blog]
---

# <b> Mission Mars </b>

The last assignment of the year was to digitise a board game I had made as part of a group earlier in the year.
We had to turn this 4 player board game into a turn-based game over a network.

### Key Features
Part of the implementation was building a server to handle 4 different players connecting, assigning them usernames and allowing them to send text to each other (like a chat room) while holding all the relevant game data. 
We had some issues with different clients falling out of sync, so one player would be further ahead than others. 

We utilised the SoLoud audio engine to include sound effects and music to create a more immersive experience for the player.


