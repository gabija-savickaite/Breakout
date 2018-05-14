/*  Author: Steve Gunn
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *           View this license at http://creativecommons.org/about/licenses/
 *
 *  
 *  - Jan 2015  Modified for LaFortuna (Rev A, black edition) [KPZ]
 * 
 *  Modified by Gabija Savickaite to include colours taken from https://forum.arduino.cc/index.php?topic=451297.0
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "font.h"
#include "ili934x.h"
#include "lcd.h"

lcd display;
static inline uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
colours[ARRAYSIZE] = {
    0x0257,
    0xB5E3,
    0x7DDD,
    0xCFFC,
    0xB437,
    0x5C55,
    0x0191,
    0x7518,
    0xA805,
    0xF79C,
    0xF7DF,
    0x86E0,
    0xE126,
    0xC302,
    0xEEF9,
    0xE14A,
    0x994D,
    0xF4F7,
    0xA929,
    0xD105,
    0x3BCA,
    0x0636,
    0xFDE0,
    0xFBE0,
    0xF807,
    0x9B39,
    0xA627,
    0xF79E,
    0xCCAE,
    0x62E3,
    0x92F0,
    0x80C5,
    0xFF5A,
    0x0400,
    0x8DA0,
    0xFE76,
    0x07FF,
    0x7FFA,
    0xD7E2,
    0x4A84,
    0x3A29,
    0x8CAF,
    0xEEAD,
    0xB5F6,
    0x854D,
    0xFCCC,
    0xA145,
    0xFF60,
    0x6BF0,
    0x5400,
    0xF90A,
    0xC4CA,
    0x03FF,
    0xF7FF,
    0xF7FF,
    0xDF5E,
    0x8E7E,
    0xA65E,
    0xF618,
    0xFFFF,
    0xFC95,
    0x2559,
    0xFF36,
    0xFF06,
    0x0349,
    0xE111,
    0x7840,
    0x1D7A,
    0x8430,
    0x9BAF,
    0xBEBC,
    0x9C0E,
    0xFB6F,
    0xF7BB,
    0x2AD2,
    0x9928,
    0xEC6B,
    0xFF38,
    0x3943,
    0x9382,
    0xCF01,
    0xBFE0,
    0xFB6B,
    0xBA6A,
    0x0000,
    0x3860,
    0x530D,
    0x21A5,
    0x39E6,
    0xBD76,
    0xFF59,
    0xA38C,
    0x347C,
    0xAF3D,
    0xFF97,
    0x001F,
    0x1BBF,
    0x0495,
    0x0437,
    0x00D5,
    0x3193,
    0x023F,
    0xA51A,
    0x05DF,
    0x64D9,
    0x0CD7,
    0x5D7D,
    0xAF3D,
    0x51B2,
    0x1310,
    0x895C,
    0x5394,
    0x4C3E,
    0x18FE,
    0xDAF0,
    0x7A27,
    0x04B6,
    0xE6D9,
    0xDF0D,
    0xC800,
    0x0349,
    0x818C,
    0x039F,
    0xB528,
    0xCA0A,
    0x1D7A,
    0x67E0,
    0xBCBC,
    0xDC9D,
    0xC109,
    0x1BBA,
    0xF80F,
    0x0F5B,
    0xD4FD,
    0xFD43,
    0x34DF,
    0xF5DF,
    0xFAB4,
    0xFB0F,
    0x0204,
    0xCBE6,
    0x7380,
    0x9240,
    0xA145,
    0x6A24,
    0xAB69,
    0xCCCC,
    0x1A67,
    0xFE19,
    0xE7FF,
    0x7DAC,
    0xF6F0,
    0x4820,
    0x8004,
    0xDDD0,
    0xA3CE,
    0xCAA0,
    0xEBAA,
    0x8984,
    0x251D,
    0xB994,
    0x714C,
    0x534E,
    0x5CF4,
    0x9516,
    0x0347,
    0xEC25,
    0xE004,
    0xFFA0,
    0xA3CB,
    0x49A4,
    0x1A65,
    0xA615,
    0xC4CD,
    0xEDD9,
    0x7C2D,
    0xFFF3,
    0xFF60,
    0xF840,
    0xE38F,
    0x05FF,
    0x5924,
    0xC0E7,
    0x0673,
    0x9003,
    0xD008,
    0xEA68,
    0xF807,
    0xFD39,
    0xB0C3,
    0x551A,
    0xEC84,
    0x02A7,
    0x014F,
    0x71A8,
    0xCAC9,
    0x9519,
    0xAF15,
    0x03D4,
    0x2C2F,
    0xB7FF,
    0x4CBA,
    0xD98C,
    0xE9D0,
    0x03D4,
    0x2A97,
    0x6CD8,
    0x03D4,
    0xE1E6,
    0xA3CB,
    0xF739,
    0xF6F9,
    0x3229,
    0x2145,
    0xE475,
    0xDFE0,
    0x7FE0,
    0xD98C,
    0xFDB8,
    0x9226,
    0xDB74,
    0xAA8D,
    0xA9C3,
    0x8311,
    0x4FE0,
    0x79E0,
    0xD343,
    0xFD20,
    0x9C0F,
    0xE206,
    0xD343,
    0xCB0F,
    0xE681,
    0x9D43,
    0x78A6,
    0xFE7C,
    0x0235,
    0xD343,
    0x92C7,
    0x6A66,
    0xC6DC,
    0xFC0F,
    0x016C,
    0x8C95,
    0xBB86,
    0xDC4C,
    0xAB6D,
    0xCB6A,
    0x9B2C,
    0xF9C0,
    0xFBEA,
    0xFC0F,
    0xFA08,
    0xFBED,
    0x89E8,
    0xFF6B,
    0xB0C3,
    0x64BD,
    0xFFDB,
    0x2971,
    0xFFDC,
    0x8307,
    0xFDFB,
    0xFFFA,
    0xD8A7,
    0xB806,
    0x9800,
    0xF7BE,
    0x07FF,
    0x4C16,
    0x4417,
    0x2AD3,
    0x1C58,
    0x05BD,
    0x5A0F,
    0xFE80,
    0xF374,
    0xFFE6,
    0xF706,
    0x0011,
    0x6333,
    0x6204,
    0x8B29,
    0x59CA,
    0xA000,
    0x0A2F,
    0x9B4C,
    0xCAC8,
    0x0451,
    0x534F,
    0xBC21,
    0xAD55,
    0x0184,
    0x0320,
    0x1925,
    0x020D,
    0x00AF,
    0x1924,
    0xBDAD,
    0x49E6,
    0x7272,
    0x5249,
    0x51E6,
    0x8811,
    0xAD55,
    0x018C,
    0x4AE4,
    0x5345,
    0xFC60,
    0x9999,
    0x74F9,
    0x0607,
    0x937A,
    0xC1C4,
    0xE2B0,
    0x0193,
    0x49C7,
    0x30C6,
    0x812A,
    0x8800,
    0xECAF,
    0x5003,
    0x8DF1,
    0x38A2,
    0x8DFA,
    0x49F1,
    0x2A69,
    0x1388,
    0x940A,
    0xFD42,
    0x49E6,
    0xCA6B,
    0x067A,
    0xD5F5,
    0x901A,
    0x9C21,
    0x0387,
    0x52AA,
    0xD04A,
    0x440D,
    0xA907,
    0xE987,
    0xEB45,
    0xD990,
    0xFEB4,
    0xBA69,
    0x7208,
    0xC2B8,
    0x0321,
    0x0BEC,
    0x0249,
    0x318C,
    0xF623,
    0x9AB7,
    0xC819,
    0x8000,
    0xD39A,
    0x32E7,
    0xFE54,
    0xF8B2,
    0xAAED,
    0x8000,
    0x81EB,
    0xFCC6,
    0x05FF,
    0x4B2D,
    0x5345,
    0x7AEC,
    0x6209,
    0x300C,
    0xBC2B,
    0x1317,
    0x2216,
    0x64D3,
    0xC4CD,
    0xEE55,
    0xE9EA,
    0xBF9F,
    0x6B4D,
    0xC18A,
    0x9BAA,
    0x1C9F,
    0xD0CD,
    0x85CC,
    0x8470,
    0x6265,
    0x9382,
    0x0013,
    0xE679,
    0xEEF7,
    0xE54B,
    0x52EA,
    0xC590,
    0x18C3,
    0x620A,
    0xF75A,
    0x11B4,
    0x7FDF,
    0xF807,
    0x07FF,
    0x07E0,
    0x681F,
    0xF5DF,
    0xCFE0,
    0xB81F,
    0x381F,
    0x881F,
    0xFFE6,
    0x564F,
    0x6990,
    0x1A67,
    0xB412,
    0xAA4A,
    0xCA29,
    0x51EB,
    0x9654,
    0x46B5,
    0xC4CD,
    0x80C3,
    0xB191,
    0xDA90,
    0xF014,
    0xE54E,
    0x4AEA,
    0xFEB6,
    0x4BC8,
    0xF940,
    0x6AA3,
    0xFAAE,
    0xB104,
    0xC905,
    0xE2C4,
    0xFC75,
    0x6A24,
    0xF751,
    0xEEF0,
    0xA00D,
    0xFFDE,
    0xFDE0,
    0xF8B2,
    0xCFE0,
    0xF809,
    0x0224,
    0x2444,
    0xA3CB,
    0x8369,
    0x0397,
    0xF9F2,
    0x8311,
    0x9FE7,
    0xD39A,
    0xFB73,
    0x80AA,
    0x48A1,
    0xC169,
    0xF251,
    0x75BF,
    0x8839,
    0xA8E8,
    0xA73F,
    0xE9B4,
    0xF81F,
    0xC2B8,
    0xFBBF,
    0xC9CF,
    0xC20E,
    0xE420,
    0xCB2C,
    0xDEFB,
    0xE4C1,
    0x9B20,
    0xFEE8,
    0x03EC,
    0xFFDF,
    0xB2EA,
    0xFAC3,
    0xB320,
    0x6416,
    0xE75F,
    0xAC96,
    0x054C,
    0xD566,
    0xFEA0,
    0x83A9,
    0x9B22,
    0xFE00,
    0xFEE0,
    0xDD24,
    0x632C,
    0xAF34,
    0x6975,
    0x8410,
    0x8410,
    0xBDF7,
    0x42C8,
    0x8C95,
    0x07E0,
    0x1D6F,
    0x0400,
    0x054E,
    0x04ED,
    0x0568,
    0x052A,
    0x6586,
    0x1336,
    0x04CC,
    0xA7A6,
    0x6D74,
    0xAFE5,
    0x8AC3,
    0xACD0,
    0x07EF,
    0x29A7,
    0x61CA,
    0x4379,
    0x50DF,
    0xEEAD,
    0x3FE0,
    0x4643,
    0xC802,
    0xDC80,
    0x8400,
    0xFBC0,
    0x9003,
    0xDB9F,
    0xACD5,
    0xA817,
    0xF014,
    0xF7FE,
    0x0376,
    0x4BCD,
    0xF8F9,
    0xFB56,
    0x32E7,
    0x753A,
    0xFFAB,
    0x75EF,
    0x348E,
    0x616D,
    0x0112,
    0x6007,
    0xE947,
    0xB76B,
    0x4A8D,
    0x1441,
    0xCAEB,
    0xE54A,
    0x4810,
    0x08F2,
    0x4810,
    0xFA4D,
    0x3079,
    0x0174,
    0xFA60,
    0xB8A1,
    0xC1A5,
    0x5A79,
    0xB22D,
    0xF79D,
    0x0480,
    0xB7FF,
    0xFFFE,
    0x054D,
    0x9946,
    0x2209,
    0x598A,
    0xFEEF,
    0xD1C7,
    0xA04B,
    0xDB09,
    0x31A6,
    0xF642,
    0x8DDE,
    0xBECA,
    0x2D50,
    0x4DC2,
    0x78E0,
    0x3D93,
    0xEFB1,
    0xC592,
    0xF731,
    0x8F27,
    0x8962,
    0xE4F8,
    0x6A24,
    0x3206,
    0x5151,
    0xE801,
    0x0BC6,
    0xD65B,
    0x2313,
    0xFFEC,
    0xADD3,
    0xC884,
    0xB3FB,
    0xE73F,
    0xCE7F,
    0xFF9E,
    0xC61A,
    0x92BD,
    0xEC1D,
    0xE73F,
    0xFD7A,
    0x93D6,
    0xFD1C,
    0x7FE0,
    0xFFA0,
    0xFFD9,
    0xCD03,
    0xFFE0,
    0xE7E0,
    0xF757,
    0xFFA9,
    0x1882,
    0x52D4,
    0xFEB6,
    0xAEDC,
    0xB323,
    0xE32E,
    0x8D7C,
    0xF410,
    0x967D,
    0xF352,
    0xE7FF,
    0xFAF9,
    0xCD6F,
    0xFC3D,
    0xFFDA,
    0xD69A,
    0xCCD9,
    0x9772,
    0xFD9B,
    0xF731,
    0xD4D9,
    0xAEF5,
    0xFED6,
    0xE55A,
    0xB4FB,
    0xFDB8,
    0xEBAA,
    0xFD0F,
    0xFCD3,
    0x2595,
    0x867F,
    0x7453,
    0xB63B,
    0xB44D,
    0xE475,
    0xFFFC,
    0xCD19,
    0xACD5,
    0xBFE0,
    0x07E0,
    0x3666,
    0x9E01,
    0x1AC0,
    0xFF9C,
    0x179F,
    0xDB74,
    0x6D1B,
    0x6268,
    0xBB65,
    0x6963,
    0x9BAA,
    0x64D9,
    0xFF39,
    0xE104,
    0x00E7,
    0xFDF1,
    0xC986,
    0xF81F,
    0xFAB4,
    0xC8EF,
    0xD20F,
    0xF812,
    0x9A2E,
    0xC991,
    0xAF9A,
    0xFA2C,
    0xFFBF,
    0xC200,
    0xFF6B,
    0x629B,
    0x0ECA,
    0x94D5,
    0xF3C9,
    0xFC08,
    0x760C,
    0x8810,
    0xED04,
    0xC109,
    0x8000,
    0xB18C,
    0xE59F,
    0x92ED,
    0xECD5,
    0x4559,
    0x35F7,
    0xAD7C,
    0x5C66,
    0xDF2A,
    0x7190,
    0xD904,
    0xA1CF,
    0xFFC6,
    0xF5C9,
    0x4C88,
    0x761F,
    0xE5A7,
    0x66F5,
    0x0019,
    0xE025,
    0xAA06,
    0xF735,
    0x0292,
    0x19A5,
    0xDD1B,
    0xBABA,
    0x0334,
    0x939B,
    0xB990,
    0xAA0D,
    0x3D8E,
    0x86DD,
    0x7B5D,
    0xCEF0,
    0x07D3,
    0x6268,
    0x4E99,
    0x7A27,
    0xDB07,
    0xC0B0,
    0xFDCF,
    0xFEEF,
    0xFDF6,
    0x0BF1,
    0x9BE7,
    0xE00F,
    0x7EBC,
    0x8ED9,
    0x8B97,
    0x2046,
    0x4C6A,
    0xADEC,
    0xDC16,
    0xE46E,
    0xA28A,
    0xFF40,
    0xED8E,
    0x712E,
    0x18CE,
    0x024A,
    0xFE21,
    0xFFFE,
    0xFEDD,
    0xE7D1,
    0x33AF,
    0xF70A,
    0x3DB1,
    0xF7FF,
    0x9FF3,
    0xBDAE,
    0xFF3C,
    0xFF5A,
    0x9382,
    0x7558,
    0xA860,
    0x8D13,
    0x8CCB,
    0x35D1,
    0x9BD1,
    0x1A27,
    0x3306,
    0xC251,
    0x8470,
    0xFECB,
    0x33CE,
    0xD290,
    0xAA0F,
    0xF578,
    0x2C00,
    0xFECB,
    0xFEF5,
    0x0010,
    0x92BD,
    0xFD08,
    0xFA0C,
    0x3FE2,
    0x2278,
    0xD40F,
    0x73AE,
    0xA6FD,
    0x0486,
    0xEFFB,
    0x4A16,
    0x03B7,
    0x4DF2,
    0xCBA4,
    0x0400,
    0xFA88,
    0x4185,
    0xCDA7,
    0x51EB,
    0xFFBC,
    0x7B4F,
    0x6188,
    0x83E6,
    0xC410,
    0x8430,
    0x8400,
    0x6C64,
    0x39A3,
    0x9DCE,
    0x31C7,
    0xB434,
    0xFBE0,
    0xFBA7,
    0xFAC0,
    0xFCC0,
    0xFD20,
    0xFCE0,
    0xFA20,
    0xFAC7,
    0xFEAD,
    0xDB9A,
    0xF5F9,
    0xFA62,
    0x6204,
    0x4249,
    0xFB69,
    0x0108,
    0x9800,
    0x1D59,
    0x0320,
    0x21DC,
    0x694C,
    0xBEBC,
    0xAF7D,
    0x9BAA,
    0xAA06,
    0x9E3C,
    0xDD75,
    0xDC4C,
    0xAE7D,
    0x869F,
    0xE5F1,
    0xEF55,
    0x9FD3,
    0xDE9F,
    0xFC3C,
    0xFCD9,
    0xFEDB,
    0xDD1B,
    0xDB92,
    0x96FA,
    0xCE17,
    0xEF57,
    0xBCCF,
    0xAF7D,
    0xCCDF,
    0xDB92,
    0x6CC8,
    0x78C9,
    0x04CF,
    0xFF7A,
    0xE1EC,
    0x564F,
    0xDCD4,
    0xAE39,
    0x834A,
    0xCE78,
    0x76EE,
    0xF4D8,
    0xFD88,
    0xDD34,
    0xB4F6,
    0xFB4C,
    0xCCD9,
    0xFFF2,
    0x8010,
    0x534F,
    0xFF36,
    0xFE54,
    0xFE73,
    0xFED7,
    0xFEF5,
    0xD706,
    0xEF19,
    0x8ED8,
    0xB354,
    0xE700,
    0xCE7F,
    0xE165,
    0x19D7,
    0x0532,
    0x308F,
    0xDC8B,
    0xF3F7,
    0x70E3,
    0xC986,
    0xF954,
    0xEAC0,
    0xCC27,
    0x8D56,
    0xD81F,
    0x0071,
    0x11A4,
    0x459D,
    0xC049,
    0xFEFC,
    0x03CD,
    0x51E1,
    0xFE19,
    0xD252,
    0xFBBF,
    0xFEFE,
    0xDD9A,
    0xFCCC,
    0xE579,
    0x9806,
    0xF474,
    0x962E,
    0x3890,
    0xE73C,
    0x8A30,
    0xDD1B,
    0x5A36,
    0x5D32,
    0x8311,
    0xBA6C,
    0xFAC6,
    0xB71C,
    0xFC39,
    0xF404,
    0x70E3,
    0x018A,
    0xD81F,
    0xCC53,
    0x7166,
    0x6202,
    0x3983,
    0xFBA3,
    0x8010,
    0x9818,
    0xA11E,
    0x69B3,
    0x93D6,
    0x4A90,
    0xFA7B,
    0x9A96,
    0x5209,
    0x9A75,
    0x5249,
    0x4352,
    0xEE7A,
    0xA534,
    0x89CB,
    0x5C55,
    0xF9AB,
    0x2104,
    0xFD4C,
    0xE04B,
    0x92ED,
    0xE293,
    0xB22D,
    0xD44B,
    0x8328,
    0xF999,
    0xE12D,
    0x8A70,
    0x6193,
    0xF800,
    0xE909,
    0xF007,
    0xC006,
    0xE947,
    0xE8E4,
    0xF922,
    0xA145,
    0x8002,
    0xFA89,
    0xE00F,
    0xF9C9,
    0xC0B0,
    0xA2CA,
    0x5170,
    0x0000,
    0x0110,
    0x73B2,
    0x0208,
    0x0042,
    0x0000,
    0xF53F,
    0xD008,
    0x0C9A,
    0xA359,
    0xB33A,
    0xB18C,
    0x4267,
    0x7208,
    0x0679,
    0x8BF0,
    0x8452,
    0xF80F,
    0xFA13,
    0x9AED,
    0x6248,
    0xB36F,
    0xE126,
    0xFB39,
    0xACD5,
    0xC0EA,
    0x92EB,
    0xAA6A,
    0x6001,
    0xD000,
    0xBC71,
    0x01D5,
    0x010C,
    0x435C,
    0xC972,
    0x7A95,
    0xFECB,
    0xCA2E,
    0xD00A,
    0xE08B,
    0x9883,
    0xF805,
    0xBB25,
    0xE472,
    0xA8E0,
    0x8223,
    0x648C,
    0x30A9,
    0xB201,
    0xD968,
    0x02A7,
    0x8A22,
    0xFBC0,
    0xFB20,
    0xEE80,
    0xF626,
    0xBDD1,
    0x214F,
    0xFC0E,
    0xFC94,
    0xC590,
    0x9382,
    0xEEA8,
    0xF52C,
    0xFED6,
    0x9382,
    0x9001,
    0x53E5,
    0x0A97,
    0x0334,
    0xFA30,
    0xCD06,
    0xF920,
    0xF866,
    0xFC95,
    0xFEC0,
    0x67EC,
    0x0352,
    0x9F17,
    0x2C4A,
    0x4E39,
    0x5921,
    0xFFBD,
    0xFDC0,
    0x7202,
    0x8BCB,
    0x7454,
    0xFE7E,
    0x04EC,
    0x8EA0,
    0xDC32,
    0x5D2F,
    0xF878,
    0xFB7F,
    0x8962,
    0xC618,
    0xAD75,
    0x5C57,
    0xC575,
    0xBE18,
    0xCA01,
    0xF9CA,
    0xFEC0,
    0x03AE,
    0x867D,
    0xCB95,
    0x6AD9,
    0x7412,
    0x0193,
    0x2CA2,
    0xFB67,
    0xCA10,
    0x740E,
    0x8141,
    0x1061,
    0x91E8,
    0xFFDF,
    0xCE5D,
    0x89C8,
    0x73AE,
    0x9882,
    0x194A,
    0x83A6,
    0x0397,
    0xD008,
    0xE0C9,
    0x9CD3,
    0x048A,
    0xEB00,
    0xF5F7,
    0xE004,
    0x07FF,
    0x4950,
    0x03EB,
    0x8AE9,
    0x0E1F,
    0xA7E0,
    0x87E5,
    0x07EF,
    0x03D7,
    0x4416,
    0xC999,
    0x5C51,
    0xFECB,
    0x9800,
    0x4B2D,
    0xE6CD,
    0xFAD1,
    0x926E,
    0xFA09,
    0xFE66,
    0xF78F,
    0xE54A,
    0xFEB4,
    0xFAEA,
    0xCB55,
    0xA9A6,
    0xD5B1,
    0xFA60,
    0xF420,
    0xFE60,
    0xE38F,
    0xFA68,
    0x49E6,
    0x8C31,
    0xD798,
    0xFC0F,
    0xF618,
    0x0410,
    0x33B1,
    0x9F36,
    0x040F,
    0xC9AE,
    0xCAA0,
    0xE38B,
    0xDDFB,
    0xDB74,
    0xFC55,
    0x0DD6,
    0xE467,
    0xDEBA,
    0xEF20,
    0xFB08,
    0x7378,
    0xFE4F,
    0xF866,
    0x8410,
    0x03AB,
    0xCD3B,
    0x0399,
    0x3C7B,
    0xFC31,
    0xDD51,
    0xB390,
    0x471A,
    0x07FD,
    0xA6B6,
    0x0639,
    0x8CCB,
    0xFEB4,
    0x6A66,
    0x7A49,
    0xA3CB,
    0xC4D3,
    0x8A4D,
    0x6007,
    0x0195,
    0xD809,
    0x8BD8,
    0x5352,
    0xFD80,
    0x3E8E,
    0x381F,
    0x433E,
    0xFB7F,
    0xFB70,
    0x6288,
    0xFEF9,
    0x5C9C,
    0xB424,
    0xFFEC,
    0x0224,
    0x7882,
    0xA905,
    0xE564,
    0x0273,
    0x9800,
    0xFE60,
    0xF3E0,
    0xD007,
    0x6205,
    0xF735,
    0xF475,
    0xC58B,
    0xC842,
    0x4595,
    0xE206,
    0xD9C3,
    0xA11E,
    0x75DF,
    0x633F,
    0x6750,
    0xFD8E,
    0xFEF7,
    0xFFF7,
    0x881F,
    0x781F,
    0x8015,
    0xEC1D,
    0x3256,
    0xF292,
    0x440D,
    0x04B3,
    0x7CFB,
    0xCCC0,
    0x9124,
    0x98E6,
    0xD8F0,
    0x055D,
    0xC806,
    0xFCC0,
    0xA6A1,
    0x0666,
    0xB87C,
    0xFAE0,
    0xFD00,
    0xC81F,
    0xF80D,
    0xF063,
    0xDB04,
    0x067F,
    0xF3A4,
    0xFD11,
    0xE304,
    0x981F,
    0xFF00,
    0xCFE0,
    0x3586,
    0x0208,
    0xA7BF,
    0x7CD5,
    0x62AA,
    0xF6F6,
    0xFFFF,
    0xF7BE,
    0xA57A,
    0xD394,
    0xFA14,
    0xFB70,
    0xFAC0,
    0xA2A0,
    0x7166,
    0x6188,
    0xF80F,
    0xA73F,
    0x544F,
    0xCD1B,
    0xC4CD,
    0x742F,
    0x0A72,
    0x1948,
    0xFFE0,
    0xFF50,
    0xEE60,
    0xFE80,
    0xFEE0,
    0xFF60,
    0xFFE6,
    0x9E66,
    0xFD68,
    0xFF80,
    0xFFA0,
    0x00B5,
    0x28A1,
    0x3D31
};

void init_lcd() {
    /* Enable extended memory interface with 10 bit addressing */
    XMCRB = _BV(XMM2) | _BV(XMM1);
    XMCRA = _BV(SRE);
    DDRC |= _BV(RESET);
    DDRB |= _BV(BLC);
    _delay_ms(1);
    PORTC &= ~_BV(RESET);
    _delay_ms(20);
    PORTC |= _BV(RESET);
    _delay_ms(120);
    write_cmd(DISPLAY_OFF);
    write_cmd(SLEEP_OUT);
    _delay_ms(60);
    write_cmd_data(INTERNAL_IC_SETTING,          0x01);
    write_cmd(POWER_CONTROL_1);
        write_data16(0x2608);
    write_cmd_data(POWER_CONTROL_2,              0x10);
    write_cmd(VCOM_CONTROL_1);
        write_data16(0x353E);
    write_cmd_data(VCOM_CONTROL_2, 0xB5);
    write_cmd_data(INTERFACE_CONTROL, 0x01);
        write_data16(0x0000);
    write_cmd_data(PIXEL_FORMAT_SET, 0x55);     /* 16bit/pixel */
    set_orientation(North);
    clear_screen();
    display.x = 0;
    display.y = 0;
    display.background = BLACK;
    display.foreground = WHITE;
    write_cmd(DISPLAY_ON);
    _delay_ms(50);
    write_cmd_data(TEARING_EFFECT_LINE_ON, 0x00);
    EICRB |= _BV(ISC61);
    PORTB |= _BV(BLC);
}

void lcd_brightness(uint8_t i) {
    /* Configure Timer 2 Fast PWM Mode 3 */
    TCCR2A = _BV(COM2A1) | _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS20);
    OCR2A = i;
}

void set_orientation(orientation o) {
    display.orient = o;
    write_cmd(MEMORY_ACCESS_CONTROL);
    if (o==North) { 
        display.width = LCDWIDTH;
        display.height = LCDHEIGHT;
        write_data(0x48);
    }
    else if (o==West) {
        display.width = LCDHEIGHT;
        display.height = LCDWIDTH;
        write_data(0xE8);
    }
    else if (o==South) {
        display.width = LCDWIDTH;
        display.height = LCDHEIGHT;
        write_data(0x88);
    }
    else if (o==East) {
        display.width = LCDHEIGHT;
        display.height = LCDWIDTH;
        write_data(0x28);
    }
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(0);
    write_data16(display.width-1);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(0);
    write_data16(display.height-1);
}

void set_frame_rate_hz(uint8_t f) {
    uint8_t diva, rtna, period;
    if (f>118)
        f = 118;
    if (f<8)
        f = 8;
    if (f>60) {
        diva = 0x00;
    } else if (f>30) {
        diva = 0x01;
    } else if (f>15) {
        diva = 0x02;
    } else {
        diva = 0x03;
    }
    /*   !!! FIXME !!!  [KPZ-30.01.2015] */
    /*   Check whether this works for diva > 0  */
    /*   See ILI9341 datasheet, page 155  */
    period = 1920.0/f;
    rtna = period >> diva;
    write_cmd(FRAME_CONTROL_IN_NORMAL_MODE);
    write_data(diva);
    write_data(rtna);
}

void fill_image_pgm(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *col) {
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(x);
    write_data16(x+width);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(y);
    write_data16(y+height);
    write_cmd(MEMORY_WRITE);
/*  uint16_t x, y;
    for(x=r.left; x<=r.right; x++)
        for(y=r.top; y<=r.bottom; y++)
            write_data16(col);
*/
    uint16_t wpixels = width + 1;
    uint16_t hpixels = height + 1;
    uint8_t mod8, div8;
    uint16_t odm8, odd8;
    if (hpixels > wpixels) {
        mod8 = hpixels & 0x07;
        div8 = hpixels >> 3;
        odm8 = wpixels*mod8;
        odd8 = wpixels*div8;
    } else {
        mod8 = wpixels & 0x07;
        div8 = wpixels >> 3;
        odm8 = hpixels*mod8;
        odd8 = hpixels*div8;
    }
    uint8_t pix1 = odm8 & 0x07;
    while(pix1--)
        write_data16(pgm_read_word(col++));

    uint16_t pix8 = odd8 + (odm8 >> 3);
    while(pix8--) {
        write_data16(pgm_read_word(col++));
        write_data16(pgm_read_word(col++));
        write_data16(pgm_read_word(col++));
        write_data16(pgm_read_word(col++));
        write_data16(pgm_read_word(col++));
        write_data16(pgm_read_word(col++));
        write_data16(pgm_read_word(col++));
        write_data16(pgm_read_word(col++));
    }
}

void fill_image_pgm_2b(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *col) {
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(x);
    write_data16(x+width-1);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(y);
    write_data16(y+height-1);
    write_cmd(MEMORY_WRITE);
/*  uint16_t x, y;
    for(x=r.left; x<=r.right; x++)
        for(y=r.top; y<=r.bottom; y++)
            write_data16(col);
*/
    uint16_t wpixels = width;
    uint16_t hpixels = height;
    uint8_t mod8, div8;
    uint16_t odm8, odd8;
    if (hpixels > wpixels) {
        mod8 = hpixels & 0x07;
        div8 = hpixels >> 3;
        odm8 = wpixels*mod8;
        odd8 = wpixels*div8;
    } else {
        mod8 = wpixels & 0x07;
        div8 = wpixels >> 3;
        odm8 = hpixels*mod8;
        odd8 = hpixels*div8;
    }
    uint8_t pix1 = odm8 & 0x07;
    while(pix1--) {
        write_data16(pgm_read_word(col));
        write_data16(pgm_read_word(col++));
    }
    uint16_t pix8 = odd8 + (odm8 >> 3);
    uint16_t temp;
    while(pix8--) {
        temp = pgm_read_word(col++);
        write_data16(temp);
        write_data16(temp);
        temp = pgm_read_word(col++);
        write_data16(temp);
        write_data16(temp);
        temp = pgm_read_word(col++);
        write_data16(temp);
        write_data16(temp);
        temp = pgm_read_word(col++);
        write_data16(temp);
        write_data16(temp);
    }
}

void fill_image(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t *col) {
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(x);
    write_data16(x+width);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(y);
    write_data16(y+height);
    write_cmd(MEMORY_WRITE);
/*  uint16_t x, y;
    for(x=r.left; x<=r.right; x++)
        for(y=r.top; y<=r.bottom; y++)
            write_data16(col);
*/
    uint16_t wpixels = width + 1;
    uint16_t hpixels = height + 1;
    uint8_t mod8, div8;
    uint16_t odm8, odd8;
    if (hpixels > wpixels) {
        mod8 = hpixels & 0x07;
        div8 = hpixels >> 3;
        odm8 = wpixels*mod8;
        odd8 = wpixels*div8;
    } else {
        mod8 = wpixels & 0x07;
        div8 = wpixels >> 3;
        odm8 = hpixels*mod8;
        odd8 = hpixels*div8;
    }
    uint8_t pix1 = odm8 & 0x07;
    while(pix1--)
        write_data16(*col++);

    uint16_t pix8 = odd8 + (odm8 >> 3);
    while(pix8--) {
        write_data16(*col++);
        write_data16(*col++);
        write_data16(*col++);
        write_data16(*col++);
        write_data16(*col++);
        write_data16(*col++);
        write_data16(*col++);
        write_data16(*col++);
    }
}

void fill_rectangle(rectangle r, uint16_t col) {
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(r.left);
    write_data16(r.right);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(r.top);
    write_data16(r.bottom);
    write_cmd(MEMORY_WRITE);
/*  uint16_t x, y;
    for(x=r.left; x<=r.right; x++)
        for(y=r.top; y<=r.bottom; y++)
            write_data16(col);
*/
    uint16_t wpixels = r.right - r.left + 1;
    uint16_t hpixels = r.bottom - r.top + 1;
    uint8_t mod8, div8;
    uint16_t odm8, odd8;
    if (hpixels > wpixels) {
        mod8 = hpixels & 0x07;
        div8 = hpixels >> 3;
        odm8 = wpixels*mod8;
        odd8 = wpixels*div8;
    } else {
        mod8 = wpixels & 0x07;
        div8 = wpixels >> 3;
        odm8 = hpixels*mod8;
        odd8 = hpixels*div8;
    }
    uint8_t pix1 = odm8 & 0x07;
    while(pix1--)
        write_data16(col);

    uint16_t pix8 = odd8 + (odm8 >> 3);
    while(pix8--) {
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
    }
}

void fill_rectangle_c(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t col) {
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(x);
    write_data16(x+width);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(y);
    write_data16(y+height);
    write_cmd(MEMORY_WRITE);
/*  uint16_t x, y;
    for(x=r.left; x<=r.right; x++)
        for(y=r.top; y<=r.bottom; y++)
            write_data16(col);
*/
    uint16_t wpixels = width + 1;
    uint16_t hpixels = height + 1;
    uint8_t mod8, div8;
    uint16_t odm8, odd8;
    if (hpixels > wpixels) {
        mod8 = hpixels & 0x07;
        div8 = hpixels >> 3;
        odm8 = wpixels*mod8;
        odd8 = wpixels*div8;
    } else {
        mod8 = wpixels & 0x07;
        div8 = wpixels >> 3;
        odm8 = hpixels*mod8;
        odd8 = hpixels*div8;
    }
    uint8_t pix1 = odm8 & 0x07;
    while(pix1--)
        write_data16(col);

    uint16_t pix8 = odd8 + (odm8 >> 3);
    while(pix8--) {
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
        write_data16(col);
    }
}

void fill_rectangle_indexed(rectangle r, uint16_t* col) {
    uint16_t x, y;
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(r.left);
    write_data16(r.right);
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(r.top);
    write_data16(r.bottom);
    write_cmd(MEMORY_WRITE);
    for(x=r.left; x<=r.right; x++)
        for(y=r.top; y<=r.bottom; y++)
            write_data16(*col++);
}


void clear_screen() {
    display.x = 0;
    display.y = 0;
    rectangle r = {0, display.width-1, 0, display.height-1};
    fill_rectangle(r, display.background);
}

void display_char_xy_col(char c, uint16_t x, uint16_t y, uint16_t fg, uint16_t bg) {
    display.x = x;
    display.y = y;
    display_char_col(c, fg, bg);
}

void display_char_col(char c, uint16_t fg, uint16_t bg) {
    uint16_t x, y;
    PGM_P fdata; 
    uint8_t bits, mask;
    uint16_t sc=display.x, ec=display.x + 4, sp=display.y, ep=display.y + 7;

    /*   New line starts a new line, or if the end of the
         display has been reached, clears the display.
    */
    if (c == '\n') { 
        display.x=0; display.y+=8;
        if (display.y >= display.height) { clear_screen(); }
        return;
    }

    if (c < 32 || c > 126) return;
    fdata = (c - ' ')*5 + font5x7;
    write_cmd(PAGE_ADDRESS_SET);
    write_data16(sp);
    write_data16(ep);
    for(x=sc; x<=ec; x++) {
        write_cmd(COLUMN_ADDRESS_SET);
        write_data16(x);
        write_data16(x);
        write_cmd(MEMORY_WRITE);
        bits = pgm_read_byte(fdata++);
        for(y=sp, mask=0x01; y<=ep; y++, mask<<=1)
            write_data16((bits & mask) ? fg : bg);
    }
    write_cmd(COLUMN_ADDRESS_SET);
    write_data16(x);
    write_data16(x);
    write_cmd(MEMORY_WRITE);
    for(y=sp; y<=ep; y++)
        write_data16(bg);

    display.x += 6;
    if (display.x >= display.width) { display.x=0; display.y+=8; }
}

void display_char(char c) {
    display_char_col(c, display.foreground, display.background);
}

void display_string_col(char *str, uint16_t col) {
    uint8_t i;
    for(i=0; str[i]; i++) 
        display_char_col(str[i], col, display.background);
}

void display_string(char *str) {
    display_string_col(str, display.foreground);
}

void display_string_xy_col(char *str, uint16_t x, uint16_t y, uint16_t col) {
    uint8_t i;
    display.x = x;
    display.y = y;
    for(i=0; str[i]; i++)
        display_char_col(str[i], col, display.background);
}

void display_string_xy(char *str, uint16_t x, uint16_t y) {
    display_string_xy_col(str, x, y, display.foreground);
}

void display_register(uint8_t reg) {
	uint8_t i;

	for(i = 0; i < 8; i++) {
		if((reg & (_BV(7) >> i)) != 0) {
			display_char( '1' );
		} else {
			display_char( '.' );
		}
	}
}

static inline uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

char* itoa(uint8_t i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    uint8_t shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

char* longtoa(uint32_t i, char b[]) {
    char const digit[] = "0123456789";
    char* p = b;
    uint32_t shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

char* shorttoa(uint16_t i, char b[]) {
    char const digit[] = "0123456789";
    char* p = b;
    uint16_t shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

void display_uint8(uint8_t i) {
    char b [3];
    display_string(itoa(i, b));
}

void display_uint32(uint32_t i) {
    char b [10];
    display_string(longtoa(i, b));
}

void display_uint16(uint16_t i) {
    char b [7];
    display_string(shorttoa(i, b));    
}

void display_uint16_xy_col(uint16_t i, uint16_t x, uint16_t y, uint16_t col) {
    char b [7];
    display_string_xy_col(shorttoa(i, b), x, y, col);
}

void display_uint16_xy(uint16_t i, uint16_t x, uint16_t y) {
    char b [7];
    display_string_xy(shorttoa(i, b), x, y);
}

void display_uint16_col(uint16_t i, uint16_t col) {
    char b [7];
    display_string_col(shorttoa(i, b), col);
}

void display_uint8_xy_col(uint8_t i, uint16_t x, uint16_t y, uint16_t col) {
    char b [3];
    display_string_xy_col(itoa(i, b), x, y, col);
}
