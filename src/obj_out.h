//
// Created by KaiyuanLiu on 2019-06-24.
//

#ifndef GRAPHICS_OBJ_OUT_H
#define GRAPHICS_OBJ_OUT_H
#include <fstream>
void saveOBJ(const char *filename){
    std::ofstream handle(filename);
    char obj[] = "o Cube\n"
                "v 1.000000 -1.000000 -1.000000\n"
                "v 1.000000 -1.000000 1.000000\n"
                "v -1.000000 -1.000000 1.000000\n"
                "v -1.000000 -1.000000 -1.000000\n"
                "v 1.000000 1.000000 -1.000000\n"
                "v 0.999999 1.000000 1.000001\n"
                "v -1.000000 1.000000 1.000000\n"
                "v -1.000000 1.000000 -1.000000\n"
                "usemtl Material\n"
                "s off\n"
                "f 5 1 4\n"
                "f 5 4 8\n"
                "f 3 7 8\n"
                "f 3 8 4\n"
                "f 2 6 3\n"
                "f 6 7 3\n"
                "f 1 5 2\n"
                "f 5 6 2\n"
                "f 5 8 6\n"
                "f 8 7 6\n"
                "f 1 2 3\n"
                "f 1 3 4\n";
    handle.write(obj, sizeof(obj) - 1);
    handle.close();
}
#endif //GRAPHICS_OBJ_OUT_H
