#include"client.h"
 /*********************************************
客户端函数第一次运行时的初始化函数，负责建立用户邮箱
返回值：-2 创建目录失败
        0 成功
        -1 打开文件失败
 **************************************************/
int clientInitiallization() {
    int state = 0;
    state = mkdir("client", 0777);//建立客户端根目录
    if (state < 0)
        return -2;
    int number=0;

   

    FILE *fp1;
    fp1 = fopen(BLACKLIST, "w+");//建立黑名单文件
    if (fp1==NULL)
        return -1;
    fclose(fp1);

     FILE *fp2;
     fp2 = fopen(BLACKLISTNUM, "w+");//建立黑名单人数文件
     if (fp1==NULL)
         return -1;
     fwrite(&number,sizeof(int),1,fp2);
     fclose(fp2);

     FILE *fp3;
     fp3 = fopen(PEIZHIWENJIAN, "w+");//建立用户个数文件
     if (fp3==NULL)
         return -1;
     fclose(fp3);

     FILE *fp4;
     fp4 = fopen(CONTACTLIST, "w+");//建立联系人文件
     if (fp4==NULL)
         return -1;
     fclose(fp4);

     FILE *fp5;
     fp5 = fopen(CONTACTLISTNUM, "w+");//建立联系人个数文件
     if (fp5==NULL)
         return -1;
     fwrite(&number,sizeof(int),1,fp5);
     fclose(fp5);
     state = mkdir("client/TemporaryStorage", 0777);
    if (state < 0)
        return -2;
     state = mkdir("client/mailBox", 0777);
     if (state < 0)
         return -2;
     FILE *fp6;
     fp6 = fopen("client/mailBox/list.txt", "w+");//建立邮箱列表
     if (fp6==NULL)
         return -1;
     fclose(fp6);

	 FILE *fp7;
     fp7 = fopen("client/mailBox/mailNumber.txt", "w+");//建立邮箱个数文件
     if (fp7==NULL)
         return -1;
     fclose(fp7);
    return 0;
}

