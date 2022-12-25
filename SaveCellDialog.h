#ifndef NETLIST_SAVECELLDIALOG_H
#define NETLIST_SAVECELLDIALOG_H

#include <QDialog>

class SaveCellDialog : public QDialog{
  Q_OBJECT;
  public:
                  SaveCellDialog( QWidget* parent );
    const QString getCellName   () const;
    void          setCellName   ( const QString& name );
    bool          run           ( QString& name );
  protected:
    QLineEdit* lineEdit_;
};

#endif  // NETLIST_SAVECELLDIALOG_H
