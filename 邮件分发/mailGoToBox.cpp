#include"mailGoToBox.h"
/******************************
 *
 * 判断是否拒收邮件（发件人在收件人黑名单中）
 * @param filename只穿入文件名自己可，函数中会补齐路径,并修改邮件状态为是否发送成功
 * @return 0 可投递状态
 *         -1 文件打开失败
 *         -2  不可投递，被拒收
 */
int sfRecieve(char* filename){//由此函数判断是否接受此邮件
    char fileCompleteName[50];
    memset(fileCompleteName,0,50);
    strcpy(fileCompleteName,"server/TemporaryStorage/");
    strcat(fileCompleteName,filename);
    MAILHEAD  temphead;
    MAILBODY  tempbody;
    struct blacklist temp1;
    FILE* fp;
    fp=fopen(fileCompleteName,"r");
    if(fp==NULL)
        return -1;
    fread(&temphead,sizeof(MAILHEAD),1,fp);
    fread(&tempbody,sizeof(MAILBODY),1,fp);
    fclose(fp);
    char targetIdBlackList[25]; //目标邮箱号
    memset(targetIdBlackList,0,25);
    strcat(targetIdBlackList,"server/");
    strcat(targetIdBlackList,temphead.targetID);
    strcat(targetIdBlackList,"/blackList.txt");
    FILE* fp1;
    fp1=fopen(targetIdBlackList,"r");
    if(fp==NULL)
        return -1;
    for(int i=0;i<=getBlackListNum()-1;i++){
        fread(&temp1,sizeof(struct blacklist),1,fp1);
        if(strcmp(temp1.ID,temphead.originID)==0){
            temp.sendstate=2;
            FILE* fp1;
            fp1=fopen(fileCompleteName,"w+");
            if(fp1==NULL)
                return -1;
            fwrite(&temp,sizeof(MAILHEAD),1,fp1);
            fwrite(&tempbody,sizeof(MAILBODY),1,fp1);
            fclose(fp);
            return -2;
        }
    }
    fclose(fp1);
    temp.sendstate=1;
    FILE* fp1;
    fp1=fopen(fileCompleteName,"w+");
    if(fp1==NULL)
        return -1;
    fwrite(&temp,sizeof(MAILHEAD),1,fp1);
    fwrite(&tempbody,sizeof(MAILBODY),1,fp1);
    fclose(fp);
    return 0;
}
/**************************
 * 投递函数，负责将邮件投递到目标邮箱或退回到个人邮箱,将邮件头存入邮件列表中
 * @param filename 邮件名字
 * @param state  0为正常投递，1为拒收撤回
 * @return -1 打开文件错误
 *         0 投递成功
 */
int throwMail(char* filename,int state){
    char fileCompleteName[50];
    memset(fileCompleteName,0,50);
    strcpy(fileCompleteName,"server/TemporaryStorage/");
    strcat(fileCompleteName,filename);
    MAILHEAD  temp;
    FILE* fp;
    fp=fopen(fileCompleteName,"r");
    if(fp==NULL)
        return -1;
    fread(&temp,sizeof(MAILHEAD),1,fp);
    fclose(fp);
    char targetDir[50];
    memset(targetDir,0,50);
    strcpy(targetDir,"server/");
    if(state==0)
        strcat(targetDir, temp.targetID);
    else
        strcat(targetDir,temp.originID);
    strcat(targetDir,"/mailBox/");
    char listAdress[50];
    strcpy(listAdress,"list.txt");
    strcat(targetDir,filename);
    rename(fileCompleteName, targetDir);
    FILE* fp;
    fp=fopen(listAdress,"a+");
    if(fp==NULL)
        return -1;
    fwrite(&temp,sizeof(MAILHEAD),1,fp);
    fclose(fp);
    return 0;
}
