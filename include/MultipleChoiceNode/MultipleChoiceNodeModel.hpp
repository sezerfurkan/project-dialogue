#pragma once

#include "MultipleChoiceDialogueData.hpp"
#include "MultipleChoiceNodeDataModel.hpp"

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MultipleChoiceNodeModel : public MultipleChoiceNodeDataModel
{
public:
    ~MultipleChoiceNodeModel() = default;

public:
    QString caption() const override { return QStringLiteral("Multiple Choice Node"); }

    QString name() const override { return QStringLiteral("Multiple Choice Node"); }

private:
    void compute() override
    {
        PortIndex const outPortIndex = 0;

        //auto inputDialogue = _inputDialogue.lock();
        //if (inputDialogue) {
        //    _outputDialogue = std::make_shared<SimpleDialogueData>();
        //    _outputDialogue->setDialogueId(inputDialogue->dialogueId());
        //} else {
        //    _outputDialogue.reset();
        //}

        Q_EMIT dataUpdated(outPortIndex);
    }
};
