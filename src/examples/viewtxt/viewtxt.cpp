#include <stdio.h>
#include <stdlib.h>
#include <gu3000graphic.h>

#define DEFAULT_FONTNAME "Noritake6x8"

void usage(){
  fprintf(stderr, "Usage: viewtxt [OPTION]... [FILE]\n");
  fprintf(stderr, "  -f fontname : select font\n");
  fprintf(stderr, "  -h : show usage\n");
  fprintf(stderr, "  -l : show fontname list\n");
  fprintf(stderr, "  -p : proportional font\n");
  fprintf(stderr, "EXAMPLES\n");
  fprintf(stderr, "  viewtxt -f 4x6 file.txt\n");
  fprintf(stderr, "  viewtxt -p file.txt\n");
  fprintf(stderr, "  viewtxt -l\n");
  exit(1);
}

void showfontlist(VFD *vfd){
  for(int i = 0; vfd->fontList[i] != NULL; i++){
    printf("%s\n", vfd->fontList[i]->name);
  }
}

int main(int argc, char *argv[]){
  VFD vfd;
  FILE *fp;
  const char *filename = NULL;
  const char *fontname = NULL;
  char *line = NULL;
  size_t len;
  ssize_t n_read;
  bool proportional = false;
  
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
      if(filename == NULL){
	filename = argv[i];
      } else {
	usage();
      }
    }
  }
  if( filename == NULL){
    fp = stdin;
  } else {
    if((fp = fopen(filename, "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], filename);
      exit(1);
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
 
  while((n_read = getline(&line, &len, fp)) != -1){
#if 0
    for(int i = 0; i < n_read; i++){
      vfd.putchar(line[i]);
      vfd.show();
    }
#else
    vfd.puts(line);
    //vfd.showAllArea();
    vfd.show();
#endif
  }
  free(line);
  fclose(fp);
  exit(EXIT_SUCCESS);
}
