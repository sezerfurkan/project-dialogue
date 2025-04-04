#pragma once

#include <QString>

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class MultipleChoiceData
{
public:
    MultipleChoiceData(QString const message)
        : _message{message}
    {}

    QString message() const { return _message; }

private:
    QString _message;
};
