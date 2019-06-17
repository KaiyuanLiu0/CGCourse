//
// Created by KaiyuanLiu on 2019-06-15.
//

#ifndef GRAPHICS_MAP_H
#define GRAPHICS_MAP_H
#include "type.h"
#define MAP_HEIGHT 9
#define MAP_WIDTH 8
enum LEVEL {
    LEVEL1,
    LEVEL2,
    NUMOFLEVEL
};

class Map {
public:
    Map();
    Map(LEVEL level);
    void SetLevel(LEVEL level);
    TYPE GetType(int row, int col);
private:
    const TYPE map[NUMOFLEVEL][MAP_HEIGHT][MAP_WIDTH] = {
            {{PLAIN, PLAIN, WALL,    WALL,  WALL,  WALL,  WALL,  PLAIN}, // LEVEL 1 MAP
             {WALL,  WALL,  WALL,    PLAIN, PLAIN, PLAIN, WALL,  PLAIN},
             {WALL,  END,   PLAIN,   PLAIN, PLAIN, PLAIN, WALL,  PLAIN},
             {WALL,  WALL,  WALL,    PLAIN, PLAIN, END,   WALL,  PLAIN},
             {WALL,  END,   WALL,    WALL,  PLAIN, PLAIN, WALL,  PLAIN},
             {WALL,  PLAIN, WALL,    END,   PLAIN, PLAIN, WALL,  WALL },
             {WALL,  PLAIN, END,     PLAIN, PLAIN, PLAIN, END,   WALL },
             {WALL,  PLAIN, PLAIN,   PLAIN, END,   PLAIN, PLAIN, WALL },
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL }},

            {{WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL}, // LEVEL 2 MAP NOT FILLED
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,  WALL,    WALL,  WALL,  WALL,  WALL,  WALL }}
    };
    const TYPE base[MAP_HEIGHT][MAP_WIDTH] = {
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL}, // LEVEL 2 MAP NOT FILLED
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL},
             {WALL,  WALL,   WALL,   WALL,  WALL,  WALL,  WALL,  WALL }
    };
    const TYPE boxmap[NUMOFLEVEL][MAP_HEIGHT][MAP_WIDTH] = {
            {{PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN}, // LEVEL 1 BOX MAP
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  BOX,   PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, BOX,   PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, BOX,   PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, BOX,    PLAIN,  BOX,   BOX,   BOX,   PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN}},

            {{PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN},
             {PLAIN, PLAIN,  PLAIN,  PLAIN, PLAIN, PLAIN, PLAIN, PLAIN}}

    };
    int m_level_;
};


#endif //GRAPHICS_MAP_H
