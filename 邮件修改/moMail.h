//
// Created by nsu on 18-7-31.
//

#ifndef UNTITLED1_STARMAIL_H
#define UNTITLED1_STARMAIL_H
#include <stdio.h>
#include<string.h>
typedef struct {
    char targetID[25]; //目标邮箱号
    char originID[25]; //发件人邮箱号
    struct DATE{// 发送时间
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
    };
    char title[50]; //邮件主题
    int state;// 0收藏,1已读，2未读
    int sendstate;//发送状态，成功为1，被拒收2
}MAILHEAD;
typedef struct {
    char content[500];//保存用户击键内容
    int appendixState;//有无附件，有则为1，无为0
    char appendixName[50];

}MAILBODY;
int getMailNumber(char *ID);
int setMailNumber(char *ID);
int delMail(char * filename,char *ID);
int starMail(char* filename,char* ID);
#endif //UNTITLED1_STARMAIL_H
