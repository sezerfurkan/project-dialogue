#pragma once

#include <QtNodes/NodeData>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class StartDialogueData : public NodeData
{
public:
    StartDialogueData()
        : _dialogueId{""}
    {}

    StartDialogueData(QString const dialogueId)
        : _dialogueId{dialogueId}
    {}

    NodeDataType type() const override { return NodeDataType{"simpleDialogue", "SimpleDialogue"}; }

    void setDialogueId(QString const dialogueId) { _dialogueId = dialogueId; }

    QString dialogueId() const { return _dialogueId; }

private:
    QString _dialogueId;
};
