/*
 * Menu.c
 *
 *  Created on: Sep 23, 2019
 *      Author: chorm
 */

#include <ConInteract.h>
#include <stdio.h>

int32_t menu(const char* title,const char* const itemv[]){
	int32_t selection = 0;
	clearScreen();
	int itemc;
	for(itemc=0;itemv[itemc]!=0;itemc++);
	while(1){
		printf("%s\n\n",title);
		for(int i = 0;i<itemc;i++)
			printf("%s%d. %s\n",(selection==i)?"->":"  ",i+1,itemv[i]);
		switch(waitch()){
		case '\n':
		case '\r':
			return selection;
		case 'w':
		case 'W':
			selection--;
		break;
		case 's':
		case 'S':
			selection++;
		break;
		case '\033':
			return MENU_CLOSE;
		}
		if(selection>itemc)
			while(selection>itemc)
				selection-=itemc;
		else while(selection<0)
			selection +=itemc;
		clearScreen();
	}
}

