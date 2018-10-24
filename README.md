# Calibration How-to.

## Introduction.
This document is a guide to keeping track and scoring predictions with my a .txt file and with my calibration program, and thus get me closer to a position in which 10 out of every 100 times I give something a probablity of 10%, it happens. 

I started writting this program because I was unaware of alternatives, like PredictionBook.com, and kept going because I liked a) being able to modify my program and b) being able to keep my predictions private. As of yet, there are some kinks to be smoothed out, though the barrier to entry should be no longer than 5-10 mins.

## Worked example.

### Data file.

You keep your predictions in a .txt or .md file. I call mine data.txt. The predictions are stored in the following format:

> Prediction statement; probability; result; date; comment (optional).

For example:

> I am able to press 50 pushups; 2; F; 6/7/2018; also made a bet with Vlad Firoiu.

The probability is a whole number between 1 and 99, because I didn't expect to be able to need much more granularity. However, I was proven wrong: when considering the probability that Atiyah's proof of the Riemann hypothesis was true, <1% was needed. Additionally, when talking about small probabilties, the difference between 1% and 1.5% is significant. This should change in future versions. The probability does not include the "%" symbol. 

The result can be either "T", for true, "F", for false, and "U", for undecided. Personally, I keep my undecided statements in a different file, and might add some way of bringing them up when it's time to resolve them.

The date includes as few 0s as posible, i.e., 1/1/2018 is fine, but 01/01/2018 breaks the program.

You can write a comment by starting with //

>// This is a comment

Blank lines are ignored.

### Using the program.
In Linux, you open your terminal, go to the folder in which the program is stored, write ./calibration and press enter.  
In Windows, you click the program. 

The file with your data should be stored in the same folder as your program. When the program is opened, you get greeted with some flavor text asking you for the name of your data file. Because mine is "data.txt", if you just press enter, it will assume your is as well. 

If your data file is in a subfolder, you'd write "subfolder/name.txt" (without apostrophes).

It then asks you whether you want to aggregate your data, that is, whether you want to interpret '60% to X' as '40% to not X' . Afterwards, it provides you with your Brier score and with a custom logarithmic score particularly meaningful for me because of it's relation to prediction markets.

## Functionalities I want to add in the future and breaks in compatibilty:

Because the program is in its early stages, I will not hesitate to break compatibility. If you want to request something, shoot me an email at name of this webpage + LH at gmail.com.

- Update Undecideds when the time comes.
- Give more granularity.
- Allow editing the database from the program, and then save it.
- Make the date optional / see evolution with time.
