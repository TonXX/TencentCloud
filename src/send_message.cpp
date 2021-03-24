#include"send_message.h"
#include<ctime>
send_message::send_message()
{
    cout<<"construct"<<endl;
    TencentCloud::InitAPI();
}
send_message::~send_message()
{
    cout<<"~construct"<<endl;
    TencentCloud::ShutdownAPI();
}

bool send_message::send()
{
    //发送短信
    struct timespec start;
    struct timespec end;
    clock_gettime(CLOCK_REALTIME,&start);
    SmsClient::SendSmsOutcome out = m_client->SendSms(req);
    clock_gettime(CLOCK_REALTIME,&end);

    cout<<(end.tv_sec * 1000000000 + end.tv_nsec)-(start.tv_sec * 1000000000 + start.tv_nsec)<<endl;
    //获取错误
    Error err = out.GetError();
    cout << "err.GetErrorMessage:" << err.GetErrorMessage() << endl;
    cout << "err.GetErrorCode:" << err.GetErrorCode() << endl;
    SendSmsResponse res = out.GetResult();
    std::vector<SendStatus> status = res.GetSendStatusSet();
    
    for (auto item : status) {
        cout << "item.GetSerialNo:" << item.GetSerialNo() << endl;
        cout << "item.GetPhoneNumber:" << item.GetPhoneNumber() << endl;
        cout << "item.GetFee:" << item.GetFee() << endl;
        cout << "item.GetSessionContext:" << item.GetSessionContext() << endl;
        cout << "item.GetCode:" << item.GetCode() << endl;
        cout << "item.GetMessage:" << item.GetMessage() << endl;
        cout << "item.GetIsoCode:" << item.GetIsoCode() << endl;
    }
    
    
    return out.IsSuccess();
}
void send_message::init()
{ 
    //https://console.cloud.tencent.com/cam/overview  访问管理/访问密钥/API密钥管理
    string secretId = "xxxx";
    string secretKey = "xxxx";
    
    m_cred = new Credential(secretId, secretKey);
    
    ClientProfile clientProfile;
    HttpProfile httpProfile;
    httpProfile.SetEndpoint("sms.tencentcloudapi.com");
    clientProfile.SetHttpProfile(httpProfile);
 
    m_client = new SmsClient(*m_cred, "ap-beijing", clientProfile);

    //设置模板id
    //https://console.cloud.tencent.com/smsv2/csms-sign
    //短信控制台/国内短信/征文模板管理（以国内短信为例）
    req.SetTemplateID("781989");
        
    //设置短信SdkAppid
    //https://console.cloud.tencent.com/smsv2/app-manage
    //短信控制台/应用管理/应用列表
    req.SetSmsSdkAppid("1400448648");
    
    //设置签名内容，此处需审核通过的签名，否则会报错（如：The SecretId is not found, please ensure that your SecretId is correct）。如下
    //https://console.cloud.tencent.com/smsv2/csms-sign
    //短信控制台/国内短信/签名管理（以国内短信为例）
    req.SetSign("董大仙aa");
}


int main()
{
    send_message sm;
    sm.init();
    sm.add_phone_number<std::string>("+8618098841143");
    //sm.add_phone_number<std::string>("+8618840851193");
    sm.add_phone_template_param<std::string>("DCE","90%","1111");
    cout<<sm.send()<<endl;
    return 0;
}

