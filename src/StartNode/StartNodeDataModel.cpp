#include "StartNodeDataModel.hpp"

#include "SimpleDialogueData.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

StartNodeDataModel::StartNodeDataModel()
    : _lineEdit{nullptr}
    , _dialogueData(std::make_shared<SimpleDialogueData>("New dialogue chain", true))
{}

QJsonObject StartNodeDataModel::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["startDialogueId"] = _dialogueData->dialogueId();

    return modelJson;
}

void StartNodeDataModel::load(QJsonObject const &p)
{
    QJsonValue v = p["startDialogueId"];

    if (!v.isUndefined()) {
        QString dialogueId = v.toString();

        _dialogueData = std::make_shared<SimpleDialogueData>(dialogueId);

        if (_lineEdit)
            _lineEdit->setText(_dialogueData->dialogueId());

    }
}

unsigned int StartNodeDataModel::nPorts(PortType portType) const
{
    unsigned int result = 1;

    switch (portType) {
    case PortType::In:
        result = 0;
        break;

    case PortType::Out:
        result = 1;

    default:
        break;
    }

    return result;
}

void StartNodeDataModel::onTextEdited(QString const &str)
{
    bool ok = true;

    //QString dialogueId = str.toStdString(&ok);

    if (ok) {
        _dialogueData = std::make_shared<SimpleDialogueData>(str);

        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}

NodeDataType StartNodeDataModel::dataType(PortType, PortIndex) const
{
    return SimpleDialogueData().type();
}

std::shared_ptr<NodeData> StartNodeDataModel::outData(PortIndex)
{
    return _dialogueData;
}

QWidget *StartNodeDataModel::embeddedWidget()
{
    if (!_lineEdit) {
        _lineEdit = new QLineEdit();

        _lineEdit->setMaximumSize(_lineEdit->sizeHint());

        connect(_lineEdit, &QLineEdit::textChanged, this, &StartNodeDataModel::onTextEdited);

        _lineEdit->setText(_dialogueData->dialogueId());
    }

    return _lineEdit;
}

void StartNodeDataModel::setDialogueId(const QString dialogueId)
{
    _dialogueData = std::make_shared<SimpleDialogueData>(dialogueId);

    Q_EMIT dataUpdated(0);

    if (_lineEdit)
        _lineEdit->setText(_dialogueData->dialogueId());
}
