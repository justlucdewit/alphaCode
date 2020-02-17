# alphaCode

#### a simple interpreted language based on zetaCode and BASIC <br> made by luc de wit

alpha code is a project started by luc de wit in februari 2020, its based on the programming language "zetaCode" wich was made by joseph catanzarit.

zetaCode aimed to be a simple language, interpreted in python wich looked like BASIC<br>
alphaCode on the other hand aimes for the same but improved, its written in C to gain alot more performance, and it has more advanced features like variables and markers

## alpha CLI commands
run a script .ac script:
```
alpha run folder/example.ac
```
<br>
get current version:

```
alpha version
```

## commands
alpha code is based on simple comands, that are executed from top to bottom.<br>
however, alpha code is able to change the line it is reading, while executing using the goto command<br>
here is a list of the currently available commands

<br>
comments are defined using #'s, and are allowed to put inline after another command

```
#this is a comment
goto 1 #this is a inline comment
```

<br>
print statements are made using the print keyword, and then the string to print

```
print "hello world"
```

<br>
exit statements quits the program and mentions what the exit code is<br>the exit code is usually 0 if the program ran normally, it needs 1 int argument<br>representing the exit code

```
exit 0
```


<br>
goto statements change the line number, where the program is currently running<br>this way you can make loops, and functions<br>

```
#go to line 5
goto 5 
```

<br>
let statements let you create a variable with a name and a value wich can be<br>a number or a string

```
let name "your mom"
let age 82
```

<br>
get statements let you get information from the user via console input<br>and then store it in a variable

```
get name
#name is now a variable with a name
```

<br>
debug is a command that lets you print every single variable that are<br> currently available, it doesnt need any arguments

```
get name
let age 18
debug
```