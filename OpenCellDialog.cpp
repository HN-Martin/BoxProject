#include "OpenCellDialog.h"

OpenCellDialog::OpenCellDialog( QWidget* parent )
:QDialog(parent)
,lineEdit_(NULL)
{
  SetWindowTitle( tr("Open Cell") );
  
  QLabel* label = new QLabel();
  label->setText( tr("Enter Cell Name (Without Extension)") );
  
  lineEdit_ = new QLineEdit();
  lineEdit_->setMinimumWidth( 400 );
  
  QPushButton* okButton = new QPushButton();
  okButton->setText( "OK" );
  okButton->setDefault( true );
  
  QPushButton* cancelButton = new QPushButton();
  cancelButton->setText( "Cancel" );
  
  QHBoxLayout* hLayout = new QHBoxLayout();
  hLayout->addstretch();
  hLayout->addWidget( okButton );
  hLayout->addstretch();
  hLayout->addWidget( cancelButton );
  hLayout->addstretch();
  QFrame* separator = new QFrame();
  separator->setFrameShape( QFrame::HLine );
  separator->setFrameShadow( QFrame::Sunken );
  QVBoxLayout* vLayout = new QVBoxLayout();
  vlayout->setSizeConstraint( QLayout::SetFixedSize );
  vlayout->addWidget( label );
  vlayout->addWidget( lineEdit_ );
  vlayout->addLayout( hlayout );
  setLayout( vlayout );
  
  connect( okButton, SIGNAL(clicked()), this, SLOT(accept()) );
  connect( cancelButton, SIGNAL(clicked()), this, SLOT(reject()) );
}

const QString OpenCellDialog::getCellName() const{
  return lineEdit_->text();
}

bool OpenCellDialog::run( QString& name ){
  int dialogResult = exec();
  name = getCellName();
  return dialogResult == Accepted;
}
