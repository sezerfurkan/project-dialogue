#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, registry(std::make_shared<NodeDelegateModelRegistry>())
{
    this->setWindowTitle("[*]Game Dialogue System");
    this->resize(800, 600);

    this->initNodeViewWidget();
    this->initMenuBarWidget();
    this->initComponentsDockWidget();
    this->initPropertiesDockWidget();


}

void MainWindow::initNodeViewWidget(){
    registry->registerModel<NumberSourceDataModel>("Sources");
    registry->registerModel<NumberDisplayDataModel>("Displays");
    registry->registerModel<AdditionModel>("Operators");
    registry->registerModel<SubtractionModel>("Operators");
    registry->registerModel<MultiplicationModel>("Operators");
    registry->registerModel<DivisionModel>("Operators");
    registry->registerModel<StartNodeDataModel>("Dialogue Nodes");
    registry->registerModel<SimpleNodeModel>("Dialogue Nodes");


    dataFlowGraphModel = new DataFlowGraphModel(registry);

    scene = new DataFlowGraphicsScene(*dataFlowGraphModel, this);
    view = new GraphicsView(scene);

    QWidget *nodeViewWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(nodeViewWidget);
    layout->addWidget(view);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    this->setCentralWidget(nodeViewWidget);
}

void MainWindow::initMenuBarWidget(){
    auto menuBar = new QMenuBar();
    QMenu *menu = menuBar->addMenu("File");

    auto saveAction = menu->addAction("Save Scene");
    saveAction->setShortcut(QKeySequence::Save);

    auto loadAction = menu->addAction("Load Scene");
    loadAction->setShortcut(QKeySequence::Open);


    this->connect(saveAction, &QAction::triggered, scene, [this]() {
        if (scene->save())
            this->setWindowModified(false);
    });

    this->connect(loadAction, &QAction::triggered, scene, &DataFlowGraphicsScene::load);

    this->setMenuBar(menuBar);
}

void MainWindow::initComponentsDockWidget(){
    QDockWidget *dockWidget = new QDockWidget("Components", this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QFrame *componentsFrame = new QFrame(dockWidget);

    QVBoxLayout *componentsLayout = new QVBoxLayout(componentsFrame);
    componentsLayout->setSpacing(0);
    componentsLayout->setContentsMargins(0, 0, 0, 0);

    QGroupBox *dialogueComponentsGroupBox = new QGroupBox(dockWidget);
    dialogueComponentsGroupBox->setTitle("Dialogue Components");

    QVBoxLayout *dialogueComponentsLayout = new QVBoxLayout(dialogueComponentsGroupBox);
    dialogueComponentsLayout->setAlignment(Qt::AlignTop);
    dialogueComponentsLayout->setSpacing(0);
    dialogueComponentsLayout->setContentsMargins(5, 0, 5, 0);

    QPushButton *startNodeButton = new QPushButton();
    startNodeButton->setText("Start Node");

    QPushButton *simpleNodeButton = new QPushButton();
    simpleNodeButton->setText("Simple Node");

    QPushButton *multipleChoiceNodeButton = new QPushButton();
    multipleChoiceNodeButton->setText("Multiple Choice Node");

    QPushButton *endNodeButton = new QPushButton();
    endNodeButton->setText("End Node");

    dialogueComponentsLayout->addWidget(startNodeButton);
    dialogueComponentsLayout->addWidget(simpleNodeButton);
    dialogueComponentsLayout->addWidget(multipleChoiceNodeButton);
    dialogueComponentsLayout->addWidget(endNodeButton);

    QGroupBox *otherComponentsGroupBox = new QGroupBox(dockWidget);
    otherComponentsGroupBox->setTitle("Other Components");

    QVBoxLayout *otherComponentsLayout = new QVBoxLayout(otherComponentsGroupBox);
    otherComponentsLayout->setAlignment(Qt::AlignTop);
    otherComponentsLayout->setSpacing(0);
    otherComponentsLayout->setContentsMargins(5, 0, 5, 0);

    QPushButton *commentButton = new QPushButton();
    commentButton->setText("Comment");

    otherComponentsLayout->addWidget(commentButton);

    componentsLayout->addWidget(dialogueComponentsGroupBox);
    componentsLayout->addWidget(otherComponentsGroupBox);
    dockWidget->setWidget(componentsFrame);

    this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
}

void MainWindow::initPropertiesDockWidget(){
    QDockWidget *dockWidget = new QDockWidget("Properties", this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    PropertiesWidget *propertiesWidget = new PropertiesWidget(dockWidget);

    this->connect(dataFlowGraphModel, &DataFlowGraphModel::nodeCreated,
                  this, [this, propertiesWidget, dockWidget](QtNodes::NodeId nodeId) {

        SimpleNodeModel *simpleNodeModel = dynamic_cast<SimpleNodeModel*>
            (dataFlowGraphModel->delegateModel<NodeDelegateModel>(nodeId));

        if(simpleNodeModel != nullptr){

            connect(simpleNodeModel, &SimpleNodeDataModel::dataUpdated,
                    this, [this, propertiesWidget, simpleNodeModel](PortIndex portIndex){

                if (simpleNodeModel->getInputDialogue().lock() && propertiesWidget->dialogueTitle().isEmpty()){
                    propertiesWidget->setDialogueTitle(simpleNodeModel->getInputDialogue().lock()->dialogueId());
                    propertiesWidget->initDialogueMemory(simpleNodeModel->getInputDialogue().lock()->dialogueId());
                }

            });

            connect(simpleNodeModel, &SimpleNodeDataModel::buttonClicked, this, [this, dockWidget, propertiesWidget, simpleNodeModel](){
                if (simpleNodeModel->getInputDialogue().lock()){
                    propertiesWidget->setDialogueTitle(simpleNodeModel->getInputDialogue().lock()->dialogueId());
                    propertiesWidget->loadDialogueMemory(simpleNodeModel->getInputDialogue().lock()->dialogueId());
                }

                dockWidget->setVisible(true);
            });
        }
    });

    dockWidget->setWidget(propertiesWidget);

    dockWidget->setVisible(false);

    this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
}


