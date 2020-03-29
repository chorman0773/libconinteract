
add_library(libconinteract src/Menu.c src/ClearScreen.c src/WaitInput.c include/ConInteract.h)

set_property(TARGET libconinteract PROPERTY PREFIX "")