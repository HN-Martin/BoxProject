#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "XmlUtil.h"

namespace Netlist {
  std::string Term::toString ( Term::Type t ){
    switch(t){
      case Term::Internal :
        return std::string{"Internal"};
      case Term::External :
        return std::string{"External"};
    }
    return NULL;
  }
  std::string Term::toString ( Term::Direction d ){
    switch(d){
      case Term::In :
        return std::string{"In"};
      case Term::Out :
        return std::string{"Out"};
      case Term::Inout :
        return std::string{"Inout"};
      case Term::Tristate :
        return std::string{"Tristate"};
      case Term::Transcv :
        return std::string{"Transcv"};
      default :
        return std::string{"Unknown"};
    }
  }
  Term::Type Term::toType ( std::string s ){
    if(std::string{"Internal"}.compare(s) == 0 )
      return Term::Internal;
    return External;
  }
  Term::Direction Term::toDirection ( std::string s ){
    if(      std::string{"In"}.compare(s) == 0 )
      return Term::In;
    if(     std::string{"Out"}.compare(s) == 0 )
      return Term::Out;
    if(   std::string{"Inout"}.compare(s) == 0 )
      return Term::Inout;
    if(std::string{"Tristate"}.compare(s) == 0 )
      return Term::Tristate;
    if( std::string{"Transcv"}.compare(s) == 0 )
      return Term::Transcv;
    return Term::Unknown;
  }
    
  Term::Term ( Cell*    c, const std::string& name, Direction d):owner_(c),name_(name),direction_(d),type_(External),net_(c->getNet(name)),node_(this)
  {
    c->add(this);
  }
  Term::Term ( Instance* i, const Term* modelTerm ):owner_(i),name_(modelTerm->name_),direction_(modelTerm->direction_),type_(Internal),net_(i->getCell()->getNet(modelTerm->name_)),node_(this)
  {
    i->add(this);
  }
  Term::~Term ()
  {
    if(type_==Internal)
      static_cast<Instance*>(owner_)->remove(this);
    else
      static_cast<Cell*>(owner_)->remove(this);
    owner_=NULL;
    net_->remove(getNode());
    net_=NULL;
  }
  
  inline Cell* Term::getOwnerCell () const{return (type_==Internal)? (static_cast<Instance*>(owner_))->getCell():static_cast<Cell*>(owner_);}
    
  void  Term::setNet       (Net* n){
    if(n==NULL){
      net_->remove(&node_);
      net_=NULL;
      node_.setId(Node::noid);
    }else{
      if(net_!=NULL){
        net_->remove(&node_);
        net_=NULL;
        node_.setId(Node::noid);
      }
      net_=n;
      net_->add(&node_);
    }
  }
  void  Term::setNet       ( const std::string& name ){
    setNet(getOwnerCell()->getNet(name));
  }
  void  Term::setPosition  ( const Point& p){node_.setPosition(p);}
  void  Term::setPosition  ( int x, int y ){node_.setPosition(x,y);}
  
  void  Term::toXml ( std::ostream& stream ) const{
    std::string dir=Term::toString(getDirection());
    stream << "<term name=\"" << name_ << "\" direction=\"" << dir << "\"/>" << std::endl;
  }
  
  Term*  Term::fromXml ( Cell* cell, xmlTextReaderPtr reader ){
    Term* term = NULL;
    while ( true ) {
      switch ( xmlTextReaderNodeType(reader) ){
        case  XML_READER_TYPE_COMMENT:
        case  XML_READER_TYPE_WHITESPACE:
        case  XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
          continue;
      }

      std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
      
      Direction d = toDirection(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"direction" )));

      int x, y;
      bool bx = xmlGetIntAttribute(reader, "x", &x);
      bool by = xmlGetIntAttribute(reader, "y", &y);
      
      if(!bx || !by){
        std::cerr << "ERROR IN TERM" << std::endl;
        return NULL;
      }
        
      term = new Term(cell, name, d);
      term->setPosition(x, y);
    }
    return term;
  }
}
