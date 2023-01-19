---
layout: post
title: Virtual Emergencies
date: 2022-08-07
excerpt: "Developing a training simulator for student doctors using VR"
category: Project
project: true
published: true
tags: [project management, VR, c#, Unity]
---

# Virtual Emergencies
In May 2021 I was approached by clinicians from an NHS trust in England to discuss developing a training simulator for student doctors.

## Brief
The clinicians wanted students to be able to practice medical procedures in a safe environment without the need for actors or the risk of harming real patients.
[br] Immediately, I knew that this could be achieved in a virtual space and jumped at the chance to take on this project.
After some scoping meetings, we decided that the project should have the functionality to:
* allow the user to move around and interact with objects in a virtual space, styled on a resuscitation room
* apply objects to a patient model 
    * (e.g. medicine and medical apparatus)
* interact with other NPC models and instruct them to perform tasks 
    * (e.g. preparing medical apparatus for the user to use)
* have the patient react to tasks with real-time visual and audio feedback 
    * (e.g. heartrate increasing on a monitor, patient fitting/spasming)


## Prototype
I set to work to find assets and build a prototype, with medical apparatus, <b>very</b> basic UI and object interaction. 
<br>This was my first progress video for the client - 
<iframe width="560" height="315" src="https://www.youtube.com/embed/zD6GKQpe4AU" frameborder="0"></iframe>

Client was impressed with the prototype and we decided on a project plan for the rest of the development. 

## September 22 Update
After working with another developer, we added most of the aspects of the project plan including:
* applying objects to an animated patient model
* interactions with NPCs
* real-time visual and audio feedback
* realistic sounds 
<iframe width="560" height="315" src="https://www.youtube.com/embed/99EmaD-wZds" frameborder="0"></iframe>

We included two modes for the simulation - an educational mode where the user is given prompts such as where to place the ECG cables on the patient and what condition the patient is suffering from, and an assessed mode where the user is given know prompts and must diagnose the patient and choose the correct procedure to treat them.

After this update, the only work left to do was testing and fine tuning based on client feedback, to ensure that the simulation was highly accurate, to allow the best educational experience for users.