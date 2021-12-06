#include "Http.hpp"
#include "Send.hpp"
using namespace std;
/*Http::Http(const string & request,const sinfo & in):info(in)
{
    data = &request;
    paser(request);
    pos = 0;

}*/
Http::Http(const string & request)
{
    data = &request;
    paser(request);
    pos = 0;
}

Http::~Http()
{
}

void Http::init(const string & request)
{
	data = &request;
    paser(request);
    pos = 0;
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


void Http::show() const
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

void Http::sendData(int fd)
{
	shared_ptr<NSend::SendHttp> send;
	shared_ptr<Http> this_http = getThis();
	try{
		send = Factory::get().produce_shared(method);
		send->init(this_http,fd);
	}catch(string &s)
	{
		send = make_shared<NSend::Get>(NSend::Get(this_http,fd));
	}
	send->sendData();
}

shared_ptr<vector<string>> getUri(shared_ptr<Http> http,string & file_name)
{
    // /index.html  /home.html /{}/x.html
	
	const string & url = http->getUrl();
	shared_ptr<vector<string>> args = make_shared<vector<string>>();
	if(http==nullptr)
		return args;
    //vector<string> * args = new vector<string>;
    if(url.find("cgi-bin")== string::npos)//not cgi
    {
        if(url=="/")
        {
            file_name += "/home.html";
        }else{
            file_name += url;
        }   
    }else{//  /cgi-bin/x.cgi(?xxx=aaa&ooo=bbb/)
		int arg_start = 0;
		int url_len = url.size();
		while(arg_start<url_len&&url[arg_start]!='?')
		{
			++arg_start;//   ?xxx=aaa&ooo=bbb
		}
		if(arg_start>=url_len)
		{
			//cout<<"<getUri>bad url"<<endl;
			//throw string("<getUri>bad url");
			args->push_back(file_name + url);
			args->push_back("");
			return args;
		}
		args->push_back(file_name + url);  // cgi_name   /pages/cgi-bin/xxx.cgi
		args->push_back(url.substr(arg_start,url_len - arg_start));    // args
    }
    return args;
}