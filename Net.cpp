#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include <iostream>
#include "XmlUtil.h"

namespace Netlist {
	using namespace std;

  Net::Net     ( Cell* c, const std::string& name, Term::Type t):owner_(c),name_(name),id_(c->newNetId()),type_(t),nodes_()
  {
    c->add(this);
  }

  Net::~Net    ()
  {
    owner_->remove(this);
    owner_ = NULL;
    for(std::vector<Node*>::iterator it=nodes_.begin(); it!=nodes_.end(); ++it)
      nodes_.erase(it);
  }

  Cell*                     Net::getCell       () const{return owner_;}
  const std::string&        Net::getName       () const{return name_;}
  unsigned int              Net::getId         () const{return id_;}
  Term::Type                Net::getType       () const{return type_;}
  const std::vector<Node*>& Net::getNodes      () const{return nodes_;}

  size_t                    Net::getFreeNodeId () const{
	  size_t i=0;
    for(vector<Node*>::const_iterator it=nodes_.begin(); it!=nodes_.end(); ++it, ++i)
      if(!*it) break;
    return i;
  }

  void  Net::add    ( Node* n){
	  if(!n) return;

	  size_t id= n->getId();
	  if(id == Node::noid){
		  id=getFreeNodeId();
		  n->setId(id);
	  }
	  if(id<nodes_.size()){

		  if(!nodes_[id]->setId(Node::noid))
			  cerr << "Erreur : le noeud d'id : "<< id << " n'était pas vide" << endl;
		  nodes_[id]=n;
    }else{
    	for(size_t tmax = nodes_.size(); tmax<id ; ++tmax)
    		nodes_.push_back(NULL);

      nodes_.push_back(n);
    }
  }
  bool  Net::remove ( Node* n){
    size_t i=0;
    for(std::vector<Node*>::iterator it=nodes_.begin(); it!=nodes_.end(); ++it, ++i){
      if(*it==n){
        nodes_[i]=NULL;
        return true;
      }
    }
    return false;
  }
  
  void  Net::toXml ( std::ostream& stream ) const{
    Indentation ind;
    std::string type = toString(type_);
    stream << "<net name=\"" << name_ << "\" type=\"" << type << "\"/>" << std::endl;
    ++ind;
    ++ind;
    ++ind;
    for(Node* n : nodes_){
      stream << ind;
      n->toXml(stream);
    }
    --ind;
    stream << ind << "</net>" << std::endl;
  }

  void  Net::add ( Line* line ){ 
	if (line) lines_.push_back( line ); 
  }

  bool  Net::remove ( Line* line ){
	 if (line) {
	    for ( vector<Line*>::iterator il = lines_.begin()
		; il != lines_.end() ; ++il ) {
	      if (*il == line) {
		lines_.erase( il );
		return true;
	      }
	    }
	  }
	  return false;
  }
  
  Net* Net::fromXml ( Cell* cell, xmlTextReaderPtr reader ){
    Net* net = NULL;
    while ( true ) {
      switch ( xmlTextReaderNodeType(reader) ){
        case  XML_READER_TYPE_COMMENT:
        case  XML_READER_TYPE_WHITESPACE:
        case  XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
          continue;
      }

      string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
      
      Term::Type t = toType(xmlCharToString(xmlTextReaderGetAttribute( reader, (const xmlChar*)"type" )));

      net = new Net(cell, name, t);
    }
    return net;
  }
}
