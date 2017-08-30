WordV
======

WordV is a program that is meant to work in combination with password
auditing programs like hashcat and aircrack, which take as their input a
dictionary list of potential passwords in an attempt to crack a hashed
password. The intent of wordv is to provide a comprehensive and intelligent
list as input for these programs.

The variations that wordv produces are considered common modifications to
everyday words when used as passwords. Some examples are:

1. Uppercase the first letter of the word
2. Add a single digit to the end of the word.
3. Add a special character to the end of the word.
4. Add a birthdate to the end of a word.
5. Change certain letters to numbers in the word. (known as "leet speak")
6. Combine two words together.
7. Any combination of 2 or more of the above variations.

WordV can produce over 100 million variations from a single list of
1000 commonly used words.

Table of Contents
-----------------

1. [Download and Install](#download-and-install)
3. [Usage](#usage)
5. [License](#license)
6. [Tips](#tips)

Download and Install
--------------------

To install this project from source, you will need to have the tools `git`,
`gcc`, and `make` to download and build it. Install them from your package
manager if they are not already installed.

Once you have the necessary tools installed, follow these instructions:

```
https://github.com/bartobri/wordv.git
cd ./wordv
make
sudo make install
```

This will build and install `wordv` in to the /usr/local/bin directory.

Uninstall:

```
sudo make uninstall
```

Usage
-----

Run wordv and pipe its output to a password auditing program. Here is an
example with aircrack:

```
wordv | sudo aircrack-ng -w - -b 08:62:66:94:48:40 psk*.cap
```

By default, wordv uses a list of 1000 commonly used words. To see what
other lists are available, use the `-s` command line option:

```
wordv -s
```

To override the default word list, use the -l option and provide the list
name as an argument:

```
wordv -l password
```

License
-------

This program is free software; you can redistribute it and/or modify it under the terms of the GNU 
General Public License as published by the Free Software Foundation; either version 3 of the License,
or (at your option) any later version.  See [LICENSE](LICENSE) for more details.

Tips
----

[Tips are always appreciated!](https://github.com/bartobri/tips)
