/*
 * WaitInput.c
 *
 *  Created on: Sep 23, 2019
 *      Author: chorm
 */

#include <ConInteract.h>

#include <stdio.h>

#if defined(__GNUC__)
#define unreachable() __builtin_unreachable()
#else
#if !defined(__has_builtin)
#define __has_builtin(n) 0
#endif
#if __has_builtin(__builtin_unreachable)
#define unreachable() __builtin_unreachable()
#else
#include <stdlib.h>
#define unreachable() (void)*((int *)0);
#endif

#endif

#ifndef WIN32
#include <termios.h>
#include <unistd.h>
#include <errno.h>
int waitch()
{
	fsync(STDOUT_FILENO);
	struct termios oldattr, newattr;
	unsigned char ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	if (read(STDIN_FILENO, &ch, 1) <= 0)
	{
		int errn = errno; // Preserve errno
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
		errno = errn;
		return -1;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}
#else
#include <conio.h>
int waitch()
{
	return _getch();
}
#endif

void waitInput()
{
	waitch();
}

KeyDirection waitDirection()
{
	for (;;)
	{
		int ch = waitch();
		//Has Observable-behavior
		//so this loop isn't UB.
		switch (ch)
		{
		case 'w':
		case 'W':
			return KEY_UP;
		case 'a':
		case 'A':
			return KEY_LEFT;
		case 's':
		case 'S':
			return KEY_DOWN;
		case 'd':
		case 'D':
			return KEY_RIGHT;
		case '\033':
			return KEY_ESC;
		case -1:
			return KEY_EOF;
		}
	}
	unreachable();
}
