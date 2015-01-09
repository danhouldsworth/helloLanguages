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

# Build & interactive environments
* Go : ```go run file.go```
* Javascript : ```node file.js```
* C : ```cc file.c && ./a.out```
* Haskell : ```ghc --make file.hs && ./file```

# Habbit forming and best practice
I will impose two more additional constraints in the spirit of learning good habbits :
* All code should adhere to accepted best standards for both structure and formating - it should pass a linter set to maximum strictness.
* Aim for (and justify why I believe that) the most elegant solution for the task in each language.

This way if I (or anyone else) reviews or adds to a code challenge at a later date, the solution can be modified or validated objectively.

# Wishlist of my typical challenge tasks
* String manipulation
* Iterative calculations
* Mandlebrot set (text output)
* Basic web (file) server
* Basic Telnet chat server
* Web server with API hooks for local executable actions
* SuDoCo solver (mainly for Prologue)
* Websocket server
* Database access
* Multi-core calculation (Mandlebrot again - yay!)
* Display - primative shapes on screen or png
* Display - high res complex images and manipulation (Buddabrot!)
* GPIO (ARM, Atmel)
* Scheduler (ARM, Atmel)
* GPU (Direct Shader coding in C, OpenCL, WebGL, GPU Accelerator Frameworks)

