#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <gu3000graphic.h>

// Wire frame models are available
// from https://people.sc.fsu.edu/~jburkardt/data/obj/obj.html

#define MAX_NUM_VERTEX 65536*2
#define PI 3.14159265358979323846

typedef struct {
  double x;
  double y;
  double z;
} Vertex;


double scale = 1.0;
double scale_time;

double scaling(double t){
  //  return(3.0*abs(fmod(t, 2.0)-1.0) + 0.0*(1-abs(fmod(t, 2.0)-1.0)));
  return(1.2*(cos(PI*scale_time)-1.0));
}

double theta = 0.0;
Vertex projected(Vertex *v){
  Vertex p;
  double a, b, c, d;
  a = sin(theta);
  b = cos(theta);
  c = cos(theta);
  d = -sin(theta);
  p.x = (a*v->x + b*v->z)*scale*scaling(scale_time)+ 128;
  p.y = (c*v->y + d*v->z)*scale*scaling(scale_time)+  64;
  p.z = 0.0;
  return(p);
}

int num_lines = 0;
void drawLine(VFD *vfd, Vertex *v1, Vertex *v2){
  Vertex p1, p2;

  p1 = projected(v1);
  p2 = projected(v2);
  
  //printf("p(%d, %d, %d, %d, 1)\n", (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
  if(p1.x < 0 && p2.x < 0) return;
  if(p1.x > vfd->WIDTH && p2.x > vfd->WIDTH) return;
  if(p1.y < 0 && p2.y < 0) return;
  if(p1.y > vfd->HEIGHT && p2.x > vfd->HEIGHT) return;
  num_lines ++;
  vfd->drawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, 1);

}

char *getanumber(char *buf, int *i){
  int n;
  unsigned char c;

  n = -1;
  while((c = *buf++) != '\0'){
    if(n < 0){
      if(c < '0' || c > '9'){
	continue;
      } else {
	n = (int)(c - '0');
      }
    } else {
      if(c < '0' || c > '9'){
	if(c == '/'){
	  while(!isspace(*buf)){
	    buf++;
	  }
	}
	break;
      } else {
	n = n * 10 + (int)(c - '0');
      }
    }
  }
  *i = n;
  if(n < 0){
    return(NULL);
  } else {
    return(buf);
  }
}

#define drawLines(vfd, v, list)   drawLinesPolygon(vfd, v, list, 0)
#define drawPolygon(vfd, v, list) drawLinesPolygon(vfd, v, list, 1)

void drawLinesPolygon(VFD *vfd, Vertex v[], char *list, int mode){
  int s;
  int i, j;

  if((list = getanumber(list, &(s))) == NULL){
    return;
  }
  i = s;
  while((list = getanumber(list, &(j))) != NULL){
    drawLine(vfd, &v[i], &v[j]);
    //printf("v[%d]-v[%d],", i, j);
    i = j;
  }
  if(mode == 1){ // connect last to start
    drawLine(vfd, &v[i], &v[s]);
    //printf("v[%d]-v[%d]\n", i, s);
  }
}


int main(int argc, char *argv[]){
  VFD vfd;
  FILE *fp;
  char *line = NULL;
  size_t len;
  ssize_t n_read;
  long seekpoint = 0;
  
  Vertex v[MAX_NUM_VERTEX];
  double x, y, z;
  int i;
  
  if(argc <= 1){
    fp = stdin;
  } else {
    char *infile = argv[1];
    if((fp = fopen(infile, "r")) == NULL){
      fprintf(stderr, "%s: Cannot open file '%s'\n", argv[0], infile);
      exit(1);
    }
  }

  vfd.clear();
  
  double max_position = 0.0;
  unsigned long time_s, time_last;
  time_last = 0;
  while(1){
    time_s = micros();
    num_lines = 0;
    i = 1;
    if(seekpoint > 0){
      fseek(fp, seekpoint, SEEK_SET);
    }
    while((n_read = getline(&line, &len, fp)) != -1){
      if(line[0] == '#') continue;
      if(sscanf(line, "v %lf %lf %lf", &x, &y, &z) == 3){
	v[i].x = x;
	v[i].y = y;
	v[i].z = z;
	i++;
	max_position=max(max_position, max(max(abs(x), abs(y)), abs(z)));
      }
      if(*line == 'f' || *line =='l'){
	if(seekpoint == 0){
	  seekpoint = ftell(fp) - n_read;
	  scale = 128.0 / max_position;
	}
      }
      
      if(*line == 'f'){
	drawPolygon(&vfd, v, &(line[1]));
      }
      if(*line == 'l'){
	drawLines(&vfd, v, &(line[1]));
      }
    }
    if(time_last > 0){
      char linebuf[128];
      sprintf(linebuf, "%dusec(%dFPS)\n%d Lines",
	      (int)(time_last),
	      (int)(1000000.0/time_last),
	      num_lines
	      );
      vfd.puts(linebuf);
    }
    vfd.show();
    rewind(fp);
    vfd.clearFrameBuffer();
    theta += PI/100.0;
    scale_time += 1.0/240.0;
    time_last = micros() - time_s;
  }

  free(line);
  fclose(fp);
  exit(EXIT_SUCCESS);
}
