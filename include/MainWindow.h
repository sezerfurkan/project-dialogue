#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNodes/ConnectionStyle>
#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModelRegistry>

#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QSizePolicy>

#include <QtGui/QScreen>
#include <QMainWindow>

#include <PropertiesWidget/PropertiesWidget.hpp>

#include "AdditionModel.hpp"
#include "DivisionModel.hpp"
#include "MultiplicationModel.hpp"
#include "NumberDisplayDataModel.hpp"
#include "NumberSourceDataModel.hpp"
#include "SubtractionModel.hpp"

#include "StartNodeDataModel.hpp"
#include "SimpleNodeModel.hpp"

using QtNodes::ConnectionStyle;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::DataFlowGraphModel;
using QtNodes::GraphicsView;
using QtNodes::NodeDelegateModelRegistry;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


private:

    std::shared_ptr<NodeDelegateModelRegistry> registry;
    DataFlowGraphModel *dataFlowGraphModel;
    DataFlowGraphicsScene *scene;
    GraphicsView *view;

    void initMenuBarWidget();
    void initComponentsDockWidget();
    void initPropertiesDockWidget();
    void initNodeViewWidget();


signals:

};

#endif // MAINWINDOW_H
