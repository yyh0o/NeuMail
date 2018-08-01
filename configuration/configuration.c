//
//  main.c
//  Project
//
//  Created by 周彦錞 on 2018/7/29.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#define PEIZHIWENJIAN "client/configurationFiles.txt"
struct configurationFile{
    char userId[12];
    char serverIp[30];
    char port[10];
};//配置资料

int configuration(char* userID,char* serverIP,char* serverPort);
/********************
 配置文件写入
 函数返回整型值 int
 传入字符指针 char* userID,char* serverIP,char* serverPort
 创建了一个TXT文件保存配置
 *********************/
int configuration(char* userID,char* serverIP,char* serverPort){
    FILE* fp;
    fp = fopen("/Users/kevin/Desktop/小学期/packaging/packaging/configuration.txt","w+");//创建并读写文件
    if(fp == NULL){
        return -1;
    }
    struct configurationFile config={0};
    fread(&config,sizeof(struct configurationFile),1,fp);//读取文件
    strcpy(config.userId, userID);
    strcpy(config.serverIp, serverIP);
    strcpy(config.port, serverPort);
    fwrite(&config, sizeof(struct configurationFile), 1, fp);//写入文件
    fclose(fp);
    return 0;
}

int main(void){
    configuration("1212","1212","121212");
    FILE* fp;
    fp=fopen("/Users/kevin/Desktop/小学期/packaging/packaging/configuration.txt", "r");
    if(fp == NULL){
        return -1;
    }
    struct configurationFile config={0};
    fread(&config, sizeof(struct configurationFile), 1, fp);
    printf("%s\n",config.userId);
    printf("%s\n",config.serverIp);
    printf("%s\n",config.port);
    fclose(fp);
    return 0;
}
