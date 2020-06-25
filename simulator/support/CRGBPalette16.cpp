#include "CRGBPalette16.h"
//#include <QtCore/QDebug>

CRGBPalette16::CRGBPalette16( const CRGB& c1)
{
    fill_solid( &(entries[0]), 16, c1);
}

CRGBPalette16::CRGBPalette16( const CRGB& c1, const CRGB& c2)
{
    fill_gradient_RGB( &(entries[0]), 16, c1, c2);
}

CRGBPalette16::CRGBPalette16( const CRGB& c1, const CRGB& c2, const CRGB& c3)
{
    fill_gradient_RGB( &(entries[0]), 16, c1, c2, c3);
}

CRGBPalette16::CRGBPalette16( const CRGB& c1, const CRGB& c2, const CRGB& c3, const CRGB& c4)
{
    fill_gradient_RGB( &(entries[0]), 16, c1, c2, c3, c4);
}

CRGB ColorFromPalette( const CRGBPalette16& pal, uint8_t index, uint8_t brightness, TBlendType blendType)
{
    uint8_t hi4 = index >> 4;
//    uint8_t hi4 = lsrX4(index);
    uint8_t lo4 = index & 0x0F;

    // const CRGB* entry = &(pal[0]) + hi4;
    // since hi4 is always 0..15, hi4 * sizeof(CRGB) can be a single-byte value,
    // instead of the two byte 'int' that avr-gcc defaults to.
    // So, we multiply hi4 X sizeof(CRGB), giving hi4XsizeofCRGB;
    uint8_t hi4XsizeofCRGB = hi4 * sizeof(CRGB);
    // We then add that to a base array pointer.
    const CRGB* entry = (CRGB*)( (uint8_t*)(&(pal[0])) + hi4XsizeofCRGB);

    uint8_t blend = lo4 && (blendType != NOBLEND);

    uint8_t red1   = entry->r;
    uint8_t green1 = entry->g;
    uint8_t blue1  = entry->b;

    if( blend ) {

        if( hi4 == 15 ) {
            entry = &(pal[0]);
        } else {
            entry++;
        }

        uint8_t f2 = lo4 << 4;
        uint8_t f1 = 255 - f2;

        // -----
        CRGB rgb1(red1, green1, blue1);
//        qDebug() << "ColorFromPalette, rgb1" << index << red1 << green1 << blue1;
        rgb1.nscale8(f1);

        CRGB rgb2(entry->r, entry->g, entry->b);
//        qDebug() << "ColorFromPalette, rgb2" << index << entry->r << entry->g << entry->b;
        rgb2.nscale8(f2);

        rgb1 += rgb2;
        red1 = rgb1.r;
        green1 = rgb1.g;
        blue1 = rgb1.b;

        // -----

//        uint8_t red2   = entry->red;
//        red1   = scale8_LEAVING_R1_DIRTY( red1,   f1);
//        red2   = scale8_LEAVING_R1_DIRTY( red2,   f2);
//        red1   += red2;
//
//        uint8_t green2 = entry->green;
//        green1 = scale8_LEAVING_R1_DIRTY( green1, f1);
//        green2 = scale8_LEAVING_R1_DIRTY( green2, f2);
//        green1 += green2;
//
//        uint8_t blue2  = entry->blue;
//        blue1  = scale8_LEAVING_R1_DIRTY( blue1,  f1);
//        blue2  = scale8_LEAVING_R1_DIRTY( blue2,  f2);
//        blue1  += blue2;
//
//        cleanup_R1();
    }

    /*
    if( brightness != 255) {
        if( brightness ) {
            brightness++; // adjust for rounding
            // Now, since brightness is nonzero, we don't need the full scale8_video logic;
            // we can just to scale8 and then add one (unless scale8 fixed) to all nonzero inputs.
            if( red1 )   {
                red1 = scale8_LEAVING_R1_DIRTY( red1, brightness);
#if !(FASTLED_SCALE8_FIXED==1)
                red1++;
#endif
            }
            if( green1 ) {
                green1 = scale8_LEAVING_R1_DIRTY( green1, brightness);
#if !(FASTLED_SCALE8_FIXED==1)
                green1++;
#endif
            }
            if( blue1 )  {
                blue1 = scale8_LEAVING_R1_DIRTY( blue1, brightness);
#if !(FASTLED_SCALE8_FIXED==1)
                blue1++;
#endif
            }
            cleanup_R1();
        } else {
            red1 = 0;
            green1 = 0;
            blue1 = 0;
        }
    }
    */

//    qDebug() << "ColorFromPalette" << index << red1 << green1 << blue1;
    return CRGB( red1, green1, blue1);
}
