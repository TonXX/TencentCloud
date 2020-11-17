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
 
int main()
{
    // 必须调用初始化函数
    TencentCloud::InitAPI();
 
    //https://console.cloud.tencent.com/cam/overview  访问管理/访问密钥/API密钥管理
    string secretId = "AKIDC*****EqhJePiFVV*******";
    string secretKey = "EBxj*****nPGtHOKFwQ********";
    Credential cred = Credential(secretId, secretKey);
    
    ClientProfile clientProfile;
    HttpProfile httpProfile;
    httpProfile.SetEndpoint("sms.tencentcloudapi.com");
    clientProfile.SetHttpProfile(httpProfile);
 
    SmsClient client(cred, "ap-beijing", clientProfile);
    SendSmsRequest req;
 
    //设置手机号，需要+86
    std::vector<std::string> phoneNumbers;
    phoneNumbers.push_back("+86185****6627");
    req.SetPhoneNumberSet(phoneNumbers);
    
    //设置模板id。
    //https://console.cloud.tencent.com/smsv2/csms-sign
    //短信控制台/国内短信/征文模板管理（以国内短信为例）
    req.SetTemplateID("77***9");
 
    //设置短信SdkAppid
    //https://console.cloud.tencent.com/smsv2/app-manage
    //短信控制台/应用管理/应用列表
    req.SetSmsSdkAppid("140******70");
 
    //设置签名内容，此处需审核通过的签名，否则会报错。如下
    //https://console.cloud.tencent.com/smsv2/csms-sign
    //短信控制台/国内短信/签名管理（以国内短信为例）
    req.SetSign("董大仙aa");
 
    //设置模板参数，此处与征文模板一直，如下为我的模板，只需要一个参数{1},故传一个参数即可。
    //验证码为：{1}，您正在登录，若非本人操作，请勿泄露。测试
    std::vector<std::string> templateParam;
    templateParam.push_back("1111");
    //templateParam.push_back("验证码有效时间");
    req.SetTemplateParamSet(templateParam);
 
    SmsClient::SendSmsOutcome out = client.SendSms(req);
 
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
 
    bool isok = out.IsSuccess();
 
    cout << "isok:" << isok << endl;
 
    return 0;
}