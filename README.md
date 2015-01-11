# helloLanguages
A problem oriented approach as I explore and learn programming languages

# Background
I tend to have a set approach as I learn a new language that goes along the lines of 'Hello, world!' to get going, and then moving onto a factorial calculation for trying basic functions and recursion, and then finally tackling a mandlebrot set for a taster of architecting and displaying a reasonable size task.

I may then move onto a file/socket server, or even a particle simulator to encourage me to explore the nuances of the language more deeply.

# Problem
However, I frequently realise that I've forgotten much of what I had learned, and when I go back to my files for a refresher, each stage has morphed into the next more complex task, and the original 'Hello, World!' is now a fully feldged Telnet server in Go, or a particle simulator in Javascript, or a Mandlebrot set area calculator in ARM assembly...!
None of which are useful as quick reminders.

# Brief
This time, I plan to orient the learning by the task itself. Tackling each challenge with as many languages as I have an appetite for, and ideally exploiting the particular capabilities and paradigms of each language to find the most elegant solution.

# Aim
I'm hopeful of three things to come out of this:

1. A quick revision of all the languages I've previously dabbled with : javascript, Go, C, ARM assembly
2. Provide a convenient, resiliant and growing framework for me to engage with new languages I'm interested in : Haskell, Rust, Prologue...
3. Develope an appreciation for the contrasting paradigms of each language.

# Structure
* Files stored within challenge project folders.
* Filename suffix will make langauge clear, filename should be name of challenge.
* Folder names prefixed with numbers to enable easy view of increasing difficulty
* Notes defining the task to be kept in seperate TASK.md and not in each code file, however findings & pitfalls relevant to each language approach should be included appropriately
* Comment on anything not immediately clear, however never explain through comments that which can be made clear with better structure and variable names

# Build & interactive environments
* Go : ```go run file.go``` or ```go build file.go && ./file```
* Javascript : ```node file.js```
* C : ```cc file.c && ./a.out```
* Haskell : ```ghc --make file.hs && ./file```
* Ruby : ```ruby file.rb```
* Java : ```javac file.java && java file```
* Python: ```python file.py```
* Perl: ``` perl file.pl ```
* Lisp: ``` clisp file.lisp ```

# Habbit forming and best practice
I will impose three more additional constraints in the spirit of learning good habbits :
* All code should adhere to accepted best standards for both structure and formating - it should pass a linter set to maximum strictness.
* Aim for (and justify why I believe that) the most elegant solution for the task in each language. This way if I (or anyone else) reviews or adds to a code challenge at a later date, the solution can be modified or validated objectively.
* Always park downhill! The first line(s) of every file should always be a status of completion or the issue that currently incomplete / stuck on. This will enable me (or others) to quickly jump back in if its been long enough to forget.

As I get into the more complex algorithms, I should also consider and comment on the efficiency of the solution specific to that language. (Probably need to brush up on http://en.wikipedia.org/wiki/Big_O_notation !!)

# Wishlist of my typical challenge tasks
* String manipulation
* Iterative calculations
* External input (command line, config file or user)
* Mandlebrot set (text output)
* Basic web (file) server
* Basic Telnet chat server
* Closures (while I use this in JS I could do with a more intuitive understanding)
* Modular architecture (eg. external libraries)
* Web server with API hooks for local executable actions
* SuDoCo solver (mainly for Prologue)
* Websocket server
* Database access
* Multi-core calculation (Mandlebrot again - yay!)
* Display - primative shapes on screen or png
* Display - high res complex images and manipulation (Buddabrot!)
* GPIO (ARM, Atmel)
* Scheduler - non blocking sub tasks in a single thread
* GPU (Direct Shader coding in C, OpenCL, WebGL, GPU Accelerator Frameworks)

