#include "SimpleNodeDataModel.hpp"

#include "SimpleDialogueData.hpp"

SimpleNodeDataModel::SimpleNodeDataModel()
    : _editDialogueButton{nullptr}
{

}

unsigned int SimpleNodeDataModel::nPorts(PortType portType) const
{
    return 1;
}

NodeDataType SimpleNodeDataModel::dataType(PortType, PortIndex) const
{
    return SimpleDialogueData().type();
}

QWidget *SimpleNodeDataModel::embeddedWidget()
{
    if (!_editDialogueButton) {
        _editDialogueButton = new QPushButton();

        _editDialogueButton->setText("Edit Dialogue");
        _editDialogueButton->setMaximumSize(_editDialogueButton->sizeHint());

        connect(_editDialogueButton, &QPushButton::clicked, this, [this]() {
            Q_EMIT buttonClicked();
        });
    }

    return _editDialogueButton;
}


std::shared_ptr<NodeData> SimpleNodeDataModel::outData(PortIndex)
{
    //return std::static_pointer_cast<NodeData>(_outputDialogue);
    return _outputDialogue;
}

void SimpleNodeDataModel::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
    auto dialogueData = std::dynamic_pointer_cast<SimpleDialogueData>(data);

    if (!data) {
        Q_EMIT dataInvalidated(0);
    }

    if (portIndex == 0){
        _inputDialogue = dialogueData;
        //_outputDialogue = dialogueData;
        std::cout << "test" << std::endl;
    }


    compute();
}


std::weak_ptr<SimpleDialogueData> SimpleNodeDataModel::getInputDialogue()
{
    return _inputDialogue.lock();
}


void SimpleNodeDataModel::setOutputDialogue(std::shared_ptr<SimpleDialogueData> outputDialogue)
{
    _outputDialogue = outputDialogue;
}

std::shared_ptr<SimpleDialogueData> SimpleNodeDataModel::getOutputDialogue()
{
    return _outputDialogue;
}
