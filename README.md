# alphaCode

#### a simple interpreted language based on zetaCode and BASIC <br> made by luc de wit

alpha code is a project started by luc de wit in februari 2020, its based on the programming language "zetaCode" wich was made by joseph catanzarit.

zetaCode aimed to be a simple language, interpreted in python wich looked like BASIC<br>
alphaCode on the other hand aimes for the same but improved, its written in C to gain alot more performance, and it has more advanced features like variables and markers

### alpha CLI commands
run a script .ac script:
```
alpha run folder/example.ac
```
<br>
get current version:
```
alpha version
```

### commands
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
exit statements quit 
```
print "hello world"
```