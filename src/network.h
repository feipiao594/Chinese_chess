#ifndef NETWORK_H
#define NETWORK_H

#include "exception.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

#define SETTING_FILENAME "network.json"

class Network : public QObject{
    Q_OBJECT

    enum class RequestType {
        LOGIN = 0, SIGNUP = 1, FIND = 2, MESSAGE = 3, MOVE = 4,
        CONTINUE = 5, //长轮询
        UNEXPECTED = -1
    };
    bool find_complete = false;
    QNetworkAccessManager manager;
    QString username;
    unsigned timeout;
    QTimer timer;
    QNetworkRequest* request = nullptr; //长轮询请求
    QString url[6];
public:
    static Network* getInstance() {
        static Network* singleton = nullptr;
        if (!singleton)
            singleton = new Network;
        return singleton;
    }
    bool getIfStart(){
        return find_complete;
    }
private:
    Network();
public:
    void setUsername(const QString &name){
        username=name;
    };
    inline void login(QString username, QString passwd) {
        auto usr = QUrl::toPercentEncoding(username);
        auto pwd = QUrl::toPercentEncoding(passwd);
        send(setRequest(RequestType::LOGIN, QString("?usr=%1&pwd=%2").arg(usr).arg(pwd)));
    }
    inline void signup(QString username, QString passwd) {
        auto usr = QUrl::toPercentEncoding(username);
        auto pwd = QUrl::toPercentEncoding(passwd);
        send(setRequest(RequestType::SIGNUP, QString("?usr=%1&pwd=%2").arg(usr).arg(pwd)));
    }
    inline void findOpp(bool another = false) {
        static unsigned wait = 0;
        if (another)
            wait++;
        //if(wait==80000)onTimeOut();
        send(setRequest(RequestType::FIND, QString("?wait=%1").arg(wait)));
    }
private:
    void readSettings();
    void send(QNetworkRequest* request) {
        if (request == this->request) {
            timer.setInterval(timeout);
            timer.start();
        }
        manager.get(*request);
        //connect(&manager, &QNetworkAccessManager::finished, this, &Network::onResponse);
    }
    inline QNetworkRequest* setRequest(RequestType type, QString form) {
        QNetworkRequest* request;
        if (type >= RequestType::FIND) {
            auto usr = QUrl::toPercentEncoding(username);
            request = new QNetworkRequest(QUrl(url[(int)type] + form + QString("&usr=%1").arg(usr)));
            if (type == RequestType::CONTINUE)
                this->request = request;
        } else
            request = new QNetworkRequest(QUrl(url[(int)type] + form));
        return request;
    }
    inline const RequestType str2enum(const QString& str) {
        if (str.toLower() == "signup")
            return RequestType::SIGNUP;
        if (str.toLower() == "login")
            return RequestType::LOGIN;
        if (str.toLower() == "find")
            return RequestType::FIND;
        if (str.toLower() == "message")
            return RequestType::MESSAGE;
        if (str.toLower() == "move")
            return RequestType::MOVE;
        if (str.toLower() == "continue")
            return RequestType::CONTINUE;
        return RequestType::UNEXPECTED;
    }
    inline void error() {
        throw Exception("Network Error!", 2);
    }
signals:
    void loginOK();
    void signupOK();
    void findOK(const QString opp_name);
    void failure(const QString message);
    void move(const std::pair<int, int> from, const std::pair<int, int> to);
    //聊天功能
    void message(const QString);
private slots:
    void onTimeOut() {
        try {
            error();
        } catch (Exception e) {
            e.process();
        }
    }
public slots:
    void onMove(const std::pair<int, int> from, const std::pair<int, int> to);
    void onResponse(QNetworkReply* reply);
    //聊天功能
    void sendMessage(QString);
};

#endif // NETWORK_H
