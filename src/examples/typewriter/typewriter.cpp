#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <gu3000graphic.h>

#define DEFAULT_FONTNAME "Noritake6x8"

void usage(){
  fprintf(stderr, "Usage: typewriter [OPTION]... [FILE]\n");
  fprintf(stderr, "  -f fontname : select font\n");
  fprintf(stderr, "  -h : show usage\n");
  fprintf(stderr, "  -l : show fontname list\n");
  fprintf(stderr, "  -p : proportional font\n");
  fprintf(stderr, "EXAMPLES\n");
  fprintf(stderr, "  typewriter -f 4x6\n");
  exit(1);
}

void showfontlist(VFD *vfd){
  for(int i = 0; vfd->fontList[i] != NULL; i++){
    printf("%s\n", vfd->fontList[i]->name);
  }
}

int main(int argc, char *argv[]){
  VFD vfd;
  const char *fontname = NULL;
  bool proportional = false;
  int key;
  
  for(int i = 1; i < argc; i++){
    if(argv[i][0] == '-'){
      switch(argv[i][1]){
      case 'f':
	i++;
	if(i >= argc) usage();
	fontname = argv[i];
	break;
      case 'h':
	usage();
      case 'p':
	proportional = true;
	break;
      case 'l':
	showfontlist(&vfd);
	exit(0);
      default:
	usage();
      }
    } else {
      usage();
    }
  }

  // Fixed width
  if(fontname == NULL){
    fontname = DEFAULT_FONTNAME;
  }

  vfd.setFontByName(fontname);
  if(proportional){
    vfd.setFontProportional();
  }
 
  initscr();
  noecho();
  cbreak();
  while(1){
    key = getch();
    vfd.putchar(key);
    vfd.show();
    //vfd.showAllArea();
  }
  exit(EXIT_SUCCESS);
}
