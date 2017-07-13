WordV
======

WordV is a program that is meant to work in combination with security
auditing programs like hashcat and aircrack. WordV loops over a provided
list of common words or passwords and it outputs variations of those words
in an attempt to help security auditing programs find weak passwords

Table of Contents
-----------------

1. [Download and Install](#download-and-install)
3. [Usage](#usage)r)
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
wordv -l password
```

License
-------

This program is free software; you can redistribute it and/or modify it under the terms of the GNU 
General Public License as published by the Free Software Foundation; either version 3 of the License,
or (at your option) any later version.  See [LICENSE](LICENSE) for more details.

Tips
----

If you've found any of my open source projects helpful to the extent that
you'd like to repay me in some way, below are a few methods you can use to
tip me for my work. I work on open source software full time, and I do not
get paid for it. Any tips are greatly appreciated.

#### PayPal
Send tips to bartobrian@gmail.com or [follow this link](https://www.paypal.me/BrianBarto).

#### Bitcoin
Tip address: 19fy9CsJvN39f3dV6MJy6FfvggP5zunh5j

#### Ethereum                                                                                                 
Tip Address: dc711e5e4cad4912cbd06f1f136bef05643ce3f0

#### Litecoin
Tip Address: LQSWiz3cKGDMLuFZqF7osUaxhSNJXxBtkD
