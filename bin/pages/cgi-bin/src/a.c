#include <stdio.h>

int main()
{
    printf("Content-Type: text/html\n\n");
    const char* str = "<html>"
    "<head><meta charset=\"UTF-8\"><title>C CGI</title></head>\r\n"
    "<body><p>this is a C</p><a href=\"/home.html\">首页</a></body>"
    "</html>";    
    printf("%s",str);
    return 0;
}