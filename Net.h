#ifndef  NETLIST_NET_H
#define  NETLIST_NET_H


#include <string>
#include "Indentation.h"
#include "Term.h"
#include  "XmlUtil.h"

namespace Netlist {
  
  class Term;
  class Net{
  public:
  static       Net*                fromXml       ( Cell* , xmlTextReaderPtr );
                                   Net           ( Cell*, const std::string&, Term::Type );
                                   ~Net          ();
  
               Cell*               getCell       () const;
         const std::string&        getName       () const;
               unsigned int        getId         () const;
               Term::Type          getType       () const;
         const std::vector<Node*>& getNodes      () const;
               size_t              getFreeNodeId () const;
               void                add           ( Node* );
               bool                remove        ( Node* );
               void                toXml         ( std::ostream& ) const;
	       inline const std::vector<Line*>& Net::getLines () const{ return lines_; }
	       void		   add           (Line* line);
	       bool  		   remove 	 ( Line* line );
  private:
  Cell*               owner_;
  std::string         name_;
  unsigned int        id_;
  Term::Type          type_;
  std::vector<Node*>  nodes_;
  vector<Line*>       lines_;
  };
  class Instance;
  class Cell;
}



#endif  // NETLIST_NET_H
