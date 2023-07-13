//
// Created by bol on 2023/6/29.
//
#include "i18n.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const char PATH_TEXT_KEY[] = "res/conf/text_key.txt";
const char PATH_LANGUAGE_CONF[] = "res/conf/language_conf.txt";

LangConf *CURRENT_LANG_CONF = NULL;

LangConf LANG_CONF_ARRAY[5];
int LANG_CONF_NUM = 0;

LangItem LANG_ITEM_ARRAY[30];
int LANG_ITEM_NUM = 0;


// TODO 优化匹配效率
char *transText(char *key) {
    char *value = NULL;
    for (int i = 0; i < LANG_ITEM_NUM; ++i) {
        if (strcmp(LANG_ITEM_ARRAY[i].key, key) == 0) {
            value = LANG_ITEM_ARRAY[i].value;
            break;
        }
    }
    return value;
}

void I18N_Init() {
    loadLangConf();
    loadLangText();
}

void I18N_ChangeLang(char *show) {
    for (int i = 0; i < LANG_CONF_NUM; ++i) {
        LangConf *temp = &(LANG_CONF_ARRAY[i]);
        if (strcmp(show, temp->show) == 0) {
            CURRENT_LANG_CONF = temp;
            freeLangText();
            loadLangText();
            return;
        }
    }

    printf("change language dont exist: %s \n", show);
}

void loadLangConf() {
    FILE *confFile = fopen(PATH_LANGUAGE_CONF, "r");
    char buf[100];
    while (fgets(buf, sizeof(buf), confFile) != NULL) {
        if (str_isblank(buf)) {
            memset(buf, 0, sizeof(buf));
            continue;
        }

        char **kv = str_split(buf, '=');
        char **keyItem = str_split(kv[0], '.');
        saveConfItem(str_trim(keyItem[0]), str_trim(keyItem[1]), str_trim(kv[1]));
        free(kv);
        free(keyItem);
        memset(buf, 0, sizeof(buf));
    }
    fclose(confFile);

    // 将语言配置文件中的第一项设为默认语言
    if (LANG_CONF_NUM > 0) {
        CURRENT_LANG_CONF = &(LANG_CONF_ARRAY[0]);
    }
}

void saveConfItem(char *key, char *item, char *value) {
    LangConf *langConf = NULL;
    if (LANG_CONF_NUM > 0) {
        for (int i = 0; i < LANG_CONF_NUM; i++) {
            if (strcmp(LANG_CONF_ARRAY[i].key, key) == 0) {
                langConf = &(LANG_CONF_ARRAY[i]);
                break;
            }
        }
    }
    if (langConf == NULL) {
        LANG_CONF_NUM++;
        LangConf temp = {};
        LANG_CONF_ARRAY[LANG_CONF_NUM - 1] = temp;
        langConf = &(LANG_CONF_ARRAY[LANG_CONF_NUM - 1]);

        strcpy(langConf->key, key);
    }

    if (strcmp(item, "show") == 0) {
        strcpy(langConf->show, value);
    } else if (strcmp(item, "size") == 0) {
        langConf->size = atoi(value);
    } else if (strcmp(item, "font") == 0) {
        strcpy(langConf->font, value);
    } else {
        printf("error language conf key: %s", key);
    }
}

void loadLangText() {
    char path[20] = "res/i18n/";
    strcat(path, CURRENT_LANG_CONF->key);
    strcat(path, ".txt");

    FILE *langFile = fopen(path, "r");
    char buf[100];
    while (fgets(buf, sizeof(buf), langFile) != NULL) {
        if (str_isblank(buf)) {
            memset(buf, 0, sizeof(buf));
            continue;
        }

        char **kv = str_split(buf, '=');
        saveLangText(str_trim(kv[0]), str_trim(kv[1]));
        free(kv);

        memset(buf, 0, sizeof(buf));
    }

    fclose(langFile);
}

void saveLangText(char *key, char *value) {
    LangItem item;
    item.key = malloc(strlen(key) + 1);
    item.value = malloc(strlen(value) + 1);
    strcpy(item.key, key);
    strcpy(item.value, value);

    LANG_ITEM_NUM++;
    LANG_ITEM_ARRAY[LANG_ITEM_NUM - 1] = item;
}

void freeLangText() {
    for (int i = 0; i < LANG_ITEM_NUM; ++i) {
        LangItem *temp = &(LANG_ITEM_ARRAY[i]);
        free(temp->key);
        free(temp->value);
    }
    LANG_ITEM_NUM = 0;
}
