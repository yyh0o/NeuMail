//
//  main.c
//  PrintMailLists
//
//  Created by 周彦錞 on 2018/8/2.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#include <stdio.h>
struct MAILHEAD{
    char targetID[25];
    char originID[25];
    char data[30];
    char title[50];
    int state;
    int sendstate;
};

int PrintMailingLists(void){
    int number;
    FILE* fp1;
    fp1 =fopen("client/mailBox/mailNumber.txt", "r");
    if(fp1 == NULL){
        return -1;
    }
    fread(&number, sizeof(int), 1, fp1);
    fclose(fp1);
    struct MAILHEAD head[100];
    FILE* fp;
    fp = fopen("client/mailBox/list.txt", "r");
    fread(head, sizeof(struct MAILHEAD), number, fp);
    fclose(fp);
    for(int i=0;i<number;i++){
        printf("TargetID: %s\n",head[i].targetID);
        printf("OriginID: %s\n",head[i].originID);
        printf("Data: %s\n",head[i].data);
        printf("Title: %s\n",head[i].title);
    }
}

