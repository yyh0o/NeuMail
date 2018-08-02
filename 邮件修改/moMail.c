#include "moMail.h"
#include "Initialization.h"
#include "mailGoToBox.h"
int getMailNumber(char *ID){
    char completeName[50];
    memset(completeName,0,50);
    strcpy(completeName,"server/");
    strcat(completeName,ID);
    strcat(completeName,"/mailBox/mailNumber.txt");
    int number=0;
    FILE* fp;
    if(fp==NULL){
        return -1;
    }
    fp=fopen(completeName,"r");
    fread(&number,sizeof(int),1,fp);
    fclose(fp);
    return number;
}
int setMailNumber(char *ID){
    char completeName[50];
    memset(completeName,0,50);
    strcpy(completeName,"server/");
    strcat(completeName,ID);
    strcat(completeName,"/mailBox/mailNumber.txt");
    int number=0;
    FILE* fp;
    if(fp==NULL){
        return -1;
    }
    fp=fopen(completeName,"r");
    fread(&number,sizeof(int),1,fp);
    fclose(fp);
    number--;
    FILE* fp1;
    if(fp1==NULL){
        return -1;
    }
    fp1=fopen(completeName,"w+");
    fwrite(&number,sizeof(int),1,fp1);
    fclose(fp);
    return 0;
}
/***********************************
 * 删掉邮件，修改邮件列表
 * @param filename 邮件主题
 * @param ID 用户
 * @return 0 成功
 *        -1  文件打开失败
 *        -2 删除失败
 */
int delMail(char * filename,char *ID){
    char completeName[50];
    char fileName[50];
    memset(completeName,0,50);
    strcpy(completeName,"server/");
    strcat(completeName,ID);
    strcpy(fileName,completeName);
    strcat(completeName,"/mailBox/list.txt");
    strcat(fileName,"/mailBox/");
    strcat(fileName,filename);
    strcat(fileName,".txt");

    MAILHEAD temp[100];
    memset(temp,0,100*sizeof(MAILHEAD));
    int number=0;
    FILE* fp;
    fp=fopen(completeName,"r");
    for(int i=0;i<=getMailNumber(ID)-1;i++){
        fread(&temp[i],sizeof(MAILHEAD),1,fp);
        if(strcmp(temp[i].title,ID)==0){
            i--;
        }

    }
    fclose(fp);
    FILE* fp1;
    fp1=fopen(completeName,"w+");
    setMailNumber(ID);
    fwrite(temp,sizeof(MAILHEAD),getMailNumber(ID),fp1);
    fclose(fp1);
    int state=remove( fileName);
    if(state==-1)
        return -2;
    return 0;
}
int starMail(char* filename,char* ID){
    char completeName[50];
    memset(completeName,0,50);
    strcpy(completeName,"server/");
    strcat(completeName,ID);
    strcat(completeName,"/mailBox/");
    strcat(completeName, filename);
    strcat(completeName, ".txt");
    FILE* fp;
    fp = fopen(completeName, "r");
    if(fp == NULL){
        return -1;
    }
    MAILHEAD head;
    MAILBODY body;
    fread(&head, sizeof(MAILHEAD), 1, fp);
    fread(&body, sizeof(MAILBODY), 1, fp);
    fclose(fp);
    head.state =0;
    FILE* fp1;
    fp1 = fopen(completeName, "w+");
    fwrite(&head, sizeof(MAILHEAD), 1, fp1);
    fwrite(&body, sizeof(MAILBODY), 1, fp1);
    fclose(fp1);
    int number;
    number = getMailNumber(ID);
    char completeName1[50];
    memset(completeName1,0,50);
    strcpy(completeName1,"server/");
    strcat(completeName1,ID);
    strcat(completeName1,"/mailBox/");
    strcat(completeName1, "list.txt");
    FILE* fp2;
    fp2 = fopen(completeName1, "r");
    if(fp2 == NULL){
        return -1;
    }
    MAILHEAD head1[100];
    fread(head1, sizeof(MAILHEAD),number, fp2);
    fclose(fp2);
    for(int i=0;i<number;i++)
        if(strcmp(head1[i].title, filename)== 0){
            head1[i].state = 0;
        }
    FILE* fp4;
    fp4 = fopen(completeName1, "w+");
    if(fp4 == NULL){
        return -1;
    }
    fwrite(head1, sizeof(MAILHEAD), number, fp4);
    fclose(fp4);
    return 0;
}

