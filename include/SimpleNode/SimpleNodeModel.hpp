#pragma once

#include "SimpleDialogueData.hpp"
#include "SimpleNodeDataModel.hpp"

#include <QtNodes/NodeDelegateModel>

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class SimpleNodeModel : public SimpleNodeDataModel
{
public:
    ~SimpleNodeModel() = default;

public:
    QString caption() const override { return QStringLiteral("Simple Node"); }

    QString name() const override { return QStringLiteral("Simple Node"); }

private:
    void compute() override
    {
        PortIndex const outPortIndex = 0;

        auto inputDialogue = _inputDialogue.lock();

        if (inputDialogue) {
            _outputDialogue = std::make_shared<SimpleDialogueData>();
            _outputDialogue->setDialogueId(inputDialogue->dialogueId());
        } else {
            _outputDialogue.reset();
        }

        Q_EMIT dataUpdated(outPortIndex);
    }
};
