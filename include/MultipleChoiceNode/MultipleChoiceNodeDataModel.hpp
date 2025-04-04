#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QVector>

#include <iostream>

class MultipleChoiceDialogueData;

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MultipleChoiceNodeDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    MultipleChoiceNodeDataModel();
    ~MultipleChoiceNodeDataModel() = default;

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

    QWidget *embeddedWidget() override;

    void addOutputPort();
    void removeOutputPort();
    void addChoiceLineEdit();
    void removeChoiceLineEdit();
    QString getChoiceText(int index) const;

    //std::weak_ptr<MultipleChoiceDialogueData> getInputDialogue();

    //void setOutputDialogue(std::shared_ptr<SimpleDialogueData> outputDialogue);

    //std::shared_ptr<SimpleDialogueData> getOutputDialogue();

signals:
    void buttonClicked();
    void portsChanged();
    void sizeChanged();

protected:
    virtual void compute() = 0;

protected:
    std::weak_ptr<MultipleChoiceDialogueData> _inputDialogue;
    std::shared_ptr<MultipleChoiceDialogueData> _outputDialogue;

    QFrame *_embeddedWidgetFrame;
    QVBoxLayout *_embeddedWidgetLayout;
    QFrame *_choicesFrame;
    QVBoxLayout *_choicesLayout;
    QPushButton *_editDialogueButton;
    QPushButton *_addChoiceButton;
    QPushButton *_removeChoiceButton;
    QVector<QLineEdit*> _choiceLineEdits;

    unsigned int _numOutputPorts;
};
