#include <iostream>
#include <tencentcloud/core/TencentCloud.h>
#include <tencentcloud/core/Credential.h>
#include <tencentcloud/sms/v20190711/SmsClient.h>
 
 
#include <string>
#include <vector>
 
using namespace TencentCloud;
using namespace TencentCloud::Sms::V20190711;
using namespace TencentCloud::Sms::V20190711::Model;
using namespace std;
 
class send_message
{
    
public:
    send_message();
    ~send_message();
    //展开函数
    
    template <typename  T, typename  ...Args>
    void add_phone_number(T head, Args... rest)
    {
       cout<<head<<endl;
       m_phone_numbers.push_back(head);
       add_phone_number(rest...);
    }
    void add_phone_number()
    {
        req.SetPhoneNumberSet(m_phone_numbers);
    }
    template <typename  T, typename  ...Args>
    void add_phone_template_param(T head, Args... rest)
    {
       cout<<head<<endl;
       m_template_param.push_back(head);
       add_phone_template_param(rest...);
    }
    void add_phone_template_param()
    {
        req.SetTemplateParamSet(m_template_param);
    }
    
    void init();
    bool send();
    
private:

    SendSmsRequest req;
    std::vector<std::string> m_phone_numbers; 
    std::vector<std::string> m_template_param;
    SmsClient *m_client;
    Credential *m_cred;
};
