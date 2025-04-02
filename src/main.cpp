#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>

#include <QMainWindow>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>

#include <QtGui/QScreen>

#include "AdditionModel.hpp"
#include "DivisionModel.hpp"
#include "MultiplicationModel.hpp"
#include "NumberDisplayDataModel.hpp"
#include "NumberSourceDataModel.hpp"
#include "SubtractionModel.hpp"

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

//using QtNodes::ConnectionStyle;
//using QtNodes::DataFlowGraphicsScene;
//using QtNodes::DataFlowGraphModel;
//using QtNodes::GraphicsView;
//using QtNodes::NodeDelegateModelRegistry;
//
//static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
//{
//    auto ret = std::make_shared<NodeDelegateModelRegistry>();
//    ret->registerModel<NumberSourceDataModel>("Sources");
//
//    ret->registerModel<NumberDisplayDataModel>("Displays");
//
//    ret->registerModel<AdditionModel>("Operators");
//
//    ret->registerModel<SubtractionModel>("Operators");
//
//    ret->registerModel<MultiplicationModel>("Operators");
//
//    ret->registerModel<DivisionModel>("Operators");
//
//    return ret;
//}
//
//static void setStyle()
//{
//    ConnectionStyle::setConnectionStyle(
//        R"(
//  {
//    "ConnectionStyle": {
//      "ConstructionColor": "gray",
//      "NormalColor": "black",
//      "SelectedColor": "gray",
//      "SelectedHaloColor": "deepskyblue",
//      "HoveredColor": "deepskyblue",
//
//      "LineWidth": 3.0,
//      "ConstructionLineWidth": 2.0,
//      "PointDiameter": 10.0,
//
//      "UseDataDefinedColors": true
//    }
//  }
//  )");
//}
//
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//
//    setStyle();
//
//    std::shared_ptr<NodeDelegateModelRegistry> registry = registerDataModels();
//
//    QMainWindow mainWindow;
//
//    auto menuBar = new QMenuBar();
//    QMenu *menu = menuBar->addMenu("File");
//
//    auto saveAction = menu->addAction("Save Scene");
//    saveAction->setShortcut(QKeySequence::Save);
//
//    auto loadAction = menu->addAction("Load Scene");
//    loadAction->setShortcut(QKeySequence::Open);
//
//    DataFlowGraphModel dataFlowGraphModel(registry);
//
//    auto scene = new DataFlowGraphicsScene(dataFlowGraphModel, &mainWindow);
//
//    auto view = new GraphicsView(scene);
//
//    QWidget *centralWidget = new QWidget();
//    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
//
//    layout->addWidget(view);
//    layout->setContentsMargins(0, 0, 0, 0);
//    layout->setSpacing(0);
//
//    mainWindow.setMenuBar(menuBar);
//    mainWindow.setCentralWidget(centralWidget);
//
//    QDockWidget *dockWidget = new QDockWidget("Components", &mainWindow);
//    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//
//    QFrame *componentsFrame = new QFrame(dockWidget);
//
//    QVBoxLayout *componentsLayout = new QVBoxLayout(componentsFrame);
//    componentsLayout->setSpacing(0);
//    componentsLayout->setContentsMargins(0, 0, 0, 0);
//
//    QGroupBox *dialogueComponentsGroupBox = new QGroupBox(dockWidget);
//    dialogueComponentsGroupBox->setTitle("Dialogue Components");
//
//    QVBoxLayout *dialogueComponentsLayout = new QVBoxLayout(dialogueComponentsGroupBox);
//    dialogueComponentsLayout->setAlignment(Qt::AlignTop);
//    dialogueComponentsLayout->setSpacing(0);
//    dialogueComponentsLayout->setContentsMargins(5, 0, 5, 0);
//
//    QPushButton *startNodeButton = new QPushButton();
//    startNodeButton->setText("Start Node");
//
//    QPushButton *simpleNodeButton = new QPushButton();
//    simpleNodeButton->setText("Simple Node");
//
//    QPushButton *multipleChoiceNodeButton = new QPushButton();
//    multipleChoiceNodeButton->setText("Multiple Choice Node");
//
//    QPushButton *endNodeButton = new QPushButton();
//    endNodeButton->setText("End Node");
//
//    dialogueComponentsLayout->addWidget(startNodeButton);
//    dialogueComponentsLayout->addWidget(simpleNodeButton);
//    dialogueComponentsLayout->addWidget(multipleChoiceNodeButton);
//    dialogueComponentsLayout->addWidget(endNodeButton);
//
//    QGroupBox *otherComponentsGroupBox = new QGroupBox(dockWidget);
//    otherComponentsGroupBox->setTitle("Other Components");
//
//    QVBoxLayout *otherComponentsLayout = new QVBoxLayout(otherComponentsGroupBox);
//    otherComponentsLayout->setAlignment(Qt::AlignTop);
//    otherComponentsLayout->setSpacing(0);
//    otherComponentsLayout->setContentsMargins(5, 0, 5, 0);
//
//    QPushButton *commentButton = new QPushButton();
//    commentButton->setText("Comment");
//
//    otherComponentsLayout->addWidget(commentButton);
//
//    //QListWidget *listWidget = new QListWidget();
//    //listWidget->addItem("Start Node");
//    //listWidget->addItem("Simple Node");
//    //listWidget->addItem("Multiple Choice Node");
//    //listWidget->addItem("End Node");
//    //dockWidget->setWidget(listWidget);
//    componentsLayout->addWidget(dialogueComponentsGroupBox);
//    componentsLayout->addWidget(otherComponentsGroupBox);
//    dockWidget->setWidget(componentsFrame);
//
//    mainWindow.addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
//
//    QObject::connect(saveAction, &QAction::triggered, scene, [scene, &mainWindow]() {
//        if (scene->save())
//            mainWindow.setWindowModified(false);
//    });
//
//    QObject::connect(loadAction, &QAction::triggered, scene, &DataFlowGraphicsScene::load);
//
//    QObject::connect(scene, &DataFlowGraphicsScene::sceneLoaded, view, &GraphicsView::centerScene);
//
//    QObject::connect(scene, &DataFlowGraphicsScene::modified, &mainWindow, [&mainWindow]() {
//        mainWindow.setWindowModified(true);
//    });
//
//    mainWindow.setWindowTitle("[*]Data Flow: simplest calculator");
//    mainWindow.resize(800, 600);
//    // Center window.
//    mainWindow.move(QApplication::primaryScreen()->availableGeometry().center()
//                    - mainWindow.rect().center());
//    mainWindow.showNormal();
//
//    return app.exec();
//}
