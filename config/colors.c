void red () {
  printf("\033[0;31m");
}
void b_red (){
  printf("\033[1;33m");
}

void green (){
  printf("\033[0;32m");
}
void b_green (){
  printf("\033[1;32m");
}

void yellow (){
  printf("\033[0;33m");
}
void b_yellow (){
  printf("\033[1;33m");
}

void blue (){
  printf("\033[0;34m");
}
void b_blue (){
  printf("\033[1;34m");
}

void magenta (){
  printf("\033[0;35m");
}
void b_magenta (){
  printf("\033[1;35m");
}

void cyan (){
  printf("\033[0;36m");
}
void b_cyan (){
  printf("\033[1;36m");
}

void resetColor () {
  printf("\033[0m");
}