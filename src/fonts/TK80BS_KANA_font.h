// Font of NEC TK-80BS katakana mix
// 0x20-0x3F: symbols and numbers (origilal mode,       0x20-0x3F)
// 0x40-0x5F: uppercase alphabet  (original JIS mode,   0x00-0x1F)
// 0x60-0x7F: lowercase alphabet  (original ASCII mode, 0x00-0x1F)
//
// 0x80-0xBF: katakana            (original JIS mode,   0x40-0x7F)
// 0xC0-0xFF: picture symbols     (origilal JIS mode,   0xC0-0xFF)

const unsigned char bmp_TK80BS_KANA[] =
  {
   //
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   // !
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00101111,
   0b00000000,
   0b00000000,
   0b00000000,
   // "
   0b00000000,
   0b00000000,
   0b00000111,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000111,
   0b00000000,
   // #
   0b00000000,
   0b00010100,
   0b01111111,
   0b00010100,
   0b00010100,
   0b00010100,
   0b01111111,
   0b00010100,
   // $
   0b00000000,
   0b00100100,
   0b00101010,
   0b00101010,
   0b01111111,
   0b00101010,
   0b00101010,
   0b00010010,
   // %
   0b00000000,
   0b01000011,
   0b00100011,
   0b00010000,
   0b00001000,
   0b00000100,
   0b01100010,
   0b01100001,
   // &
   0b00000000,
   0b01100110,
   0b01010101,
   0b01011001,
   0b01010101,
   0b00100101,
   0b01100010,
   0b01010000,
   // '
   0b00000000,
   0b00000000,
   0b00000101,
   0b00000011,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   // (
   0b00000000,
   0b00000000,
   0b00011100,
   0b00100010,
   0b01000001,
   0b00000000,
   0b00000000,
   0b00000000,
   // )
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b01000001,
   0b00100010,
   0b00011100,
   0b00000000,
   // *
   0b00000000,
   0b00000000,
   0b00010100,
   0b00001000,
   0b00111110,
   0b00001000,
   0b00010100,
   0b00000000,
   // +
   0b00000000,
   0b00000000,
   0b00001000,
   0b00001000,
   0b00111110,
   0b00001000,
   0b00001000,
   0b00000000,
   // ,
   0b00000000,
   0b00000000,
   0b01010000,
   0b00110000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   // -
   0b00000000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   // .
   0b00000000,
   0b01100000,
   0b01100000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   // /
   0b00000000,
   0b01000000,
   0b00100000,
   0b00010000,
   0b00001000,
   0b00000100,
   0b00000010,
   0b00000001,
   // 0
   0b00000000,
   0b00111110,
   0b01100001,
   0b01010001,
   0b01001001,
   0b01000101,
   0b01000011,
   0b00111110,
   // 1
   0b00000000,
   0b00000000,
   0b00000000,
   0b01000010,
   0b01111111,
   0b01000000,
   0b00000000,
   0b00000000,
   // 2
   0b00000000,
   0b01000010,
   0b01100001,
   0b01010001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01000110,
   // 3
   0b00000000,
   0b00100001,
   0b01000001,
   0b01000001,
   0b01000101,
   0b01000101,
   0b01001011,
   0b00110001,
   // 4
   0b00000000,
   0b00011000,
   0b00010100,
   0b00010010,
   0b00010001,
   0b01111111,
   0b00010000,
   0b00010000,
   // 5
   0b00000000,
   0b00100111,
   0b01000101,
   0b01000101,
   0b01000101,
   0b01000101,
   0b01000101,
   0b00111001,
   // 6
   0b00000000,
   0b00111100,
   0b01001010,
   0b01001001,
   0b01001001,
   0b01001001,
   0b00110001,
   0b00000000,
   // 7
   0b00000000,
   0b00000001,
   0b00000001,
   0b01110001,
   0b00001001,
   0b00000101,
   0b00000011,
   0b00000001,
   // 8
   0b00000000,
   0b00110000,
   0b01001110,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001110,
   0b00110000,
   // 9
   0b00000000,
   0b00000110,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b00101001,
   0b00011110,
   // :
   0b00000000,
   0b00000000,
   0b00000000,
   0b00110110,
   0b00110110,
   0b00000000,
   0b00000000,
   0b00000000,
   // ;
   0b00000000,
   0b00000000,
   0b00000000,
   0b01010110,
   0b00110110,
   0b00000000,
   0b00000000,
   0b00000000,
   // <
   0b00000000,
   0b00001000,
   0b00010100,
   0b00100010,
   0b01000001,
   0b00000000,
   0b00000000,
   0b00000000,
   // =
   0b00000000,
   0b00010100,
   0b00010100,
   0b00010100,
   0b00010100,
   0b00010100,
   0b00010100,
   0b00010100,
   // >
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b01000001,
   0b00100010,
   0b00010100,
   0b00001000,
   // ?
   0b00000000,
   0b00000010,
   0b00000001,
   0b00000001,
   0b01010001,
   0b00010001,
   0b00001001,
   0b00000110,
   // @
   0b00000000,
   0b00110010,
   0b01001001,
   0b01001001,
   0b01111001,
   0b01000001,
   0b01000001,
   0b00111110,
   // A
   0b00000000,
   0b01111100,
   0b00010010,
   0b00010001,
   0b00010001,
   0b00010001,
   0b00010010,
   0b01111100,
   // B
   0b00000000,
   0b01111111,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b00110110,
   // C
   0b00000000,
   0b00111110,
   0b01000001,
   0b01000001,
   0b01000001,
   0b01000001,
   0b01000001,
   0b00100010,
   // D
   0b00000000,
   0b01111111,
   0b01000001,
   0b01000001,
   0b01000001,
   0b01000001,
   0b00100010,
   0b00011100,
   // E
   0b00000000,
   0b01111111,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01000001,
   // F
   0b00000000,
   0b01111111,
   0b00001001,
   0b00001001,
   0b00001001,
   0b00001001,
   0b00000001,
   0b00000001,
   // G
   0b00000000,
   0b00111110,
   0b01000001,
   0b01000001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01111010,
   // H
   0b00000000,
   0b01111111,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b01111111,
   // I
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b01111111,
   0b00000000,
   0b00000000,
   0b00000000,
   // J
   0b00000000,
   0b00100000,
   0b01000000,
   0b01000001,
   0b01000001,
   0b00111111,
   0b00000001,
   0b00000001,
   // K
   0b00000000,
   0b01111111,
   0b00001000,
   0b00001100,
   0b00010010,
   0b00100001,
   0b01000000,
   0b00000000,
   // L
   0b00000000,
   0b01111111,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   // M
   0b00000000,
   0b01111111,
   0b00000010,
   0b00000100,
   0b00001000,
   0b00000100,
   0b00000010,
   0b01111111,
   // N
   0b00000000,
   0b01111111,
   0b00000010,
   0b00000100,
   0b00001000,
   0b00010000,
   0b00100000,
   0b01111111,
   // O
   0b00000000,
   0b00111110,
   0b01000001,
   0b01000001,
   0b01000001,
   0b01000001,
   0b01000001,
   0b00111110,
   // P
   0b00000000,
   0b01111111,
   0b00001001,
   0b00001001,
   0b00001001,
   0b00001001,
   0b00001001,
   0b00000110,
   // Q
   0b00000000,
   0b00111110,
   0b01000001,
   0b01000001,
   0b01000001,
   0b01010001,
   0b00100001,
   0b01011110,
   // R
   0b00000000,
   0b01111111,
   0b00001001,
   0b00001001,
   0b00001001,
   0b00011001,
   0b00101001,
   0b01000110,
   // S
   0b00000000,
   0b00000110,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b00110010,
   // T
   0b00000000,
   0b00000001,
   0b00000001,
   0b00000001,
   0b01111111,
   0b00000001,
   0b00000001,
   0b00000001,
   // U
   0b00000000,
   0b00111111,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b00111111,
   // V
   0b00000000,
   0b00001111,
   0b00010000,
   0b00100000,
   0b01000000,
   0b00100000,
   0b00010000,
   0b00001111,
   // W
   0b00000000,
   0b00111111,
   0b01000000,
   0b00100000,
   0b00011000,
   0b00100000,
   0b01000000,
   0b00111111,
   // X
   0b00000000,
   0b01000001,
   0b00100010,
   0b00010100,
   0b00001000,
   0b00010100,
   0b00100010,
   0b01000001,
   // Y
   0b00000000,
   0b00000011,
   0b00000100,
   0b00001000,
   0b01110000,
   0b00001000,
   0b00000100,
   0b00000011,
   // Z
   0b00000000,
   0b01000001,
   0b01100001,
   0b01010001,
   0b01001001,
   0b01000101,
   0b01000011,
   0b01000001,
   // [
   0b00000000,
   0b00000000,
   0b01111111,
   0b01000001,
   0b01000001,
   0b01000001,
   0b00000000,
   0b00000000,
   // "\"
   0b00000000,
   0b00101001,
   0b00101010,
   0b00101100,
   0b01111000,
   0b00101100,
   0b00101010,
   0b00101001,
   // ]
   0b00000000,
   0b00000000,
   0b01000001,
   0b01000001,
   0b01000001,
   0b01111111,
   0b00000000,
   0b00000000,
   // ^
   0b00000000,
   0b00001000,
   0b00000100,
   0b00000010,
   0b00000001,
   0b00000010,
   0b00000100,
   0b00001000,
   // _
   0b00000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b01000000,
   // `
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000011,
   0b00000100,
   // a
   0b00000000,
   0b00110000,
   0b01001000,
   0b01000100,
   0b01000100,
   0b00100100,
   0b01111000,
   0b00000000,
   // b
   0b00000000,
   0b01111111,
   0b00101000,
   0b01000100,
   0b01000100,
   0b01000100,
   0b00111000,
   0b00000000,
   // c
   0b00000000,
   0b00111000,
   0b01000100,
   0b01000100,
   0b01000100,
   0b01000100,
   0b00000000,
   0b00000000,
   // d
   0b00000000,
   0b00111000,
   0b01000100,
   0b01000100,
   0b01000100,
   0b00101000,
   0b01111111,
   0b00000000,
   // e
   0b00000000,
   0b00111000,
   0b01010100,
   0b01010100,
   0b01010100,
   0b01010100,
   0b01001000,
   0b00000000,
   // f
   0b00000000,
   0b00001000,
   0b00001000,
   0b01111110,
   0b00001001,
   0b00001001,
   0b00000010,
   0b00000000,
   // g
   0b00000000,
   0b00001110,
   0b01010001,
   0b01010001,
   0b01010001,
   0b01001010,
   0b00111111,
   0b00000000,
   // h
   0b00000000,
   0b01111111,
   0b00001000,
   0b00000100,
   0b00000100,
   0b01111000,
   0b00000000,
   0b00000000,
   // i
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b01111010,
   0b00000000,
   0b00000000,
   0b00000000,
   // j
   0b00000000,
   0b00000000,
   0b00000000,
   0b00110000,
   0b01000000,
   0b01000000,
   0b00111101,
   0b00000000,
   // k
   0b00000000,
   0b01111111,
   0b00010000,
   0b00010000,
   0b00101000,
   0b01000100,
   0b00000000,
   0b00000000,
   // l
   0b00000000,
   0b00000000,
   0b00000000,
   0b01111111,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   // m
   0b00000000,
   0b01111100,
   0b00000100,
   0b00000100,
   0b01111000,
   0b00000100,
   0b00000100,
   0b01111000,
   // n
   0b00000000,
   0b01111100,
   0b00001000,
   0b00000100,
   0b00000100,
   0b00000100,
   0b01111000,
   0b00000000,
   // o
   0b00000000,
   0b00111000,
   0b01000100,
   0b01000100,
   0b01000100,
   0b01000100,
   0b00111000,
   0b00000000,
   // p
   0b00000000,
   0b01111111,
   0b00001010,
   0b00010001,
   0b00010001,
   0b00010001,
   0b00001110,
   0b00000000,
   // q
   0b00000000,
   0b00001110,
   0b00010001,
   0b00010001,
   0b00010001,
   0b00001010,
   0b01111111,
   0b00000000,
   // r
   0b00000000,
   0b01111100,
   0b00001000,
   0b00000100,
   0b00000100,
   0b00000100,
   0b00001000,
   0b00000000,
   // s
   0b00000000,
   0b00100100,
   0b01001010,
   0b01001010,
   0b01010010,
   0b01010010,
   0b00100100,
   0b00000000,
   // t
   0b00000000,
   0b00000100,
   0b00000100,
   0b01111111,
   0b01000100,
   0b01000100,
   0b00000000,
   0b00000000,
   // u
   0b00000000,
   0b00111100,
   0b01000000,
   0b01000000,
   0b01000000,
   0b00111100,
   0b00000000,
   0b00000000,
   // v
   0b00000000,
   0b00011100,
   0b00100000,
   0b01000000,
   0b00100000,
   0b00011100,
   0b00000000,
   0b00000000,
   // w
   0b00000000,
   0b00111100,
   0b01000000,
   0b01000000,
   0b00111000,
   0b01000000,
   0b01000000,
   0b00111100,
   // x
   0b00000000,
   0b01000100,
   0b00101000,
   0b00010000,
   0b00101000,
   0b01000100,
   0b00000000,
   0b00000000,
   // y
   0b00000000,
   0b00100111,
   0b01001000,
   0b01001000,
   0b01001000,
   0b01001000,
   0b00111111,
   0b00000000,
   // z
   0b00000000,
   0b01000100,
   0b01100100,
   0b01010100,
   0b01001100,
   0b01000100,
   0b00000000,
   0b00000000,
   // {
   0b00000000,
   0b00001000,
   0b00110110,
   0b01000001,
   0b01000001,
   0b01000001,
   0b00000000,
   0b00000000,
   // |
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b01100011,
   0b00000000,
   0b00000000,
   0b00000000,
   // }
   0b00000000,
   0b01000001,
   0b01000001,
   0b01000001,
   0b00110110,
   0b00001000,
   0b00000000,
   0b00000000,
   // ~
   0b00000000,
   0b00000010,
   0b00000001,
   0b00000001,
   0b00000010,
   0b00000100,
   0b00000100,
   0b00000010,
   //  (0x7f)
   0b01111111,
   0b01111111,
   0b01111111,
   0b01111111,
   0b01111111,
   0b01111111,
   0b01111111,
   0b01111111,
   // ta(0x80)
   0b00000000,
   0b01000100,
   0b01000010,
   0b01000101,
   0b00101001,
   0b00010001,
   0b00001001,
   0b00000111,
   // ti(0x81)
   0b00000000,
   0b01010100,
   0b01010100,
   0b01010100,
   0b00111110,
   0b00010001,
   0b00010000,
   0b00010000,
   // tu(0x82)
   0b00000000,
   0b00001110,
   0b01000000,
   0b01000000,
   0b01001110,
   0b00100000,
   0b00010000,
   0b00001110,
   // te(0x83)
   0b00000000,
   0b00000100,
   0b01000101,
   0b00100101,
   0b00011101,
   0b00000101,
   0b00000101,
   0b00000100,
   // to(0x84)
   0b00000000,
   0b00000000,
   0b00000000,
   0b01111111,
   0b00001000,
   0b00010000,
   0b00000000,
   0b00000000,
   // na(0x85)
   0b00000000,
   0b00000100,
   0b01000100,
   0b00100100,
   0b00011111,
   0b00000100,
   0b00000100,
   0b00000100,
   // ni(0x86)
   0b00000000,
   0b01000000,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000000,
   // nu(0x87)
   0b00000000,
   0b00000010,
   0b01000010,
   0b01000010,
   0b00101010,
   0b00010010,
   0b00101010,
   0b00000110,
   // ne(0x88)
   0b00000000,
   0b00000010,
   0b00100010,
   0b00010010,
   0b01110011,
   0b00011010,
   0b00100110,
   0b00000010,
   // no(0x89)
   0b00000000,
   0b01000000,
   0b01000000,
   0b00100000,
   0b00010000,
   0b00001000,
   0b00000111,
   0b00000000,
   // ha(0x8A)
   0b00000000,
   0b01111000,
   0b00000000,
   0b00000000,
   0b00000001,
   0b00000010,
   0b00000100,
   0b01111000,
   // hi(0x8B)
   0b00000000,
   0b00111111,
   0b01000100,
   0b01000100,
   0b01000100,
   0b01000100,
   0b01000100,
   0b01000100,
   // hu(0x8C)
   0b00000000,
   0b00000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b00100010,
   0b00011110,
   // he(0x8D)
   0b00000000,
   0b00001000,
   0b00000100,
   0b00000010,
   0b00000100,
   0b00001000,
   0b00010000,
   0b00100000,
   // ho(0x8E)
   0b00000000,
   0b00100010,
   0b00010010,
   0b00000010,
   0b01111111,
   0b00000010,
   0b00010010,
   0b00100010,
   // ma(0x8F)
   0b00000000,
   0b00000001,
   0b00000001,
   0b00010001,
   0b00100001,
   0b01010001,
   0b00001001,
   0b00000111,
   //mi(0x90)
   0b00000000,
   0b00010000,
   0b00100100,
   0b01001001,
   0b00010010,
   0b00100100,
   0b00001000,
   0b00000000,
   // mu(0x91)
   0b00000000,
   0b00110000,
   0b00101000,
   0b00100100,
   0b00100010,
   0b00110001,
   0b00100000,
   0b01000000,
   // me(0x92)
   0b00000000,
   0b01000000,
   0b01000000,
   0b00101000,
   0b00010000,
   0b00101000,
   0b00000100,
   0b00000011,
   // mo(0x93)
   0b00000000,
   0b00001010,
   0b00001010,
   0b00001010,
   0b01111110,
   0b01001010,
   0b01001010,
   0b01001010,
   // ya(0x94)
   0b00000000,
   0b00000100,
   0b00000100,
   0b01111111,
   0b00000100,
   0b00000100,
   0b00010100,
   0b00001100,
   // yu(0x95)
   0b00000000,
   0b01000000,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01111110,
   0b01000000,
   0b01000000,
   // yo(0x96)
   0b00000000,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01111111,
   // ra(0x97)
   0b00000000,
   0b00000101,
   0b00000101,
   0b01000101,
   0b01000101,
   0b00100101,
   0b00010101,
   0b00001101,
   // ri(0x98)
   0b00000000,
   0b00001111,
   0b01000000,
   0b01000000,
   0b01000000,
   0b00100000,
   0b00011111,
   0b00000000,
   // ru(0x99)
   0b00000000,
   0b01000000,
   0b00111111,
   0b00000000,
   0b01111111,
   0b01000000,
   0b00100000,
   0b00011000,
   // re(0x9A)
   0b00000000,
   0b01111111,
   0b01000000,
   0b00100000,
   0b00010000,
   0b00001000,
   0b00000100,
   0b00000000,
   // ro(0x9B)
   0b00000000,
   0b01111110,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01111110,
   // wa(0x9C)
   0b00000000,
   0b00001110,
   0b00000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b00100010,
   0b00011110,
   // nn(0x9D)
   0b00000000,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000000,
   0b00100000,
   0b00010000,
   0b00001100,
   // dakuten(0x9E)
   0b00000000,
   0b00000010,
   0b00000100,
   0b00000001,
   0b00000010,
   0b00000000,
   0b00000000,
   0b00000000,
   // handakuten(0x9F)
   0b00000000,
   0b00000111,
   0b00000101,
   0b00000111,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xA0)
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xA1)
   0b00000000,
   0b01110000,
   0b01010000,
   0b01110000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xA2)
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000111,
   0b00000001,
   0b00000001,
   0b00000000,
   //(0xA3)
   0b00000000,
   0b01000000,
   0b01000000,
   0b01110000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xA4)
   0b00000000,
   0b00010000,
   0b00100000,
   0b01000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xA5)
   0b00000000,
   0b00000000,
   0b00110000,
   0b00110000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   // wo(0xA6)
   0b00000000,
   0b00001010,
   0b00001010,
   0b01001010,
   0b01001010,
   0b01001010,
   0b00101010,
   0b00011110,
   // xa(0xA7)
   0b00000000,
   0b00000000,
   0b00000100,
   0b01000100,
   0b00110100,
   0b00010100,
   0b00001100,
   0b00000000,
   // xi(0xA8)
   0b00000000,
   0b00000000,
   0b00100000,
   0b00010000,
   0b01111000,
   0b00000100,
   0b00000000,
   0b00000000,
   // xu(0xA9)
   0b00000000,
   0b00000000,
   0b00011000,
   0b01001000,
   0b01001000,
   0b01001000,
   0b00111000,
   0b00000000,
   // xe(0xAA)
   0b00000000,
   0b00000000,
   0b01001000,
   0b01001000,
   0b01111000,
   0b01001000,
   0b01001000,
   0b00000000,
   // xo(0xAB)
   0b00000000,
   0b00000000,
   0b01001000,
   0b00101000,
   0b00011000,
   0b11111100,
   0b00001000,
   0b00000000,
   // xya(0xAC)
   0b00000000,
   0b00001000,
   0b01111100,
   0b00001000,
   0b00001000,
   0b00101000,
   0b00011000,
   0b00000000,
   // xyu(0xAD)
   0b00000000,
   0b00000000,
   0b01000000,
   0b01001000,
   0b01001000,
   0b01111000,
   0b01000000,
   0b00000000,
   // xyo(0xAE)
   0b00000000,
   0b00000000,
   0b01010100,
   0b01010100,
   0b01010100,
   0b01111100,
   0b00000000,
   0b00000000,
   // ttu(0xAF)
   0b00000000,
   0b00000000,
   0b00011000,
   0b00000000,
   0b01011000,
   0b01000000,
   0b00111000,
   0b00000000,
   //(0xB0)
   0b00000000,
   0b00000000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00001000,
   0b00000000,
   // a(0xB1)
   0b00000000,
   0b00000001,
   0b01000001,
   0b01000001,
   0b00111001,
   0b00010001,
   0b00001001,
   0b00000111,
   // i(0xB2)
   0b00000000,
   0b00100000,
   0b00010000,
   0b00001000,
   0b01111100,
   0b00000010,
   0b00000001,
   0b00000000,
   // u(0xB3)
   0b00000000,
   0b00011100,
   0b00000100,
   0b00000100,
   0b01000111,
   0b01000100,
   0b00100100,
   0b00011100,
   // e(0xB4)
   0b00000000,
   0b01000000,
   0b01000010,
   0b01000010,
   0b01111110,
   0b01000010,
   0b01000010,
   0b01000000,
   // o(0xB5)
   0b00000000,
   0b00100010,
   0b00010010,
   0b00001010,
   0b00000110,
   0b01111111,
   0b00000010,
   0b00000010,
   // ka(0xB6)
   0b00000000,
   0b00000100,
   0b01000100,
   0b00111110,
   0b00000100,
   0b00000100,
   0b01000100,
   0b00111100,
   // ki(0xB7)
   0b00000000,
   0b00001010,
   0b00001010,
   0b00001010,
   0b01111111,
   0b00001010,
   0b00001010,
   0b00001010,
   // ku(0xB8)
   0b00000000,
   0b00000000,
   0b01001000,
   0b01000111,
   0b00100001,
   0b00010001,
   0b00001110,
   0b00000000,
   // ke(0xB9)
   0b00000000,
   0b00000100,
   0b00000011,
   0b00000010,
   0b01000010,
   0b00111110,
   0b00000010,
   0b00000010,
   // ko(0xBA)
   0b00000000,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01111110,
   // sa(0xBB)
   0b00000000,
   0b00000010,
   0b00000111,
   0b00000010,
   0b01000010,
   0b00100010,
   0b00011111,
   0b00000010,
   // si(0xBC)
   0b00000000,
   0b01001010,
   0b01001010,
   0b01001010,
   0b01000000,
   0b01000000,
   0b00100000,
   0b00011100,
   // su(0xBD)
   0b00000000,
   0b00000001,
   0b01000001,
   0b00100001,
   0b00010001,
   0b00011001,
   0b00100101,
   0b01000011,
   // se(0xBE)
   0b00000000,
   0b00000010,
   0b01111111,
   0b01000010,
   0b01000010,
   0b01000010,
   0b01001010,
   0b01000110,
   // so(0xBF)
   0b00000000,
   0b00000110,
   0b00001000,
   0b01000000,
   0b01000000,
   0b01000000,
   0b00100000,
   0b00011110,
   //(0xC0)
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00011000,
   0b00100100,
   0b01000010,
   0b10000001,
   //(0xC1)
   0b10000000,
   0b01000000,
   0b00100000,
   0b00010000,
   0b00010000,
   0b00100000,
   0b01000000,
   0b10000000,
   //(0xC2)
   0b00000000,
   0b00000000,
   0b11000000,
   0b11110000,
   0b11111000,
   0b11111000,
   0b11111100,
   0b11111100,
   //(0xC3)
   0b11111100,
   0b11111100,
   0b11111000,
   0b11111000,
   0b11110000,
   0b11000000,
   0b00000000,
   0b00000000,
   //(0xC4)
   0b00000000,
   0b00000000,
   0b00000011,
   0b00001111,
   0b00011111,
   0b00011111,
   0b00111111,
   0b00111111,
   //(0xC5)
   0b00111111,
   0b00111111,
   0b00011111,
   0b00011111,
   0b00001111,
   0b00000011,
   0b00000000,
   0b00000000,
   //(0xC6)
   0b00000000,
   0b00000000,
   0b11100000,
   0b00010000,
   0b00001000,
   0b00000100,
   0b00000100,
   0b00000100,
   //(0xC7)
   0b00000100,
   0b00000100,
   0b00000100,
   0b00001000,
   0b00010000,
   0b11100000,
   0b00000000,
   0b00000000,
   //(0xC8)
   0b00000000,
   0b00000000,
   0b00000111,
   0b00001000,
   0b00010000,
   0b00100000,
   0b00100000,
   0b00100000,
   //(0xC9)
   0b00100000,
   0b00100000,
   0b00100000,
   0b00010000,
   0b00001000,
   0b00000111,
   0b00000000,
   0b00000000,
   //(0xCA)
   0b00000000,
   0b00011000,
   0b00111100,
   0b01111110,
   0b01111110,
   0b00111100,
   0b00011000,
   0b00000000,
   //(0xCB)
   0b11111111,
   0b11100111,
   0b11000011,
   0b10000001,
   0b10000001,
   0b11000011,
   0b11100111,
   0b11111111,
   //(0xCC)
   0b00000000,
   0b00011000,
   0b00100100,
   0b01000010,
   0b01000010,
   0b00100100,
   0b00011000,
   0b00000000,
   //(0xCD)
   0b10101010,
   0b11111111,
   0b10101010,
   0b11111111,
   0b10101010,
   0b11111111,
   0b10101010,
   0b11111111,
   //(0xCE)
   0b10101010,
   0b11111111,
   0b10101010,
   0b11111111,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xCF)
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b11111111,
   0b10101010,
   0b11111111,
   0b10101010,
   //(0xD0)
   0b00001010,
   0b00001111,
   0b00001010,
   0b00001111,
   0b00001010,
   0b00001111,
   0b00001010,
   0b00001111,
   //(0xD1)
   0b01010000,
   0b11110000,
   0b01010000,
   0b11110000,
   0b01010000,
   0b11110000,
   0b01010000,
   0b11110000,
   //(0xD2)
   0b00000000,
   0b00011000,
   0b01011100,
   0b01111110,
   0b01111111,
   0b01111110,
   0b01011100,
   0b00011000,
   //(0xD3)
   0b00000000,
   0b00001110,
   0b00011111,
   0b00111111,
   0b01111110,
   0b00111111,
   0b00011111,
   0b00001110,
   //(0xD4)
   0b00000000,
   0b00001000,
   0b00011100,
   0b00111110,
   0b01111111,
   0b00111110,
   0b00011100,
   0b00001000,
   //(0xD5)
   0b00000000,
   0b00011100,
   0b01011100,
   0b01001111,
   0b01111111,
   0b01001111,
   0b01011100,
   0b00011100,
   //(0xD6)
   0b00000000,
   0b00000000,
   0b00011100,
   0b01111110,
   0b00011100,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xD7)
   0b00000000,
   0b00100000,
   0b00110100,
   0b01111110,
   0b00110100,
   0b00100000,
   0b00000000,
   0b00000000,
   //(0xD8)
   0b00001000,
   0b00110000,
   0b01010100,
   0b01111110,
   0b01010100,
   0b00110000,
   0b00001000,
   0b00000000,
   //(0xD9)
   0b00000000,
   0b00100000,
   0b01110100,
   0b01111110,
   0b01110100,
   0b00100000,
   0b00000000,
   0b00000000,
   //(0xDA)
   0b00000000,
   0b00100000,
   0b01101110,
   0b01111111,
   0b01101110,
   0b00100000,
   0b00000000,
   0b00000000,
   //(0xDB)
   0b00000000,
   0b00010000,
   0b00111000,
   0b00011100,
   0b01111110,
   0b01111100,
   0b01111110,
   0b00000000,
   //(0xDC)
   0b00000000,
   0b01001110,
   0b01111000,
   0b01111110,
   0b01111000,
   0b01001110,
   0b00000000,
   0b00000000,
   //(0xDD)
   0b00000000,
   0b01000000,
   0b01100000,
   0b01111110,
   0b01111110,
   0b01100000,
   0b01000000,
   0b00000000,
   //(0xDE)
   0b01111100,
   0b11111110,
   0b11111110,
   0b11111111,
   0b11111110,
   0b11111110,
   0b01111110,
   0b00010000,
   //(0xDF)
   0b01111100,
   0b10000010,
   0b10000010,
   0b10000011,
   0b10000010,
   0b10000010,
   0b01111100,
   0b00010000,
   //(0xE0)
   0b00000000,
   0b00010000,
   0b00010000,
   0b00010000,
   0b00010000,
   0b00010000,
   0b00010000,
   0b00000000,
   //(0xE1)
   0b00000000,
   0b00100000,
   0b00100100,
   0b00100100,
   0b00100100,
   0b00100100,
   0b00100000,
   0b00000000,
   //(0xE2)
   0b00000000,
   0b01000000,
   0b01000100,
   0b01010100,
   0b01010100,
   0b01000100,
   0b01000000,
   0b00000000,
   //(0xE3)
   0b01111100,
   0b01010100,
   0b01011100,
   0b01000100,
   0b01011100,
   0b01010100,
   0b01111100,
   0b00000000,
   //(0xE4)
   0b00000000,
   0b01000000,
   0b01010100,
   0b01111100,
   0b01010100,
   0b01110000,
   0b01000000,
   0b00000000,
   //(0xE5)
   0b00000000,
   0b01001000,
   0b00101000,
   0b00001110,
   0b00101000,
   0b01001000,
   0b00000000,
   0b00000000,
   //(0xE6)
   0b00000000,
   0b00001000,
   0b00001000,
   0b01111110,
   0b01001000,
   0b01001000,
   0b01001000,
   0b00000000,
   //(0xE7)
   0b00000000,
   0b00100000,
   0b00011100,
   0b00000000,
   0b00001100,
   0b00010000,
   0b00100000,
   0b00000000,
   //(0xE8)
   0b00000000,
   0b01000000,
   0b00100100,
   0b00011110,
   0b00000100,
   0b01111100,
   0b01000000,
   0b00000000,
   //(0xE9)
   0b00000000,
   0b00001000,
   0b00001000,
   0b01111110,
   0b00001000,
   0b00001000,
   0b00000000,
   0b00000000,
   //(0xEA)
   0b00000000,
   0b01111101,
   0b01010101,
   0b01010111,
   0b01010101,
   0b01010101,
   0b01010101,
   0b01111100,
   //(0xEB)
   0b00000000,
   0b00001000,
   0b00001010,
   0b00001010,
   0b01111110,
   0b00001001,
   0b00001000,
   0b00001000,
   //(0xEC)
   0b00000000,
   0b01000010,
   0b00100010,
   0b00011110,
   0b10001010,
   0b01001010,
   0b00111010,
   0b00000010,
   //(0xED)
   0b00000000,
   0b01111111,
   0b00001001,
   0b00001001,
   0b00001111,
   0b00001001,
   0b00001001,
   0b01111111,
   //(0xEE)
   0b00000000,
   0b01111111,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01001001,
   0b01111111,
   //(0xEF)
   0b00000000,
   0b01000000,
   0b00111111,
   0b00010101,
   0b00010101,
   0b00010101,
   0b00010101,
   0b01111111,
   //(0xF0)
   0b00000000,
   0b01000000,
   0b00100110,
   0b00010000,
   0b00001111,
   0b00010000,
   0b00100110,
   0b01000000,
   //(0xF1)
   0b00000000,
   0b01000100,
   0b00100100,
   0b00011100,
   0b01111111,
   0b00011000,
   0b00100100,
   0b01000010,
   //(0xF2)
   0b00000000,
   0b00100100,
   0b00010100,
   0b00001100,
   0b01111111,
   0b00001100,
   0b00010100,
   0b00100100,
   //(0xF3)
   0b00000000,
   0b01001000,
   0b01100100,
   0b01010110,
   0b01111101,
   0b01010110,
   0b01100100,
   0b01001000,
   //(0xF4)
   0b00000000,
   0b01000000,
   0b01001000,
   0b01001000,
   0b01111110,
   0b01001000,
   0b01001000,
   0b01000000,
   //(0xF5)
   0b00000000,
   0b01001110,
   0b01010100,
   0b01111110,
   0b01010100,
   0b01000100,
   0b00000000,
   0b00000000,
   //(0xF6)
   0b00000000,
   0b01001110,
   0b01110100,
   0b01010100,
   0b11111100,
   0b01010100,
   0b01000100,
   0b00000000,
   //(0xF7)
   0b00111110,
   0b00101010,
   0b00111110,
   0b00000000,
   0b01101010,
   0b00101111,
   0b11111010,
   0b00101000,
   //(0xF8)
   0b00000000,
   0b00001000,
   0b01010100,
   0b00110010,
   0b00010010,
   0b01110100,
   0b00001000,
   0b00000000,
   //(0xF9)
   0b00000000,
   0b00100100,
   0b00010101,
   0b01111111,
   0b00010101,
   0b01001100,
   0b00111111,
   0b00011100,
   //(0xFA)
   0b00000000,
   0b01000010,
   0b00000000,
   0b00011000,
   0b00011000,
   0b00000000,
   0b01000010,
   0b00000000,
   //(0xFB)
   0b01010101,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   0b00000000,
   //(0xFC)
   0b10000000,
   0b00000000,
   0b10000000,
   0b00000000,
   0b10000000,
   0b00000000,
   0b10000000,
   0b00000000,
   //(0xFD)
   0b10000000,
   0b00000000,
   0b00100000,
   0b00000000,
   0b00001000,
   0b00000000,
   0b00000010,
   0b00000000,
   //(0xFE)
   0b00000001,
   0b00000000,
   0b00000100,
   0b00000000,
   0b00010000,
   0b00000000,
   0b01000000,
   0b00000000,
   //(0xFF)
   0b00010000,
   0b00010000,
   0b00111000,
   0b11101111,
   0b00111000,
   0b00010000,
   0b00010000,
   0b00010000
  };

Font font_TK80BS_KANA =
  { bmp_TK80BS_KANA,
    "TK80BS_KANA",
    8, // width
    8, // height
    0, // xspacing
    0, // yspacing
    32, // first code
    255 // last code
  };

