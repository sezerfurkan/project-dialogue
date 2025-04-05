#pragma once

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

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
class EndNodeDataModel : public NodeDelegateModel
{
    Q_OBJECT

public:
    EndNodeDataModel();

    virtual ~EndNodeDataModel() {}

public:
    QString caption() const override { return QStringLiteral("End Node"); }

    bool captionVisible() const override { return true; }

    QString name() const override { return QStringLiteral("End Node"); }

public:
    QJsonObject save() const override;

    void load(QJsonObject const &p) override;

public:
    unsigned int nPorts(PortType portType) const override;

    NodeDataType dataType(PortType portType, PortIndex portIndex) const override;

    std::shared_ptr<NodeData> outData(PortIndex port) override;

    void setInData(std::shared_ptr<NodeData>, PortIndex) override;

    QWidget *embeddedWidget() override;

public:
    void setDialogueId(QString dialogueId);
    std::shared_ptr<SimpleDialogueData> getDialogue();

signals:
    void playDialogueButtonClicked();

private Q_SLOTS:

    void onTextEdited(QString const &string);

private:
    std::shared_ptr<SimpleDialogueData> _dialogueData;

    QFrame *_embeddedWidgetFrame;
    QVBoxLayout *_embeddedWidgetLayout;
    QLineEdit *_dialogueIdLineEdit;
    QPushButton *_playDialogueButton;

};
