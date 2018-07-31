//
//  main.c
//  Project
//
//  Created by 周彦錞 on 2018/7/29.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#include <stdio.h>
#define PEIZHIWENJIAN "client/configurationFiles.txt"

int configuration(char* userID,char* serverIP,char* serverPort);
/********************
 配置文件写入
函数返回整型值 int
 传入字符指针 char* userID,char* serverIP,char* serverPort
 创建了一个TXT文件保存配置
 *********************/
struct configurationFile{
    char* userId;
    char* serverIp;
    char* port;
};//配置资料

int configuration(char* userID,char* serverIP,char* serverPort){
    FILE* fp;
    fp = fopen(PEIZHIWENJIAN,"w+");//创建并读写文件
    if(fp == NULL){
        return -1;
    }
    struct configurationFile config;
    fread(&config,sizeof(config),1,fp);//读取文件
    config.userId = userID;
    config.serverIp = serverIP;
    config.port = serverPort;
    fwrite(&config, sizeof(config), 1, fp);//写入文件
    fclose(fp);
    return 0;
}

