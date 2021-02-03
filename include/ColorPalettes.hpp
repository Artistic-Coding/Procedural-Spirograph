//
// Created by tipo on 12/24/20.
//
#ifndef PROCEDURAL_SPIROGRAPH_COLORPALETTES_HPP
#define PROCEDURAL_SPIROGRAPH_COLORPALETTES_HPP

using ColorPalette = std::vector<int>;
using ColorPalettes = std::vector<ColorPalette>;

ColorPalette oldNavy{0xe63946, 0xf1faee, 0xa8dadc, 0x457b9d, 0x1d3557};
ColorPalette summerForest{0x264653, 0x2a9d8f, 0xe9c46a, 0xf4a261, 0xe76f51};
ColorPalette fancy{0x000000, 0x14213d, 0xfca311, 0xe5e5e5, 0xffffff};
ColorPalette corpo{0x222831, 0x393e46, 0x00adb5, 0xeeeeee};
ColorPalette candy{0xa8d8ea, 0xaa96da, 0xfcbad3, 0xffffd2};
ColorPalette nighEnd{0x2b2e4a, 0xe84545, 0x903749, 0x53354a};
ColorPalette skinContrast{0x355070, 0x6d597a, 0xb56576, 0xe56b6f, 0xeaac8b};
ColorPalette comfort{0xEEEDE7, 0x868B8E, 0xB9B7BD, 0xE7D2CC};
ColorPalette purpleHaze{0xdefcf9, 0xcadefc, 0xc3bef0, 0xcca8e9};
ColorPalette mrPig{0xffc8c8, 0xff9999, 0x444f5a, 0x3e4149};
ColorPalette cottonCandy{0xa1eafb, 0xfdfdfd, 0xffcef3, 0xcabbe9};
ColorPalette sunDown{0x0c056d, 0x590d82, 0xb61aae, 0xf25d9c};
ColorPalette turmoil{0x283d3b, 0x197278, 0xedddd4, 0xc44536, 0x772e25};
ColorPalette primals{0x50514f, 0x50514f, 0xffe066, 0x247ba0, 0x70c1b3};
ColorPalette polo{0x111f4d, 0xf2f4f7, 0xe43a19, 0x020205};
ColorPalette blueSky{0xc7ffff, 0xfbeeff, 0xebc6ff, 0x7e80ff};
ColorPalette bloodMoon{0xff006c, 0xd62b70, 0x973961, 0x623448};

ColorPalettes palettes{oldNavy, summerForest, fancy, corpo, candy, nighEnd,
                       skinContrast, comfort, purpleHaze, mrPig, cottonCandy,
                       sunDown, turmoil, primals, polo, blueSky, bloodMoon};

#endif //PROCEDURAL_SPIROGRAPH_COLORPALETTES_HPP
