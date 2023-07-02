#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H
#include <QString>
#include <QJsonObject>
#include<windows.h>
extern QString token;
extern QString username_glob;
extern QString password_glob;
extern QJsonObject jason_asli_glob;
extern QString contact_send;
extern QString type_send;
extern QString user_name;
extern QString all_mess;
extern QString my_name;
extern int county; 
extern QString *userha;
extern int userhas;
extern int channelhas;
extern int grouphas;
extern QString *channelha;
extern QString *groupha;
struct mme
{
    std::string src;
    std::string body;
};
extern mme temp_mme;
#endif // USER_ACCOUNT_H
