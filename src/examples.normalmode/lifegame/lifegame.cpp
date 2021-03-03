#include <stdio.h>
#include <stdlib.h>
//#include <gu3000graphic.h>
#include <gu3000normal.h>

#include "lifegame.h"

int main(void){
  VFD vfd;
  Lifegame world;
  char linebuf[1024];
  
  unsigned long time_0, time_1, time_2, time_3, time_4;
  unsigned long time_lastloop = 0;
  
  //  frameBuffer.setFontByName("14segments");
  world.clear();
  //world.fillRandom(0.5);
  //world.putPattern(pattern_r_pentomino, X_WORLD/2, Y_WORLD/2);
  //world.putPattern(pattern_glider, X_WORLD/2, Y_WORLD/2);
  world.putPattern(pattern_acorn, X_WORLD/2, Y_WORLD/2);
  
  while(1){
    time_0 = micros();
    //    world.draw(X_WORLD/4, Y_WORLD/4, &vfd);
    // world.draw(&vfd);
    world.drawWholeWorld(&vfd);

    time_1 = micros();
#ifdef GU3000_NORMALMODE
    vfd.clearDisplay();
#endif
    sprintf(linebuf, "Generation=%d\nPopulation=%d\n%dusec(%dFPS)\n",
	    world.generation,
	    world.population,
	    (int)(time_lastloop),
	    time_lastloop ? (int)(1000000.0/time_lastloop): 0
	    );
    vfd.setCursor(0, 0);
    vfd.puts(linebuf);

    time_2 = micros();

    vfd.show();
    //vfd.rotateAndShow();
    //vfd.syncAndShow();
    //vfd.syncRotateAndShow();

    time_3 = micros();

    if(world.generation == 0){
      delay(2000);
    }

    world.update();
    time_4 = micros();
    time_lastloop = time_4 - time_0;
    if(world.generation % 100 == 0){
      printf("%d usec(%dFPS)\n" ,
	     (int)time_lastloop,
	     (int)(1000000.0/time_lastloop)
	     );
      printf("cell->fb(%dus), info(%dus), fb->vfd(%dus), update(%dus)\n",
	     (int)(time_1 - time_0),
	     (int)(time_2 - time_1),
	     (int)(time_3 - time_2),
	     (int)(time_4 - time_3)
	     );
      printf("Generation = %d, Population = %d\n",
	     world.generation, world.population);
      //      printf("dbg_a, b= %d,%d\n", vfd.dbg_cnta, vfd.dbg_cntb);
    }
  }
}


void Lifegame::clear(){
  for(int i = 0; i < CELLS; i++){
    m_cell[i] = 0;
  }
  generation = 0;
}

void Lifegame::updatePopulation(){
  population = 0;
  for(int i = 0; i < CELLS; i++){
    if(m_cell[i]){
      population++;
    }
  }
}

void Lifegame::fillRandom(double d){
  for(int i = 0; i < CELLS; i++){
    if(random() < RAND_MAX * d){
      m_cell[i] = 1;
    } else {
      m_cell[i] = 0;
    }
  }
  updatePopulation();
}

void Lifegame::putPattern(int *pattern, int x, int y){
  int i, j;
  int size_x, size_y;
  
  size_x = *pattern++;
  size_y = *pattern++;
  
  for(j = 0; j < size_y; j++){
    for(i = 0; i < size_x; i++){
      m_cell[LOC(x + i, y + j) % CELLS] = *pattern++;
    }
  }
  updatePopulation();
}

void Lifegame::update(){
  int i;

  generation++;

  for(i = 0; i < CELLS; i++){
    m_cnt[i] = 0;
  }
  for(i = 0; i < CELLS; i++){
    if(m_cell[i]){
      m_cnt[UL(i)]++;
      m_cnt[UP(i)]++;
      m_cnt[UR(i)]++;
      m_cnt[LT(i)]++;
      m_cnt[RT(i)]++;
      m_cnt[DL(i)]++;
      m_cnt[DN(i)]++;
      m_cnt[DR(i)]++;
    }
  }

  population = 0;
  for(i = 0; i < CELLS; i++){
    switch(m_cnt[i]){
    case 2:
      break;
    case 3:
      m_cell[i] = 1;
      break;
    default:
      m_cell[i] = 0;
      break;
    }
    if(m_cell[i]){
      population++;
    }
  }
}

void Lifegame::draw(VFD *vfd){
  int i, j;
  vfd->clearFrameBuffer();
  for(i = 0; i < vfd->WIDTH; i++){
    for(j = 0; j < vfd->HEIGHT; j++){
      if(m_cell[LOC(i, j)]){
	vfd->pset(i, j);
      }
    }
  }
}

void Lifegame::draw(int x, int y, VFD *vfd){
  int i, j;
  vfd->clearFrameBuffer();
  for(i = 0; i < vfd->WIDTH; i++){
    for(j = 0; j < vfd->HEIGHT; j++){
      if(m_cell[LOC(x + i, y + j)]){
	vfd->pset(i, j);
      }
    }
  }
}

void Lifegame::drawWholeWorld(VFD *vfd){
  int i, j;
  double xscale, yscale;

  xscale = (double)(vfd->WIDTH) / X_WORLD;
  yscale = (double)(vfd->HEIGHT) / Y_WORLD;

  vfd->clearFrameBuffer();
  for(i = 0; i < X_WORLD; i++){
    for(j = 0; j < Y_WORLD; j++){
      if(m_cell[LOC(i, j)]){
	vfd->pset((int)(i*xscale), (int)(j*yscale));
      }
    }
  }
}
