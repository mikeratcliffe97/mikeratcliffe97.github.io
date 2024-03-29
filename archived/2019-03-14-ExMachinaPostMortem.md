---
layout: post
title: Ex Machina Post Mortem
date: 2019-03-14
description:  Post mortem for my 2nd year LLP assignment
category: development
published: true
tags: [dev, blog, degree]
---

# Ex Machina


My last Low Level Programming assignment was a 2D Platformer based on the film *Ex Machina*.
It was my first experience of working as lead developer on a project, and I'd say it was successful.

<figure>
    <img src="../assets/img/ExMachina1.PNG">
   </figure>


## Key Features
I was very pleased with how the game ran under the hood, however much of this was not obvious to a user.
Some features were:
- A level editor based on an external .txt file 
- Graded highscores based on quality of gameplay. 
- Highscore saving and loading from file
- Basic animation cycles

<!--more-->
The level editor allowed us as a group to design levels very quickly and easily, by simply changing numbers in a text file. 
Where there was a 0, a background tile was rendered and where there was a 1, a platform was added. This was adapted later to add powerups but when it came to testing and level design, this saved a lot of time.
<figure>
    <img src="../assets/img/ExMachina3.PNG">
   </figure>

### Leaderboard and File Handling
In each level there was a collectible star and the player's time was recorded. Based on the time and whether the star was collected, the player was assigned a score from 'S' to 'F'. This score was saved to an external file and read back in when needed and could be viewed on a leaderboard.
Unfortunately, on demo day, we had to remove this feature as it was unstable and caused crashes. I would like to continue working on it and fix it as our feedback for the game asked for more 'replayability' and I think this would cover that base. Players would be able to try and beat their high scores on each level.

### Sprites Animations
One feature which I did not work on but really liked in the game was sprite animation. We had a different character sprite for each level to symbolise the AI (the playable character) getting smarter (similar to the film). 
These sprites had a basic running animation which updated about 5 times per second.
As well as this we had a death screen showing Nathan, the evil (or atleast morally questionable) creator of the AI in the film, laughing manically. This helps create immersion for the player and further links gameplay to the film.
<figure>
    <img src="../assets/img/ExMachina2.PNG">
   </figure>

