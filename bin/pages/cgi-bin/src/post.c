#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
int main(void)
{
        int len;
        char *lenstr,poststr[256];
        char user[32],pwd[32];
        printf("Content-Type:text/html\n\n");
        printf("<HTML>\n");
        printf("<HEAD>\n<TITLE >post Method</TITLE>\n</HEAD>\n");
        printf("<BODY>\n");
        printf("<div style=\"font-size:12px\">\n");
        lenstr=getenv("CONTENT_LENGTH");
        if(NULL == lenstr)
                printf("<DIV STYLE=\"COLOR:RED\">Error: CONTENT_LENGTH not set!</DIV>\n");
        else{
                len=atoi(lenstr);
                fgets(poststr,len+1,stdin);
                if(sscanf(poststr,"Username=%[^&]&Password=%s",user,pwd)!=2){
                        printf("<DIV STYLE=\"COLOR:RED\">Error: parse username and password error!</DIV>\n");
                }
                else{
                        if(!strcasecmp(user, "admin") && !strcasecmp(pwd, "123456"))
                            printf("<DIV STYLE=\"COLOR:GREEN; font-size:15px;font-weight:bold\">username=%s,password=%s</DIV>\n",user,pwd);
                        else
                            printf("<DIV STYLE=\"COLOR:RED\">username or password error!</DIV>\n");
                }
        }

        printf("</div>\n");
        printf("</BODY>\n");
        printf("</HTML>\n");
        fflush(stdout);
        return 0;
}