#ifndef USER_ACCOUNT_H
#define USER_ACCOUNT_H

#include <QObject>
#include <QJsonObject>
class user_account : public QObject
{
    Q_OBJECT
public:
    explicit user_account(QObject *parent = nullptr);
    QJsonObject mm;
signals:
};
#endif // USER_ACCOUNT_H
