#include "CellViewer.h"
#include "CellWidget.h"
#include "SaveCellDialog.h"
#include "Cell.h"

namespace Netlist{

	CellViewer::CellViewer (QWidget* parent)
		: QMainWindow (parent), cellWidget_ (NULL), saveCellDialog_ (NULL){
		cellWidget_ = new CellWidget();
		saveCellWidget_ = new SaveCellDialog(this);
		setCentralWidget( cellWidget_ );

		QMenu * fileMenu = menuBar() -> addMenu("&File");
		QAction* action = new QAction("Save as",this);
		action->setStatusTip( "Save to disk");
		action->setShortcut( QKeySequence("CTRL+S"));
		action -> setVisible(true);
		fileMenu->addAction(action);
		connect(action, SIGNAL(triggered()), this , SLOT(saveCell()));

		action = new QAction("&Open",this);
		action->setStatusTip( "Save to disk");
		action->setShortcut( QKeySequence("MAJ+CTRL+O"));
		action -> setVisible(true);
		fileMenu->addAction(action);
		connect(action, SIGNAL(triggered()), this , SLOT(openCell()));

		action = new QAction("&Show Ins",this);
		action->setStatusTip( "Show instances");
		action->setShortcut( QKeySequence("ALT+CTRL+S"));
		action -> setVisible(true);
		fileMenu->addAction(action);
		connect(action, SIGNAL(triggered()), this , SLOT(showInstancesWidget()));

		action = new QAction("Show Lib",this);
		action->setStatusTip( "Show cells library");
		action->setShortcut( QKeySequence("MAJ+CTRL+S"));
		action -> setVisible(true);
		fileMenu->addAction(action);
		connect(action, SIGNAL(triggered()), this , SLOT(showCellsLib()));

		action = new QAction("&Quit",this);
		action->setStatusTip( "Exit the Viewer");
		action->setShortcut( QKeySequence("CTRL+Q"));
		action -> setVisible(true);
		fileMenu->addAction(action);
		connect(action, SIGNAL(triggered()), this , SLOT(close()));

	}

	Cell* CellViewer::getCell(){
		return cellWidget_->getCell();
	}

	void CellViewer::saveCell(){
		Cell* cell= getCell();
		if(cell==NULL) return;

		QString cname= cell->getName().c_str();


		if(saveCellDialog_->run(cname)){
			cell->setName(cname.toStdString());
			cell->save(cname.toStdString());
		}
	}

	void      CellViewer::setCell( Cell* c){
		if(c){
			cellWidget_->setCell(c);
			cellLib_->baseModel_->setCell(c);
			instanceWidget_->setCell(c);
		}
	}

	void      CellViewer::openCell            (){
		Cell* cell= NULL;
		QString name = NULL;

		if(openCellDialog_->run(name)){
			std::string cname=name.toStdString();
			if(!cname) return;

			setCell( Cell::load(cname) );
		}
	}

	void      CellViewer::showCellsLib        (){
		std::vector<Cell*> cells= Cell::getAllCells();

		if(cells==NULL) return;



	}
	void      CellViewer::showInstancesWidget (){

	}
}
