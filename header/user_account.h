#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H
#include <QString>
#include <QJsonObject>
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
struct mme
{
    std::string src;
    std::string body;
};
extern mme temp_mme;
#endif // USER_ACCOUNT_H
