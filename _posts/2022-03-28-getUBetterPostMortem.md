---
layout: post
title: My Time at getUBetter
date: 2022-03-28
description: Ask Mike, he'll know
category: Personal
published: true
tags: [blog, project management, app]
---

### getUBetter Summary

Since January 2021, I've been working at the digital health startup, [getUBetter](https://getubetter.com/), based in Bristol.
getUBetter is a digital platform which provides self-management support for common musculoskeletal injuries. It is comprised of a mobile app and a web app.
I worked as the <b>Project and Technical Support Engineer</b>, which has been a great experience. I've left on very good terms to start my trip around the world! 

## My Role
Project and Technical Support Engineer is a vague title. When I joined the company, there were only 7 people on the team. I was hired to: support the COO and developer with planning and tracking development items, working with the developer to maintain, upgrade and create documentation for the IT infrastructure, provide IT support to other team members, and handle customer relations, including user complaints and managing the social media accounts.

## Project Support

Using our project management software, I would meet weekly with the COO and developer to schedule develop items, track progress of items in development, schedule testing and updates.
Shortly after joining, I noticed that the company did not have much data on how updates were being recieved by the users. I worked with the developer to create SQL reports from our database which tracked user interaction with the app, such as:
* how many users logged in each day after an update
* which sections of the app they were visiting
* how long they spent in each section

I created spreadsheets and reports to present this data to the whole team, which allowed us to identify areas where we were underperforming or where users were experiencing difficulties. I would then create wireframe designs of potential solutions to these issues which would be designed properly by our UI designer, implemented by our developer, and I would test the changes to ensure the initial problems I identified had been solved.

These reports increased our user retention and user satisfaction significantly. For example, after identifying and solving issues with our log in page, the number of reoccurent visitors increased by 17% in the first month following our changes.

## IT Support Engineer

As we were such a small team, a big part of my role was handling day-to-day IT roles to allow our developer to work on implementing new features. This included:
* Setting up computers for new team members
* Giving new team members an IT induction and system walkthrough
* Resolving technical issues for team members and customers
* Creating documentation for the IT infrastructure.

### Personal Achievements
The things I am most proud of during my time at getUBetter are:

* Optimising the registration process and medical screening questionnaire, making it easier to log in and access features in the app 
    * a large of the user base are older patients who struggle with technology, so it was important to make this process as simple as possible and provide a lot of instructions that were simple and easy to read
* Increasing accessibility to the app, by adding text sizing options and adding subtitles to the exercise video library in 9 different languages
    * Our clients reported that many of the users were not native English speakers and would benefit from subtitles on the in-app exercise videos, so I devised a system using the AWS suite to automatically transcribe our exisiting videos, and translate the subtitle files into 9 different languages.
* Securing our IT Infrastructure and qualifying for the CyberEssentials award
    * As the app is a medical device, we had a responsibility to ensure we looked after our users' data. I personally made sure all of our work devices were cyber secure, configured a clone of our Apache server to allow external pentesters to test our security without disrupting our live operation or exposing user data. and created documentation about what to do in the event of a data breach. As a result were were awarded the CyberEssentials certification.
* Creating a disaster recovery plan
    * I configured a clone of our live server so that in the event of an outage, we could minimise downtime. I also wrote documentation about how to report a disaster, including how to detect a disaster, who to inform, and how to swap our live operation onto the backup server.

