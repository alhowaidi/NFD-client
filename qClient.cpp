#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <vector>
//#include "options.hpp"
//#include "ndncatchunks.hpp"
//#include "consumer.hpp"
#include <chrono>
#include <thread>
#include <time.h>

#include <cpprest/http_client.h>
#include <cpprest/json.h>
//#include <cpprest/ppltasks.h>
//#include <json.h>
//#pragma comment(lib, "cpprest110_1_1")
#include "cpprest/http_listener.h"
using namespace web;
using namespace web::http;
using namespace web::http::client;

using namespace boost::interprocess;
using namespace std;
int main ()
{
//--- message_queue::remove("message_queue");
// ndn::chunks::ndnChunks nchunks;
//    while(true)
    {
   try{
//struct timespec tim,tim2;
//tim.tv_sec = 0;
//tim.tv_nsec = 1;
//nanosleep(&tim, NULL);


//-- std::this_thread::sleep_for(std::chrono::nanoseconds(10000));
 //--     message_queue mq(open_only ,"message_queue") ;

     //---- size_t const max_msg_size = 0x100;

      std::string s="YYMMMlllllll";
//-----      s.resize(max_msg_size);
      size_t msg_size;
      unsigned msg_prio;
//--      mq.receive(&s[0], s.size(), msg_size, msg_prio);
//--      s.resize(msg_size);

//      ndn::chunks::ndnChunks nchunks;
//      nchunks.startChunk(s);


      std::cout <<"s: " << s << std::endl;

      // sending post message with the information .......
//----      http_client_config config;
//----      credentials cred(U("onos"), U("rocks"));
//----      config.set_credentials(cred);
//      http_client client(U("http://10.71.103.63:34568"),config);
      //http_client client(U("http://onos:rocks@10.71.105.126:8181/onos/mobius/ndn/"),config);

http_client client(U("http://10.10.1.2:34568"));//l0.71.103.63:34568"));
//--- http_client client(U("http://10.71.105.126:8181/onos/mobius/ndn/"),config);
      json::value postData;
      postData["name"] = json::value::string(U(s));
      //      postData["work"] = json::value::string(U("Phd"));
      postData["interestFileResource"] = json::value::string(U("Resource Name"));
      postData["interestSrc"] = json::value::string(U("src IP"));
      postData["interestDst"] = json::value::string(U("dst IP"));
      http_request request;
      request.set_body(postData);

      request.set_method(methods::POST);

      wcout << L"\nput values\n";

      http_response response = client.request(request).get();
      if(response.status_code() == status_codes::OK)
      {
	      auto body = response.extract_string();
	      std::wcout << L"Added new Id: " << body.get().c_str() << std::endl;

	      //      return std::stoi(body.get().c_str());
      }
      //...........................

   }
   catch(interprocess_exception &ex){
//---	   message_queue::remove("message_queue");
   }

//---   message_queue::remove("message_queue");
    }
    return 0;
}
