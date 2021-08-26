#include<http.hpp>
#include<send.hpp>

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
	//const string & s = str;
    getBody(str.substr(pos,str.size()-pos));

}
void Http::getHeader(const string &head,stringstream &ss)
{
    string name,value;
    getline(ss,name,':');
    getline(ss,value);
    //ss>>value;
    header[name] = value;
}
void Http::getLine(const string &line,stringstream &ss)
{
    ss>>method;
    ss>>url;
    ss>>http_ver;
}
void Http::getBody(const string &&body)
{
    this->body = &body;
}

void Http::sendData(int fd)
{
    SendHttp * send;
    if(method=="GET")
    {
        send = new Get(this,fd);//add thread
    }
	else if(method=="POST")
	{
		send = new Post(this,fd);
	}
	send->sendData();
	delete send;
}

void Http::show()
{
    cout<<"http method:"<<method<<endl;
    cout<<"http url:"<<url<<endl;
    cout<<"http version:"<<http_ver<<endl;
    for(auto &[name,value]:header)
    {
        cout<<name<<":"<<value;
        cout<<endl;
    }
    cout<<body<<endl;
}


shared_ptr<vector<string>> getUri(const Http * http,string & file_name)
{
    // /index.html  /home.html /{}/x.html
	shared_ptr<vector<string>> args = make_shared<vector<string>>();
    //vector<string> * args = new vector<string>;

    if(http->url.find("cgi-bin")== string::npos)//not cgi
    {
        if(http->url=="/")
        {
            file_name += "/home.html";
        }else{
            file_name += http->url;
        }   
    }else{//  /path?xxx=aaa&ooo=bbb
		int arg_start = 0;
		int url_len = http->url.size();
		while(arg_start<url_len&&http->url[arg_start]!='?')
		{
			++arg_start;//   ?xxx=aaa&ooo=bbb
		}
		if(arg_start>=url_len)
		{
			//cout<<"<getUri>bad url"<<endl;
			throw string("<getUri>bad url");
			return args;
		}
		int cgi_start = arg_start;
		while(cgi_start>=0&&http->url[cgi_start]!='/')
		{
			cgi_start--;/* /path? */
		}	
		args->push_back(http->url.substr(cgi_start,arg_start-cgi_start+1));  // cgi_name
		args->push_back(http->url.substr(arg_start,url_len - arg_start));    // args
    }
    return args;
}