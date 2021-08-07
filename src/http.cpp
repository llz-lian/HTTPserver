#include<http.h>
#include<send.h>

Http::Http(/* args */const string & request)
{
    data = &request;
    paser(request);
    pos = 0;
}
Http::~Http()
{
}


void Http::paser(const string & str)
{
	enum {
		LINE, READY_LINE,
		HEAD0, READY_HEAD,
		HEAD1, READY_BODY,
		BODY
	};
	int status = LINE;
	int start = 0;
	int pos = 0;
	string sub = "";
    stringstream ss;
	for (const char &c : str)
	{

		switch (status)
		{
		case LINE:
			break;
		case READY_LINE:
			if (c == '\n')
			{
                sub = str.substr(start, pos-start+1);
                ss.clear();
                ss<<sub;
				getLine(sub,ss);
				start = pos + 1;
				status = HEAD0;
			}
			else {
				status = LINE;
			}
			break;
		case HEAD0:
			break;
		case READY_HEAD:
			if (c == '\n')
			{
                sub = str.substr(start, pos-start+1);
                ss.clear();
                ss<<sub;
				getHeader(sub,ss);
				start = pos + 1;
				status = HEAD1;
			}
			else {
				status = HEAD0;
			}
			break;
		case HEAD1:
			if (c != '\r')
				status = HEAD0;
			break;
		case READY_BODY:
			if (c == '\n')
			{
				status = BODY;
			}
			else {
				sub = str.substr(start, pos-start+1);
                ss.clear();
                ss<<sub;
                getHeader(sub,ss);
				start = pos + 1;
				status = HEAD0;
			}
			break;
		case BODY:
			break;
		default:
			break;
		}
		if (c == '\r'&&status != BODY)
			status++;
        if(status==BODY)
        {
            break;
        }
		pos++;
	}
    getBody(str.substr(pos,str.size()-pos));

}
void Http::getHeader(string &head,stringstream &ss)
{
    string name,value;
    getline(ss,name,':');
    getline(ss,value);
    //ss>>value;
    header[name] = value;
}
void Http::getLine(string &line,stringstream &ss)
{
    ss>>method;
    ss>>url;
    ss>>http_ver;
}
void Http::getBody(const string &body)
{
    this->body = body;
}

void Http::sendData(int fd)
{
    SendHttp * send;
    if(method=="GET")
    {
        send = new Get(this,fd);
        send->sendData();
    }
}

void Http::show()
{
    cout<<"http method:"<<method<<endl;
    cout<<"http url:"<<url<<endl;
    cout<<"http version:"<<http_ver<<endl;
    for(auto &[name,value]:header)
    {
        //cout<<1<<endl;
        cout<<name<<":"<<value;
        cout<<endl;
    }
    cout<<body<<endl;
}


vector<string> *  getUri(const Http * http,string & file_name)
{
    // /index.html  /home.html /{}/x.html

    //file_name += "./pages";
    vector<string> * args = new vector<string>;

    if(http->url.find("cgi-bin")== string::npos)//not cgi
    {
        if(http->url=="/")
        {
            file_name += "/home.html";
        }else{
            file_name += http->url;
        }   
    }else{

    }
    return args;
}