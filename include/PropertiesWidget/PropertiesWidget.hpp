#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>

class PropertiesWidget : public QWidget
{

Q_OBJECT

public:
PropertiesWidget(QWidget *parent)
    : QWidget(parent)
{
    QFrame *propertiesFrame = new QFrame(this);
    QVBoxLayout *propertiesLayout = new QVBoxLayout(propertiesFrame);
    propertiesLayout->setSpacing(0);
    propertiesLayout->setContentsMargins(0, 0, 0, 0);

    title = new QLabel(propertiesFrame);

    QGroupBox *editDialogueGroupBox = new QGroupBox(propertiesFrame);
    editDialogueGroupBox->setTitle("Edit Dialogue");

    QVBoxLayout *editDialogueLayout = new QVBoxLayout(editDialogueGroupBox);
    editDialogueLayout->setAlignment(Qt::AlignTop);
    editDialogueLayout->setSpacing(0);
    editDialogueLayout->setContentsMargins(5, 0, 5, 0);

    QPushButton *addNewDialogueButton = new QPushButton("Add new dialogue");

    QGroupBox *dialoguesGroupBox = new QGroupBox();
    dialoguesGroupBox->setTitle("Dialogues");
    dialoguesGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

    QScrollArea *dialoguesScrollArea = new QScrollArea();
    dialoguesScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    dialoguesScrollArea->setMinimumWidth(400);
    dialoguesScrollArea->setWidgetResizable(true);
    dialoguesScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    dialoguesScrollArea->setWidget(dialoguesGroupBox);

    QVBoxLayout *dialoguesLayout = new QVBoxLayout(dialoguesGroupBox);
    dialoguesLayout->setAlignment(Qt::AlignTop);
    dialoguesLayout->setSpacing(0);
    dialoguesLayout->setContentsMargins(5, 10, 5, 10);

    QLabel *placeholderLabel = new QLabel("    There are no any conversation.    ");
    placeholderLabel->setAlignment(Qt::AlignHCenter);

    dialoguesLayout->addWidget(placeholderLabel);
    dialoguesLayout->addStretch(1);

    editDialogueLayout->addWidget(addNewDialogueButton);
    editDialogueLayout->addWidget(dialoguesScrollArea);

    propertiesLayout->addWidget(title);
    propertiesLayout->addWidget(editDialogueGroupBox);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(propertiesFrame);

    connect(addNewDialogueButton, &QPushButton::clicked, this, [this, dialoguesLayout, placeholderLabel]() {
        addNewDialogueWidget(dialoguesLayout, placeholderLabel);
    });
}

//void setDialogueId(const QString dialogueId) const{
//    title->setText(dialogueId);
//}

void setDialogueTitle(QString title_){
    title->setText(title_);
}

private:
    QLabel *title;


private slots:

    void addNewDialogueWidget(QVBoxLayout *layout, QLabel *placeholderLabel){

        // İlk ekleme durumunda placeholder'ı gizle
        if (placeholderLabel->isVisible()) {
            placeholderLabel->setVisible(false);
        }

        static int dialogueOrder = 0;
        dialogueOrder++;

        QGroupBox *dialogueGroupBox = new QGroupBox(QString::number(dialogueOrder));
        dialogueGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        QVBoxLayout *dialogueLayout = new QVBoxLayout(dialogueGroupBox);
        dialogueLayout->setAlignment(Qt::AlignTop);
        dialogueLayout->setSpacing(5);
        dialogueLayout->setContentsMargins(5, 0, 5, 5);

        QFrame *dialogueCharacterFrame = new QFrame();
        QLabel *dialogueCharacterLabel = new QLabel("Character:");
        QLineEdit *dialogueCharacterEdit = new QLineEdit();

        QHBoxLayout *characterEditLayout = new QHBoxLayout(dialogueCharacterFrame);
        characterEditLayout->setAlignment(Qt::AlignTop);
        characterEditLayout->setSpacing(0);
        characterEditLayout->setContentsMargins(0, 0, 0, 0);
        characterEditLayout->addWidget(dialogueCharacterLabel);
        characterEditLayout->addWidget(dialogueCharacterEdit);

        QFrame *dialogueContentFrame = new QFrame();
        QLabel *dialogueContentLabel = new QLabel("  Content:");
        QTextEdit *dialogueContentEdit = new QTextEdit();
        dialogueContentEdit->setFixedHeight(50);

        QHBoxLayout *contentEditLayout = new QHBoxLayout(dialogueContentFrame);
        contentEditLayout->setAlignment(Qt::AlignTop);
        contentEditLayout->setSpacing(0);
        contentEditLayout->setContentsMargins(0, 0, 0, 0);
        contentEditLayout->addWidget(dialogueContentLabel);
        contentEditLayout->addWidget(dialogueContentEdit);

        QFrame *dialogueFeaturesFrame = new QFrame();
        QPushButton *addAvatarButton = new QPushButton("Add avatar");
        QPushButton *addAudioFileButton = new QPushButton("Add audio file");
        QPushButton *removeDialogueButton = new QPushButton("Remove dialogue");

        QHBoxLayout *dialogueFeaturesLayout = new QHBoxLayout(dialogueFeaturesFrame);
        dialogueFeaturesLayout->setAlignment(Qt::AlignTop);
        dialogueFeaturesLayout->setSpacing(0);
        dialogueFeaturesLayout->setContentsMargins(0, 0, 0, 0);
        dialogueFeaturesLayout->addWidget(addAvatarButton);
        dialogueFeaturesLayout->addWidget(addAudioFileButton);
        dialogueFeaturesLayout->addWidget(removeDialogueButton);

        QFrame *dialogueFeatureViewsFrame = new QFrame();

        QFrame *avatarFrame = new QFrame();
        QLabel *avatarLabel = new QLabel("Avatar:");
        QLabel *avatarImageView = new QLabel();
        avatarImageView->setAlignment(Qt::AlignCenter); // İçeriği ortala
        avatarImageView->setMinimumSize(50, 50); // Minimum boyut
        avatarImageView->setMaximumSize(50,50);
        avatarImageView->setScaledContents(true);
        avatarImageView->setCursor(Qt::PointingHandCursor);
        avatarImageView->setMouseTracking(true);
        avatarImageView->installEventFilter(this);

        QPixmap pixmap(":/avatars/avatar.png");
        if (!pixmap.isNull())
            avatarImageView->setPixmap(pixmap);

        QHBoxLayout *avatarLayout = new QHBoxLayout(avatarFrame);
        avatarLayout->setAlignment(Qt::AlignLeft);
        avatarLayout->addWidget(avatarLabel);
        avatarLayout->addWidget(avatarImageView);

        QFrame *audioFileFrame = new QFrame();
        QLabel *audioFileLabel = new QLabel("Audio File:");
        QPushButton *audioFilePlayButton = new QPushButton("Play");
        audioFileLabel->setMinimumSize(50, 50);
        avatarImageView->setMaximumSize(50,50);

        QHBoxLayout *audioFileLayout = new QHBoxLayout(audioFileFrame);
        audioFileLayout->setAlignment(Qt::AlignRight);
        audioFileLayout->addWidget(audioFileLabel);
        audioFileLayout->addWidget(audioFilePlayButton);

        QHBoxLayout *dialogueFeatureViewsLayout = new QHBoxLayout(dialogueFeatureViewsFrame);
        dialogueFeatureViewsLayout->setAlignment(Qt::AlignTop);
        dialogueFeatureViewsLayout->setSpacing(0);
        dialogueFeatureViewsLayout->setContentsMargins(0, 0, 0, 0);
        dialogueFeatureViewsLayout->addWidget(avatarFrame);
        dialogueFeatureViewsLayout->addWidget(audioFileFrame);

        dialogueLayout->addWidget(dialogueFeatureViewsFrame);
        dialogueLayout->addWidget(dialogueCharacterFrame);
        dialogueLayout->addWidget(dialogueContentFrame);
        dialogueLayout->addWidget(dialogueFeaturesFrame);

        // Widgetı en üstte ekliyoruz, stretch öğesinden önce
        int index = layout->count() - 1;
        layout->insertWidget(index, dialogueGroupBox);
    }

};
