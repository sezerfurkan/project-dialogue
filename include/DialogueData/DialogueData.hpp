#pragma once

#include <QString>

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class DialogueData
{
public:
    DialogueData()
        : _characterName{""}, _message{""}
    {}

    DialogueData(QString const characterName, QString const message)
        : _characterName{characterName}, _message{message}
    {}

    QString characterName() const { return _characterName; }
    QString message() const { return _message; }

private:
    QString _characterName;
    QString _message;
};
