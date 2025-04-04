#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

#include <iostream>

class SimpleDialogueData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class SimpleNodeDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    SimpleNodeDataModel();
    ~SimpleNodeDataModel() = default;

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

    QWidget *embeddedWidget() override;

    std::weak_ptr<SimpleDialogueData> getInputDialogue();

    void setOutputDialogue(std::shared_ptr<SimpleDialogueData> outputDialogue);

    std::shared_ptr<SimpleDialogueData> getOutputDialogue();

signals:
    void buttonClicked();

protected:
    virtual void compute() = 0;

protected:
    std::weak_ptr<SimpleDialogueData> _inputDialogue;
    std::shared_ptr<SimpleDialogueData> _outputDialogue;

    QPushButton *_editDialogueButton;

};
