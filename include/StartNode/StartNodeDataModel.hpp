#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>

#include <iostream>

class SimpleDialogueData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

class QLineEdit;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class StartNodeDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    StartNodeDataModel();

    virtual ~StartNodeDataModel() {}

public:
    QString caption() const override { return QStringLiteral("Start Node"); }

    bool captionVisible() const override { return false; }

    QString name() const override { return QStringLiteral("Start Node"); }

public:
    QJsonObject save() const override;

    void load(QJsonObject const &p) override;

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override {}

    QWidget *embeddedWidget() override;

public:
    void setDialogueId(QString dialogueId);

private Q_SLOTS:

    void onTextEdited(QString const &string);

private:
    std::shared_ptr<SimpleDialogueData> _dialogueData;

    QLineEdit *_lineEdit;
};
