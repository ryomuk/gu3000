#ifndef _LIFEGAME_H_
#define _LIFEGAME_H_

#define X_WORLD (VFD_Xdots * 1)
#define Y_WORLD (VFD_Ydots * 1)
#define CELLS (X_WORLD * Y_WORLD)

int pattern_r_pentomino[] = {3, 3,
			     0, 1, 1,
			     1, 1, 0,
			     0, 1, 0};
int pattern_glider[] = {3, 3,
			0, 0, 1,
			1, 0, 1,
			0, 1, 1};

int pattern_acorn[] = {7, 3,
		       0,1,0,0,0,0,0,
		       0,0,0,1,0,0,0,
		       1,1,0,0,1,1,1};

int pattern_random[] = {-1};

#define UL(i) ((i - 1 - Y_WORLD + CELLS) % CELLS)
#define UP(i) ((i - 1           + CELLS) % CELLS)
#define UR(i) ((i - 1 + Y_WORLD + CELLS) % CELLS)
#define LT(i) ((i     - Y_WORLD + CELLS) % CELLS)
#define RT(i) ((i     + Y_WORLD + CELLS) % CELLS)
#define DL(i) ((i + 1 - Y_WORLD + CELLS) % CELLS)
#define DN(i) ((i + 1           + CELLS) % CELLS)
#define DR(i) ((i + 1 + Y_WORLD + CELLS) % CELLS)
#define LOC(x, y) ((x) * Y_WORLD + (y))

class Lifegame{
public:
  void clear();
  void update();
  void draw(int x, int y, VFD *vfd);
  void draw(VFD *vfd);
  void drawWholeWorld(VFD *vfd);
  void putPattern(int *pattern, int x, int y);
  void fillRandom(double density);
  int population;
  int generation;
private:
  void updatePopulation();
  byte m_cell[CELLS];
  byte m_cnt[CELLS];
};


#endif
