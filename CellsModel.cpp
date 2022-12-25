#include "CellsModel.h"
#include "Cell.h"

namespace Netlist{
	using namespace std;

	CellsModel::CellsModel ( QObject* parent=nullptr )
	:QAbstractTableModel(parent)
	,cell_(nullptr)
	{}

	CellsModel::~CellsModel (){}

	void     CellsModel::setCell        ( Cell* cell ){
	  emit layoutAboutToBeChanged();
	  cells_ = cell;
	  emit layoutChanged();
	}

	inline Cell*    CellsModel::getCell       ( int row ){
	  if( not cells_ ) return nullptr;
	  if( row >= (int)cells_.size() ) return nullptr;

	  return cells_[row];
	}

	int      CellsModel::rowCount       ( const QModelIndex& parent ){
	  return (cells_) ? cells_.size() : 0;
	}

	int      CellsModel::ColumnCount    ( const QModelIndex& parent ){
	  return 2;
	}

	QVariant CellsModel::data           ( const QModelIndex& index, int role ){
	  if(not cells_ or not index.isValid()) return QVariant();
	  if(role == Qt::DisplayRole){
		  int row = index.row();
		  	 return cells_[row]->getName().c_str();
	  }
	  return QVariant();
	}
	QVariant CellsModel::headerData     ( int section, Qt::Orientation orientation, int role ) const{
	  return QVariant();
	}
}





