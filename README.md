# 42Minishell
### As beautiful as a shell

The existence of shells is linked to the very existence of IT.
At the time, all developers agreed that communicating with a computer using aligned
1/0 switches was seriously irritating.

It was only logical that they came up with the idea of creating a software to com-
municate with a computer using interactive lines of commands in a language somewhat
close to the human language.

Thanks to Minishell, you’ll be able to travel through time and come back to problems
people faced when Windows didn’t exist.


![Minishell](https://user-images.githubusercontent.com/107865727/225025081-358e9c7b-a98b-43be-bd45-0282f3ecc624.png)

# Readline Leak Suppression

The readline() function can cause memory leaks. You don’t have to fix them. But
that doesn’t mean your own code, yes the code you wrote, can have memory
leaks.

Valgrind detects numerous problems in the base libraries, such as the GNU C library, and the XFree86 client libraries, which come pre-installed on your GNU/Linux system. You can't easily fix these, but you don't want to see these errors (and yes, there are many!) So Valgrind reads a list of errors to suppress at startup. A default suppression file is cooked up by the ./configure script.
You can modify and add to the suppressions file at your leisure, or, better, write your own. Multiple suppression files are allowed. This is useful if part of your project contains errors you can't or don't want to fix, yet you don't want to continuously be reminded of them.

Valgrind Suppression File [Howto](https://wiki.wxwidgets.org/Valgrind_Suppression_File_Howto)

**Creates a .supp file set up like the one in this repository in the minishell folder and launch:**
>valgrind --leak-check=full --show-leak-kinds=all --suppressions=./readline.supp ./minishell


![Screenshot from 2023-03-14 15-20-23](https://user-images.githubusercontent.com/107865727/225031679-786f8731-ff70-4143-8abf-1c28bbabbb71.png)

Only leaks caused by the code will be displayed, ignoring those of the readline function
