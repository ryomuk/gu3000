// Font bitmap data for FrameBuffer class
//

#include <stdio.h>  // for the NULL pointer
#include "font.h"

#include "fonts/16segments_font.h"
#include "fonts/hpdl1414_font.h"
#include "fonts/4x6_font.h"
#include "fonts/H68TR_font.h"
#include "fonts/MICRlike6x6_font.h"
#include "fonts/MICRlike7x8_font.h"
#include "fonts/Noritake6x8_font.h"
#include "fonts/TK80BS_font.h"
#include "fonts/TK80BS_JIS_font.h"
#include "fonts/TK80BS_ASCII_font.h"
#include "fonts/TK80BS_KANA_font.h"
#include "fonts/TK80BS_GREEK_font.h"

Font *g_FontList[] = {
		      &font_Noritake6x8,
		      &font_TK80BS_JIS,
		      &font_TK80BS_ASCII,
		      &font_4x6,
		      &font_H68TR,
		      &font_MICRlike7x8,
		      &font_MICRlike6x6,
		      &font_16segments,
		      &font_hpdl1414,
		      &font_TK80BS,
		      &font_TK80BS_KANA,
		      &font_TK80BS_GREEK,
		      NULL
};

