#include "CellViewer.h"
#include "CellWidget.h"
#include "CellsLib.h"
#include "SaveCellDialog.h"
#include "Cell.h"



namespace Netlist{

	CellsLib::CellsLib( QWidget* parent ):
		QWidget(parent)
		,cellviewer_(NULL)
		,basemodel_(new InstancesModel(this))
		,view_(new QTableView(this))
		,load_(new QPushButton(this))
	{
	  setAttribute( Qt::WA_QuitOnClose, false);
	  setAttribute( Qt::WA_DeleteOnClose, false);
	  SetContextMenuPolicy( Qt::ActionsContextMenu );

	  view_->setShowGrid( false );
	  view_->setAlternatingRowColors( true );
	  view_->setSelectionBehavior( QAbstractItemView::SelectRows );
	  view_->setSelectionMode( QAbstractItemView::SingleSelection );
	  view_->setSortingEnabled( true );
	  view_->setModel( baseModel_ );

	  QHeaderView* horizontalHeader = view_->horizontalHeader();
	  horizontalHeader->setDefaultAlignment( Qt::AlignHCenter );
	  horizontalHeader->setMinimumSectionSize( 300 );
	  horizontalHeader->setStretchLastSection( true );

	  QHeaderView* verticalHeader = view_->verticalHeader();
	  verticalHeader->setVisible( false );

	  load_->setText( "Load" );
	  connect( load_, SIGNAL(clicked()), this, SLOT(load()) );
	}

	void  CellsLib::setCellViewer   ( CellViewer* cellViewer ){
	  emit layoutAboutToBeChanged();
	  cellViewer_ = cellViewer;
	  emit layoutChanged();
	}

	int   CellsLib::getSelectedRow  () const{
	  QModelIndexList selecteds = view_->selectionModel()->selection().indexes();
	  if(selecteds.empty()) return -1;
	  return selecteds.first().row();
	}

	void  CellsLib::load            (){
	  int selectedRow = getSelectedRow();
	  if(selectedRow < 0) return;
	  cellViewer_->setCell( baseModel_->getModel(selectedRow) );
	}
}
