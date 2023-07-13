//
// Created by bol on 2023/6/30.
//

#ifndef DUNGEONRUSH2_UTIL_H
#define DUNGEONRUSH2_UTIL_H


int str_isblank(const char *str);

char *str_trim(char *str);

char **str_split(char *str, char delimiter);

char *str_concat(char dest[], ...);

#endif //DUNGEONRUSH2_UTIL_H
