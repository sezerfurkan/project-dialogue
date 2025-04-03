#pragma once

#include <QtNodes/NodeData>

#include "DialogueData.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class SimpleDialogueData : public NodeData
{
public:
    SimpleDialogueData()
        : _dialogueId{""} , _dialogueChain{{}}
    {}

    SimpleDialogueData(QString const dialogueId, bool const isStartNodeData=false)
        : _dialogueId{dialogueId}, _isStartNodeData{isStartNodeData}
    {}

    NodeDataType type() const override { return NodeDataType{"simpleDialogue", "SimpleDialogue"}; }

    void setDialogueId(QString const dialogueId) { _dialogueId = dialogueId; }
    void addDialogue(DialogueData* const dialogue) { _dialogueChain.emplace_back(dialogue); }
    int dialogueSize() { return _dialogueChain.size(); }
    void clear() { _dialogueId = ""; _dialogueChain.clear(); }

    QString dialogueId() const { return _dialogueId; }
    QVector<DialogueData*> dialogueChain() const { return _dialogueChain; }
    bool isStartNodeData() const { return _isStartNodeData; }

private:
    QString _dialogueId;
    QVector<DialogueData*> _dialogueChain;
    bool _isStartNodeData = false;
};
