# Reaction Time Game Build Journal

## Jul 9, 2026, 9:34 PM

## Reaction Time Game
### Journal 1

I've been working on this reaction time game. I'm really new at all of this, and this is the first time I've done anything electrical related. 

I had made another project following the workshop, and it was a simple LED controlled by a button and a potentiometer.

I wanted to try something more ambitious, and decided to make some kind of game, since that's what I always do. (I usually do Game Dev in Unity using C#)

Luckily, C# is very similar to this language, which I think is c++.

It took me quite a bit of time to figure out how to wire the lcd and adapter together, but it works, though I'm not sure if it's correct.

So far, I just made it display Hello World and am going to add a button and all that later on.

---

## Jul 9, 2026, 10:59 PM

## Reaction Time Game
### Journal 2

I've mostly been working on fixing a lot of problems. I got some basic code to blink the LED which was not working for like 20 minutes, and then randomly started to work.

I didn't really add much, just tested various stuff, so not much to write.

---

## Jul 10, 2026, 3:53 AM

## Reaction Time Game
### Journal 3

I've gotten some good work done. Most of my circuit work is done, now I'm just focusing on the code. 

I got a lot of base functions ready, and now the LCD says some basic stuff like Click or Get Ready. It's not finished and there are a lot of bugs, but good progress.

---

## Jul 10, 2026, 8:31 PM

## Reaction Time Game
### Journal 4

I've been working on the code this whole time, and I've gotten some good progress done. 

I got the main reaction test ready, so you can technically play it. But I am facing issues with the text overflowing. I tried to use scrollDisplayLeft(), but for some reason it doesn't do anything, which is weird.

Instead, what I'm doing is basically making the screen of the reaction time and the screen of asking to click the button to play again switch back and forth. I don't want it to switch permanently since I want the reaction time result to show, so this is a good alternative.

After I finish this, I have to make the button reset the game, and also add all the extra cases, like if the user clicks the button early, or takes too long (to prevent ms text from overflowing, I'll set a limit of 15 seconds).

I also had encountered a bug which took me so long to fix, even after trying to debug. It turns out I had to just make the variable update before the if-else statement, so it took me like 30 minutes to figure that out.

I have to finish all of that by the fifteenth, which I think I will do. 

This is kind of more fun than game dev at least temporarily, since I've not done things like this before, so it's new. Though I bet in a few days I'll get bored of it.

---

## Jul 10, 2026, 10:00 PM

## Reaction Time Game
### Journal 5

I think the main code is basically done. All I have left to do is add those extra cases, and then I think there is nothing else to do. 

I may add some extra features later, like a best time or something, but I'll probably keep it simple.

The main change I did with the code was making the game state an enum instead of a lot of bools, so it became much easier to manage. I probably didn't need to do that since I'm basically done, but I like clean code.

I was facing a few bugs, but was able to fix them. For some reason, I keep on using == to set a value instead of just a single =, and I also keep forgetting to finish lines with a semicolon. I don't get why I keep forgetting those things, since when I code in Unity I never really forget that, and they're the same in both languages.

Anyways, it's going good. I don't know how I'm actually going to build it in real life when I get the parts, since I don't have a soldering thing or whatever it is called, and I'm not sure if they are going to be provided. I don't even know if I an just do the whole thing with wires. Still new to all this electrical stuff.

Thanks!

---

## Jul 10, 2026, 11:42 PM

## Reaction Time Game
### Journal 6

I think I'm done. My family tried it out, and it worked perfectly. If you click too early, you fail, and if you take longer than 10 seconds, you fail.

There is something really weird though. To my knowledge, 1000 ms, is one second. But when I wait 10,000 ms, it only waits five seconds. Same problem with the reaction speed, with it being twice as big as it is supposed to be.
I think the millis() is going twice as fast, but I have no idea why. I adjusted to make it work like that, but it may cause problems when I build if it is different there.

Anyways, I'm probably going to publish it.

Thanks!