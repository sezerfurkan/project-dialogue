#include "MultipleChoiceNodeDataModel.hpp"

#include "MultipleChoiceDialogueData.hpp"

MultipleChoiceNodeDataModel::MultipleChoiceNodeDataModel()
    : _editDialogueButton{nullptr}, _addChoiceButton{nullptr}, _removeChoiceButton{nullptr}, _numOutputPorts{1}
{

}

unsigned int MultipleChoiceNodeDataModel::nPorts(PortType portType) const
{
    if(portType == PortType::In){
        return 1;
    }
    else{
        return _numOutputPorts;
    }
}

NodeDataType MultipleChoiceNodeDataModel::dataType(PortType, PortIndex) const
{
    return MultipleChoiceDialogueData().type();
}

QWidget *MultipleChoiceNodeDataModel::embeddedWidget()
{
    if (!_embeddedWidgetFrame) {
        _embeddedWidgetFrame = new QFrame();
        _embeddedWidgetFrame->setMinimumWidth(400); // Set minimum width for the entire node
        _embeddedWidgetLayout = new QVBoxLayout(_embeddedWidgetFrame);
        _embeddedWidgetLayout->setContentsMargins(5, 5, 5, 5);
        _embeddedWidgetLayout->setSpacing(5);

        // Buttons frame
        QFrame *buttonsFrame = new QFrame();
        buttonsFrame->setMinimumWidth(400); // Set minimum width for buttons frame
        QHBoxLayout *buttonsLayout = new QHBoxLayout(buttonsFrame);
        buttonsLayout->setContentsMargins(0, 0, 0, 0);
        buttonsLayout->setSpacing(5);

        _editDialogueButton = new QPushButton();
        _editDialogueButton->setText("Edit Dialogue");
        _editDialogueButton->setMinimumWidth(90);

        _addChoiceButton = new QPushButton();
        _addChoiceButton->setText("Add Choice");
        _addChoiceButton->setMinimumWidth(90);

        _removeChoiceButton = new QPushButton();
        _removeChoiceButton->setText("Remove Choice");
        _removeChoiceButton->setMinimumWidth(90);
        _removeChoiceButton->setEnabled(false); // Initially disabled

        buttonsLayout->addWidget(_editDialogueButton);
        buttonsLayout->addWidget(_addChoiceButton);
        buttonsLayout->addWidget(_removeChoiceButton);

        // Choices frame
        _choicesFrame = new QFrame();
        _choicesFrame->setMinimumWidth(400); // Set minimum width for choices frame
        _choicesLayout = new QVBoxLayout(_choicesFrame);
        _choicesLayout->setContentsMargins(0, 0, 0, 0);
        _choicesLayout->setAlignment(Qt::AlignTop);
        _choicesLayout->setSpacing(5);
        _embeddedWidgetLayout->addWidget(_choicesFrame);

        _embeddedWidgetLayout->addWidget(buttonsFrame);

        // Add initial choice
        addChoiceLineEdit();

        connect(_editDialogueButton, &QPushButton::clicked, this, [this]() {
            Q_EMIT buttonClicked();
        });

        connect(_addChoiceButton, &QPushButton::clicked, this, [this]() {
            addOutputPort();
            addChoiceLineEdit();
            _removeChoiceButton->setEnabled(true);
            Q_EMIT sizeChanged();
        });

        connect(_removeChoiceButton, &QPushButton::clicked, this, [this]() {
            removeOutputPort();
            removeChoiceLineEdit();
            if (_numOutputPorts == 1) {
                _removeChoiceButton->setEnabled(false);
            }
            Q_EMIT sizeChanged();
        });

        _embeddedWidgetFrame->adjustSize();
    }

    return _embeddedWidgetFrame;
}

void MultipleChoiceNodeDataModel::addOutputPort()
{
    _numOutputPorts++;
    Q_EMIT portsChanged();
}

void MultipleChoiceNodeDataModel::removeOutputPort()
{
    if (_numOutputPorts > 1) {
        _numOutputPorts--;
        Q_EMIT portsChanged();
    }
}

void MultipleChoiceNodeDataModel::addChoiceLineEdit()
{
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(QString("Choice %1").arg(_choiceLineEdits.size() + 1));
    lineEdit->setMinimumWidth(400); // Set wider minimum width for LineEdit
    lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _choiceLineEdits.append(lineEdit);
    _choicesLayout->addWidget(lineEdit);
    
    // Update frame sizes
    _choicesFrame->adjustSize();
    _embeddedWidgetFrame->adjustSize();
}

void MultipleChoiceNodeDataModel::removeChoiceLineEdit()
{
    if (!_choiceLineEdits.isEmpty()) {
        QLineEdit* lineEdit = _choiceLineEdits.last();
        _choiceLineEdits.removeLast();
        _choicesLayout->removeWidget(lineEdit);
        lineEdit->hide();
        lineEdit->deleteLater();
        
        // Update frame sizes
        _choicesFrame->adjustSize();
        _embeddedWidgetFrame->adjustSize();
    }
}

QString MultipleChoiceNodeDataModel::getChoiceText(int index) const
{
    if (index >= 0 && index < _choiceLineEdits.size()) {
        return _choiceLineEdits[index]->text();
    }
    return QString();
}

std::shared_ptr<NodeData> MultipleChoiceNodeDataModel::outData(PortIndex)
{
    return _outputDialogue;
}

void MultipleChoiceNodeDataModel::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
    auto dialogueData = std::dynamic_pointer_cast<MultipleChoiceDialogueData>(data);

    if (!data) {
        Q_EMIT dataInvalidated(0);
    }

    if (portIndex == 0){
        _inputDialogue = dialogueData;
        std::cout << "test" << std::endl;
    }

    compute();
}


//std::weak_ptr<MultipleChoiceDialogueData> MultipleChoiceNodeDataModel::getInputDialogue()
//{
//    return _inputDialogue.lock();
//}


//void MultipleChoiceNodeDataModel::setOutputDialogue(std::shared_ptr<MultipleChoiceDialogueData> outputDialogue)
//{
//    _outputDialogue = outputDialogue;
//}

//std::shared_ptr<MultipleChoiceDialogueData> MultipleChoiceNodeDataModel::getOutputDialogue()
//{
//    return _outputDialogue;
//}
