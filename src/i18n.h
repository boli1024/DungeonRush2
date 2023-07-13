//
// Created by bol on 2023/6/29.
//

#ifndef DUNGEONRUSH2_I18N_H
#define DUNGEONRUSH2_I18N_H

// define all text key
#define TK_GAME_NAME "game_name"
#define TK_AUTHOR "author"
#define TK_PLAYER1 "player_1"
#define TK_PLAYER2 "player_1"
#define TK_SINGLE_PLAYER "single_player"
#define TK_MULTI_PLAYERS "multi_players"
#define TK_RANK_LIST "rank_list"
#define TK_EXIT "exit"
#define TK_LEVEL_NORMAL "level_normal"
#define TK_LEVEL_HARD "level_hard"
#define TK_LEVEL_INSANE "level_insane"
#define TK_MULTI_LOCAL "multi_local"
#define TK_MULTI_LAN "multi_lan"
#define TK_HOST_GAME "host_game"
#define TK_JOIN_GAME "join_game"
#define TK_PLACEHOLDER "PLACEHOLDER"
#define TK_LANGUAGE "language"

typedef struct {
    char key[10];
    char show[20];
    int size;
    char font[30];
} LangConf;

typedef struct {
    char *key;
    char *value;
} LangItem;

extern LangConf *CURRENT_LANG_CONF;
extern LangConf LANG_CONF_ARRAY[];
extern int LANG_CONF_NUM;
extern LangItem LANG_ITEM_ARRAY[30];
extern int LANG_ITEM_NUM;


char *transText(char *key);

void I18N_Init();

void I18N_ChangeLang(char *show);

void loadLangConf();

void saveConfItem(char *key, char *item, char *value);

void loadLangText();

void saveLangText(char *key, char *value);

void freeLangText();

#endif //DUNGEONRUSH2_I18N_H
