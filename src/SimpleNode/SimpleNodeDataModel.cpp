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

        //_lineEdit->setValidator(new QDoubleValidator());
        _editDialogueButton->setText("Edit Dialogue");
        _editDialogueButton->setMaximumSize(_editDialogueButton->sizeHint());

        //connect(_editDialogueButton, &QPushButton::clicked, this, )

        //connect(_lineEdit, &QLineEdit::textChanged, this, &NumberSourceDataModel::onTextEdited);

        //_lineEdit->setText(QString::number(_number->number()));

        connect(_editDialogueButton, &QPushButton::clicked, this, [this]() {
            Q_EMIT buttonClicked();
        });
    }

    return _editDialogueButton;
}


std::shared_ptr<NodeData> SimpleNodeDataModel::outData(PortIndex)
{
    return std::static_pointer_cast<NodeData>(_outputDialogue);
}

void SimpleNodeDataModel::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
    auto dialogueData = std::dynamic_pointer_cast<SimpleDialogueData>(data);

    if (!data) {
        Q_EMIT dataInvalidated(0);
    }

    //connect(_editDialogueButton, &QPushButton::clicked, this, &SimpleNodeDataModel::onEditDialogueButtonClicked);

    compute();
}


std::weak_ptr<SimpleDialogueData> SimpleNodeDataModel::getInputDialogue()
{
    return _inputDialogue.lock();
}

