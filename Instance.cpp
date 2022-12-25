#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "XmlUtil.h"

namespace Netlist {

  Instance::Instance      ( Cell* owner, Cell* model, const std::string& name):owner_(owner),masterCell_(model),name_(name),terms_()
  {
    if(model!=NULL)
      for(Term* term : model->getTerms())
        new Term(this, term);

    owner->add(this);
  }

  Instance::~Instance      ()
  {
    owner_->remove(this);
    masterCell_->remove(this);
    owner_=NULL;
    masterCell_=NULL;
    for(size_t i=0; i<terms_.size(); ++i){
      delete terms_[i];
    }
  }
  
  const std::string&        Instance::getName       () const{return name_;}
  Cell*                     Instance::getMasterCell () const{return masterCell_;}
  Cell*                     Instance::getCell       () const{return owner_;}
  const std::vector<Term*>& Instance::getTerms      () const{return terms_;}
  Point                     Instance::getPosition   () const{return position_;}
  
  Term*                     Instance::getTerm       ( const std::string& name ) const{
    for(std::vector<Term*>::const_iterator it=terms_.begin(); it!=terms_.end(); ++it)
      if((*it)->getName()==name)
        return *it;
    return NULL;
  }
  
  bool  Instance::connect       ( const std::string& name, Net* n ){
    Term* term=getTerm(name);
    if(term==NULL)
      return false;
    term->setNet(n);
    return true;
  }
  void  Instance::add           ( Term* t){
    if(t!=NULL)
      terms_.push_back(t);
  }
  void  Instance::remove        ( Term* t){
    for(std::vector<Term*>::iterator it=terms_.begin(); it!=terms_.end(); ++it)
      if(*it==t){
        terms_.erase(it);
        break;
      }
  }
  void  Instance::setPosition   ( const Point& p){
    position_=p;
    for(std::vector<Term*>::iterator it=terms_.begin(); it!=terms_.end(); ++it)
    	(*it)->setPosition((*it)->getPosition().translate(p));
  }
  void  Instance::setPosition   ( int x, int y ){
    position_=position_.setX(x).setY(y);
  }
  
  void  Instance::toXml ( std::ostream& stream ) const{
     stream << "<instance name=\"" << name_ << "\" mastercell=\"" << masterCell_->getName() << "\" x=\"" << position_.getX() << "\" y=\"" << position_.getY() << "\" />" << std::endl;
  }
  
  Instance* Instance::fromXml ( Cell* cell, xmlTextReaderPtr reader ){
    Instance* inst = NULL;
    while ( true ) {
      switch ( xmlTextReaderNodeType(reader) ){
        case  XML_READER_TYPE_COMMENT:
        case  XML_READER_TYPE_WHITESPACE:
        case  XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
          continue;
      }

      std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
      
      Cell* mastercell = Cell::find( xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell" ) ) );

      int x, y;
      bool bx = xmlGetIntAttribute(reader, "x", &x);
      bool by = xmlGetIntAttribute(reader, "y", &y);
      
      if(!bx || !by){
        std::cerr << "ERROR IN INSTANCE" << std::endl;
        return NULL;
      }
        
      inst = new Instance(cell, mastercell, name);
      inst->setPosition(x, y);
    }
    return inst;
  }
}
