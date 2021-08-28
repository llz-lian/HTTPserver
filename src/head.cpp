#include<head.hpp>
int writeFd(int fd,const char * buff,size_t len)
{
    ssize_t written;
    size_t n = len;
    while(len>0)
    {
        if((written = write(fd,buff,len))<=0)
        {
            perror("<writeFd>write err");
            if(errno == EINTR)
                written = 0;
            else
                return -1;
        }
        len -= written;
        buff += written;
    }
    return n;
}
void getFileType(const char * file_name,char * file_type)
{
    if(strstr(file_name,".html"))
        strcpy(file_type,"text/html");
    else if(strstr(file_name,".gif"))
        strcpy(file_type,"image/gif");
    else if(strstr(file_name,".jpg"))
        strcpy(file_type,"image/jpeg");
    else 
        strcpy(file_type,"text/plain");
}
int readFile(const char * file_name,char * buff,int len)
{
    FILE * fp = fopen(file_name,"r");
    if(fp==nullptr)
        return -1;
    fseek( fp , 0 , SEEK_END );
    int file_size = ftell( fp );
    if(file_size>=len)
        return -2;
    fseek( fp , 0 , SEEK_SET);
    fread( buff , file_size , sizeof(char) , fp);
    buff[file_size] = '\0';
    fclose(fp);
    return 0;
}


