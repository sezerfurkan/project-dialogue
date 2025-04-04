#pragma once

#include <QtNodes/NodeData>

#include "DialogueData.hpp"
#include "MultipleChoiceData.hpp"

using QtNodes::NodeData;
using QtNodes::NodeDataType;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class MultipleChoiceDialogueData : public NodeData
{
public:
    MultipleChoiceDialogueData()
        : _dialogueId{""} , _dialogue{nullptr}, _choices{{}}
    {}

    MultipleChoiceDialogueData(QString const dialogueId, DialogueData* const dialogue, QVector<MultipleChoiceData*> choices)
        : _dialogueId{dialogueId}, _dialogue{dialogue}, _choices{choices}
    {}

    NodeDataType type() const override { return NodeDataType{"multipleChoiceDialogue", "MultipleChoiceDialogue"}; }

    void setDialogueId(QString const dialogueId) { _dialogueId = dialogueId; }
    void setDialogue(DialogueData* const dialogue) { _dialogue = dialogue; }
    void addChoice(MultipleChoiceData* const choice) { _choices.emplace_back(choice); }
    //void clear() { _dialogueId = ""; _choices.clear(); }

    QString dialogueId() const { return _dialogueId; }
    DialogueData* dialogue() const { return _dialogue; }
    QVector<MultipleChoiceData*> choices() const { return _choices; }

private:
    QString _dialogueId;
    DialogueData* _dialogue;
    QVector<MultipleChoiceData*> _choices;
};
