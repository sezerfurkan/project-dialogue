#pragma once

#include <QMainWindow>
#include <QFrame>
#include <QVBoxLayout>
#include <QtWidgets/QLabel>

#include "SimpleDialogueData.hpp"
#include "DialogueData.hpp"

class PlayDialogueWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayDialogueWindow(QWidget *parent = nullptr);

    void setDialogueData(std::shared_ptr<SimpleDialogueData> dialogueData);
    void advanceTheDialogue();



protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    std::shared_ptr<SimpleDialogueData> _dialogueData;

    QFrame *_dialogueFrame;
    QVBoxLayout *_dialogueLayout;
    QLabel *_informationLabel;
    QLabel *_characterNameLabel;
    QLabel *_messageLabel;
};

