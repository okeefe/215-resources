# Resources

Various useful resources I've found around the web.

## General documentation

- [Wikipedia](https://en.wikipedia.or)
- [IRC](https://webchat.freenode.net)
<sup>[What is IRC?](https://en.wikipedia.org/wiki/Internet_Relay_Chat)</sup>
- [Open-source docs](https://readthedocs.io)
- [Linux](http://tldp.org/)
- [Reddit](https:// praw.readthedocs.io)
- [Python](https://python.readthedocs.io)
- [Python (stable)](https://docs.python.org/3/)
- [Java](https://docs.oracle.com/javase/8/docs/api/)

## Manual pages

- [Intro](https://ryanstutorials.net/linuxtutorial/manual.php)
- [Format](https://liw.fi/manpages/)
- [Online mirror](https://linux.die.net/man/)

## [Unix][unix]

### Tools

- [bash][bash man page]:
A 'shell'; takes input and executes programs. Has its own syntax.
I've made a very [simple shell](https://keybase.pub/jyn514/Programming/C-plus-plus/interpreter/)
in C++ if you'd like to see an example.

- [ssh](https://www.openssh.com/):
'Secure shell'; connects to a remote computer and executes programs

- [make](https://www.gnu.org/software/make/manual/html_node/index.html#Top):
Automated build tool (so you don't have to type as much)
See my [template](https://github.com/okeefe/215-resources/blob/master/template.makefile)
for a (fairly complicated) example.

- [apt](https://wiki.debian.org/Apt):
[package manager](https://en.wikipedia.org/wiki/Package_manager),
in some ways similar to an app store

- [coreutils](https://www.gnu.org/software/coreutils/manual/html_node/index.html):
The basic tools of the [GNU project](https://www.gnu.org/software/software.html)
and most of the tools we will use in this course

- [gcc](gcc.gnu.org/onlinedocs/gcc-7.2.0/gcc/):
multi-language compiler. In this course we will be using g++,
but all of the gnu compilers are often used.

- [binutils](https://www.gnu.org/software/binutils/):
tools necessary for compiling programs (assemblers, hexdumps, etc).

- [git](https://git-scm.com/book/en/v2):
[version control](https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control)
so you can keep track of the changes you've made.
See also the [subreddit](https://reddit.com/r/git) for more help.

- [GitHub][github]:
free online hosting for your git repos.
[This page](https://github.com/okeefe/215-resources/blob/master/resources.md)
is hosted there, as are various other resources.

#### Misc commands
- which
- type
- help
- umask
- zip
- tar
- gzip/bzip2
- wget/curl/telnet
- less/more/pg
- screen
- cron/crond/crontab/anacron
- gnupg
- ip/ipconfig/dhclient
- links/lynx/elinks

### History
- [What is Unix?][unix]
- [Linux](https://en.wikipedia.org/wiki/History_of_Linux)
- [First mailing lists](https://groups.google.com/forum/#!msg/comp.os.minix/dlNtH7RRrGA/SwRavCzVE7gJ)
(not original site)
- [Kernel wars](web.archive.org/web/20121003060514/http://www.dina.dk/~abraham/Linus_vs_Tanenbaum.html)
- [Free software](https://en.wikipedia.org/wiki/History_of_free_and_open-source_software)
- [Linus Torvalds](https://en.wikipedia.org/wiki/Linus_Torvalds),
creater of the Linux kernel
- [Stallman](https://en.wikipedia.org/wiki/Richard_Stallman);
see also https://stallman.org
- [GNU Project](https://en.wikipedia.org/wiki/GNU_Project)

### Installing Linux
- [Windows subsytem for Linux](https://msdn.microsoft.com/en-us/commandline/wsl/install-win10)
- [Dual-booting](https://www.howtogeek.com/187789/dual-booting-explained-how-you-can-have-multiple-operating-systems-on-your-computer/)

#### Distros
[What's a distro?](https://en.wikipedia.org/wiki/Linux_distribution)

- [Debian](https://www.debian.org/intro/about)
- [Ubuntu](https://www.ubuntu.com/) is used in the Linux labs, based on debian
- [Fedora](https://getfedora.org/en/)
- [More info than you want](https://en.wikipedia.org/wiki/Comparison_of_Linux_distributions)

### [Lots more about UNIX](http://www.catb.org/~esr/faqs/)

## Editors
I refuse to start an editor war. Find the editor wars on your own.

### For terminals

- [vim](https://vim.sourceforge.io/)
- [emacs](https://www.gnu.org/software/emacs/), which is graphical as well
- [nano](https://www.nano-editor.org/)
- [ed](https://www.gnu.org/fun/jokes/ed-msg.html)

### For Linux
- [kate](http://kate-editor.org/)
- [gedit](https://wiki.gnome.org/Apps/Gedit)

### For Windows
- [Notepad](https://en.wikipedia.org/wiki/Microsoft_Notepad)
- [Notepad++](https://notepad-plus-plus.org/)

### General purpose [IDE](https://en.wikipedia.org/wiki/Integrated_development_environments)s
- [Atom](https://atom.io/)
- [Brackets](http://brackets.io/)
- [Sublime text](https://www.sublimetext.com/)
- [Visual Studio Code](https://code.visualstudio.com/)


## [Languages](https://en.wikipedia.org/wiki/Programming_language)

### [Bash][bash man page]:

#### Basic commands
- cd, pwd
- ls
- rm, rmdir
- cat
- echo or printf
- rmdir
- history
- touch
- ln
- date, cal, calendar
- ps, kill, quit
    
#### [Guide](http://tldp.org/LDP/abs/html/)

#### [Configuration files](http://wiki.bash-hackers.org/howto/conffile)
See .bashrc/.profile in your home directory

#### [Bash vs sh](https://stackoverflow.com/questions/5725296/difference-between-sh-and-bash#5725402)

#### [Scripting](https://en.wikibooks.org/wiki/Bash_Shell_Scripting)


### C++
- [Guides](https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list)
- [Ebook](https://en.wikibooks.org/wiki/C%2B%2B_Programming)
- [Reference](http://en.cppreference.com/wv/cpp)
- [Reference (2)](http://www.cplusplus.com/doc/)

### Web
- [Handy infographic](https://i.redd.it/0nodknkfbxcz.jpg)
- [HTML reference](www.w3schools.com/html/default.asp )
- [Mozilla intro](developer.mozilla.org/en-US/docs/Learn)
- [XSS](www.google.com/about/appsecurity/learning/xss/)

### Misc
- [Google guide](https://techdevguide.withgoogle.com), very career oriented
- [Course](http://mooc.fi/english.html) by U of Helsinki
- [Intro to Programming](http://pine.fm/LearnToProgram/) with Ruby
- LOTS of [links](http://freeprogrammingresources.com/)
- [Online compiler](https://repl.it/)

## Neural Networks:
- [Courses by MIT](courses.csail.mit.edu/)
- [Tensorflow](www.tensorflow.org/get_started/), a Python framework for machine learning
- [Deep intro to core concepts](http://neuralnetworksanddeeplearning.com/)

## Challenge sites
- [Simple intro to challenge sites](http://codingbat.com)
- [Exercism](https://exercism.io): challenges of every level in every language
- [Project Euler](https://projecteuler.net), heavily math-based
- [Over the Wire](https://overthewire.org)
- [CodeWars](https://codewars.com)
- [Community pentests](https://vulnhub.com)
- [Python interactive challenges](github.com/donnemartin/interactive-coding-challenges/), heavy download
- [More links](softwareengineering.stackexchange.com/questions/756)

## Hosting
- [GitHub][github]
- [GitHub Pages](https://pages.github.com/)
- https://bitbucket.org/
- https://wordpress.com
- https://sourceforge.net

[bash man page]: https://www.gnu.org/software/bash/
[github]: https://github.com
[unix]: https://en.wikipedia.org/wiki/Unix
