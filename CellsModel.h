#ifndef CELLSMODEL_H_
#define CELLSMODEL_H_

#include <QAbstractTableModel>

class CellsModel : public QAbstractTableModel {
    Q_OBJECT;
  public:
             CellsModel ( QObject* parent=NULL );
            ~CellsModel ();
    void     setCell        ( Cell* );
    inline 	 Cell*    	getCell       ( );
    int      rowCount       ( const QModelIndex& parent = QModelIndex );
    int      ColumnCount    ( const QModelIndex& parent = QModelIndex );
    QVariant data           ( const QModelIndex& index, int role = 0 );
    QVariant headerData     ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
  private:
    std::vector<Cell*>& cells_;
};



#endif /* CELLSMODEL_H_ */
