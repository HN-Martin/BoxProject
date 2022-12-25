#ifndef NETLIST_OPENCELLDIALOG_H
#define NETLIST_OPENCELLDIALOG_H

#include <QDialog>

class OpenCellDialog : public QDialog{
  Q_OBJECT;
  public:
                  OpenCellDialog( QWidget* parent );
    const QString getCellName   () const;
    bool          run           ( QString& name );
  protected:
    QLineEdit* lineEdit_;
};

#endif  // NETLIST_OPENCELLDIALOG_H
