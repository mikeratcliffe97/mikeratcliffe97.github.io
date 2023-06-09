---
layout: post
title: Localisation and QA for getUBetter
date: 2022-06-01
description: Transcribing, translating and proof-reading subtitles for MSK exercise and advice videos
category: Project
published: true
tags: [project management, blog, app, localisation, QA]
---
 
## Localisation and QA for getUBetter

One of my last projects while working for getUBetter was to make their library of exercise and advice videos more accessible.
The app provided more than 200 videos, advising users on how to recover after injuries as well as demonstrating different exercises to help them return to their '*normal*' self.

### Requirements

In order to make these videos more accessible to users, we decided to:
* Transcribe each video
* Upload subtitle files in English onto the app, allowing users who had hearing difficulties to understand the videos
* Consult our NHS partners on which languages (other than English) they would like to see the videos in
* Translate our subtitle files into these languages

After consulting our NHS partners, we decided to translate our subtitle files into **9 other languages**.
  
These were: **Urdu, Bengali, Punjabi, Gujarati, Portuguese, Spanish, Welsh, French, Polish and Somali**. 
Translating over **200 videos into 9 different languages** involved handling, formatting and uploading **more than 1800 individual files**.


### Process
I searched for online translation software to translate files in large batches.

After some shopping around and tests, we decided to use AWS, as it could handle large quantities of files and translate them quickly and to a good degree of accuracy. However once the files had been translated, they were in the wrong file format and contained formatting errors which meant that the files could not be played by our video hosting platform.

I then developed Perl scripts to format the files in large quantities, searching the files and removing any incorrect formatting, as well as renaming them and converting them to the correct file format.

Once they were in the correct file format, it was a team effort to upload them into our platform and make them visible within the app.

### Result
I completed the translation and formatting side of the project, partly as a remote freelancer after leaving the company to travel, while the team in Bristol were responsible for sorting the videos into 'batches' based on condition and uploading the translated and formatted files into the platform.

I am proud of my contributions to this project, as it allows so many people to access and understand the library of advice and exercise videos. I learnt a lot about AWS, Perl and MacOS Automation and greatly improved my QA skills.