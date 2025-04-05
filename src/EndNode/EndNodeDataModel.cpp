#include "EndNodeDataModel.hpp"

#include "SimpleDialogueData.hpp"

#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QtWidgets/QLineEdit>

EndNodeDataModel::EndNodeDataModel()
    : _dialogueIdLineEdit{nullptr}, _playDialogueButton{nullptr}
    , _dialogueData(std::make_shared<SimpleDialogueData>("New dialogue chain", true))
{}

QJsonObject EndNodeDataModel::save() const
{
    QJsonObject modelJson = NodeDelegateModel::save();

    modelJson["startDialogueId"] = _dialogueData->dialogueId();

    return modelJson;
}

void EndNodeDataModel::load(QJsonObject const &p)
{
    QJsonValue v = p["startDialogueId"];

    if (!v.isUndefined()) {
        QString dialogueId = v.toString();

        _dialogueData = std::make_shared<SimpleDialogueData>(dialogueId);

        if (_dialogueIdLineEdit)
            _dialogueIdLineEdit->setText(_dialogueData->dialogueId());

    }
}

unsigned int EndNodeDataModel::nPorts(PortType portType) const
{
    if(portType == PortType::In){
        return 1;
    }
    else{
        return 0;
    }
}

void EndNodeDataModel::onTextEdited(QString const &str)
{
    bool ok = true;

    //QString dialogueId = str.toStdString(&ok);

    if (ok) {
        _dialogueData = std::make_shared<SimpleDialogueData>(str);

        Q_EMIT dataUpdated(0);

    } else {
        Q_EMIT dataInvalidated(0);
    }
}

NodeDataType EndNodeDataModel::dataType(PortType, PortIndex) const
{
    return SimpleDialogueData().type();
}

std::shared_ptr<NodeData> EndNodeDataModel::outData(PortIndex)
{
    return _dialogueData;
}

QWidget *EndNodeDataModel::embeddedWidget()
{
    if (!_dialogueIdLineEdit && !_playDialogueButton) {

        _embeddedWidgetFrame = new QFrame();
        _embeddedWidgetFrame->setMaximumWidth(150);
        _embeddedWidgetLayout = new QVBoxLayout(_embeddedWidgetFrame);
        _embeddedWidgetLayout->setAlignment(Qt::AlignCenter);
        _embeddedWidgetLayout->setContentsMargins(5,5,5,5);
        _embeddedWidgetLayout->setSpacing(5);


        _dialogueIdLineEdit = new QLineEdit();
        //_dialogueIdLineEdit->setMaximumSize(_dialogueIdLineEdit->sizeHint());
        //connect(_dialogueIdLineEdit , &QLineEdit::textChanged, this, &EndNodeDataModel::onTextEdited);
        //_dialogueIdLineEdit->setText(_dialogueData->dialogueId());
        _dialogueIdLineEdit->setReadOnly(true);

        _playDialogueButton = new QPushButton();
        _playDialogueButton->setFlat(true);
        _playDialogueButton->setCursor(Qt::PointingHandCursor);
        _playDialogueButton->setIcon(QIcon(":/icons/assets/icons/playButton.png"));
        _playDialogueButton->setIconSize(QSize(32, 32)); // ikonun gerçek boyutu
        _playDialogueButton->setFixedSize(50, 50);       // butonun görünür alanı (dış çerçeve dahil)

        _playDialogueButton->setStyleSheet(R"(
            QPushButton {
                background-color: rgba(255, 255, 255, 20); /* Hafif arka plan */
                border: 1px solid rgba(255, 255, 255, 40);
                border-radius: 25px; /* Tam daire efekti */
            }
            QPushButton:hover {
                background-color: rgba(255, 255, 255, 60);
                border: 1px solid rgba(255, 255, 255, 90);
            }
            QPushButton:pressed {
                background-color: rgba(200, 200, 200, 100);
                border: 1px solid rgba(255, 255, 255, 120);
            }
        )");

        connect(_playDialogueButton, &QPushButton::clicked, this, [this](){
            Q_EMIT playDialogueButtonClicked();
        });

        _embeddedWidgetLayout->addWidget(_dialogueIdLineEdit, 0, Qt::AlignCenter);
        _embeddedWidgetLayout->addWidget(_playDialogueButton, 0, Qt::AlignCenter);
    }

    return _embeddedWidgetFrame;
}

void EndNodeDataModel::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
    auto dialogueData = std::dynamic_pointer_cast<SimpleDialogueData>(data);

    if (!data) {
        Q_EMIT dataInvalidated(0);
    }

    if(dialogueData != nullptr){
        _dialogueData = dialogueData;
        setDialogueId(dialogueData->dialogueId());
        std::cout << "End Node: " <<_dialogueData->dialogueSize() << std::endl;
    }
    else{
        setDialogueId("");
    }

    //setDialogueId(dialogueData->dialogueId());

    //if (portIndex == 0){
    //    _inputDialogue = dialogueData;
    //    _outputDialogue = std::make_shared<SimpleDialogueData>();
    //    //_outputDialogue = dialogueData;
    //    std::cout << "test" << std::endl;
    //}


    //compute();
}

void EndNodeDataModel::setDialogueId(const QString dialogueId)
{
    //_dialogueData = std::make_shared<SimpleDialogueData>(dialogueId);
    _dialogueIdLineEdit->setText(dialogueId);

    Q_EMIT dataUpdated(0);

    //if (_lineEdit)
    //    _lineEdit->setText(_dialogueData->dialogueId());
}

std::shared_ptr<SimpleDialogueData> EndNodeDataModel::getDialogue(){
    return _dialogueData;
}
