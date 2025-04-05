#include "PlayDialogueWindow.hpp"
#include <QLabel>
#include <QVBoxLayout>

PlayDialogueWindow::PlayDialogueWindow(QWidget *parent)
    : QMainWindow(parent), _dialogueData(std::make_shared<SimpleDialogueData>())
{
    setWindowTitle("Play Dialogue");
    resize(800, 600);

    _dialogueFrame = new QFrame();
    _dialogueLayout = new QVBoxLayout(_dialogueFrame);
    _dialogueLayout->setAlignment(Qt::AlignCenter);
    _dialogueLayout->setContentsMargins(0, 0, 0, 0);
    _dialogueLayout->setSpacing(10);

    //_informationLabel = new QLabel("Diyaloğu ilerletmek için tıklayın!", this);
    //_informationLabel->setAlignment(Qt::AlignTop);

    QFont font;
    font.setFamily("Arial");   // Font tipi
    font.setPointSize(20);     // Font boyutu (point cinsinden)
    font.setBold(true);        // İsteğe bağlı: kalın yap

    _characterNameLabel = new QLabel("Martin", this);
    _characterNameLabel->setFont(font);
    _messageLabel = new QLabel("Merhaba, nasılsın dostum?", this);
    _messageLabel->setFont(font);

    _dialogueLayout->addWidget(_characterNameLabel);
    _dialogueLayout->addWidget(_messageLabel);

    // Bu çok önemli: İçeriği göstermek için setCentralWidget çağırmalısın
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    //layout->addWidget(_informationLabel, Qt::AlignTop);
    layout->addWidget(_dialogueFrame, Qt::AlignCenter);

}

void PlayDialogueWindow::mousePressEvent(QMouseEvent *event)
{
    advanceTheDialogue();
}

void PlayDialogueWindow::setDialogueData(std::shared_ptr<SimpleDialogueData> dialogueData){
    _dialogueData = dialogueData;
}


void PlayDialogueWindow::advanceTheDialogue(){
    static int dialogueOrder = 0;
    static bool advance = true;

    if(advance){
        if(dialogueOrder < _dialogueData->dialogueSize()){
            QString dialogueId = _dialogueData->dialogueId();
            DialogueData* dialogue = _dialogueData->dialogueChain()[dialogueOrder];

            _characterNameLabel->setText(dialogue->characterName());
            _messageLabel->setText(dialogue->message());

            dialogueOrder++;
        }
        else{
            qDebug() << "Dialogue finished";
            _characterNameLabel->setText("");
            _messageLabel->setText("THE END");
            advance = false;
        }
    }


}
